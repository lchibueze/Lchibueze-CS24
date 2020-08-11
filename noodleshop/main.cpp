#include "NoodleShop.h"
#include "Validator.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <stdexcept>

// Global for creating unique IDs.
unsigned int order_id = 0;

// Random number generator initialization.
std::random_device rd;
std::mt19937 gen(rd());


// Helper function to parse noodle information.
std::vector<Noodle> parse_noodles(std::istream& stream, unsigned int n) {
  std::string line;
  std::vector<Noodle> noodles;
  for(unsigned int i = 0; i < n; ++i) {
    if(!std::getline(stream, line)) {
      throw std::runtime_error("Could not read noodle line.");
    }

    Noodle n;
    std::istringstream linestream(line);
    if(!(linestream >> n.batch_size >> n.cook_time >> n.ingredient_cost >> n.serving_price >> std::ws)) {
      throw std::runtime_error("Invalid noodle line: " + line);
    }

    std::getline(linestream, n.name);
    if(n.name == "") {
      throw std::runtime_error("Invalid noodle line: " + line);
    }

    noodles.push_back(n);
  }

  return noodles;
}

// Helper function to parse arrival rates and generate orders.
std::vector<Order> parse_orders(std::istream& stream, const std::vector<Noodle>& noodles) {
  std::string line;
  if(!std::getline(stream, line)) {
    throw std::runtime_error("Could not read order line.");
  }

  std::vector<Order> orders;
  std::istringstream linestream(line);
  for(const Noodle& noodle: noodles) {
    float arrival_rate;
    if(!(linestream >> arrival_rate)) {
      throw std::runtime_error("Invalid order line: " + line);
    }

    std::poisson_distribution<unsigned int> dist(arrival_rate);
    for(int i = dist(gen); i > 0; --i) {
      Order order;
      order.id     = ++order_id;
      order.noodle = noodle.name;
      orders.push_back(order);
    }
  }

  return orders;
}

std::vector<Noodle> getPriority(std::istream& file){
  //will read though file, assign noodle of highest priorty to the minute (index of vector), 
  //...if all same, cook cheapest one...
  std::string line;
  unsigned int npots;
  unsigned int rent;
  unsigned int expect;
  unsigned int nnoodles;
  std::vector<Noodle> noodles;
  std::vector<Noodle> future;
  NoodleShop* shop = nullptr;

  if(!std::getline(file, line)) {
      throw std::runtime_error("Could not read file!");
    }

    std::istringstream metadata(line);
    if(!(metadata >> npots >> rent >> expect >> nnoodles)) {
      throw std::runtime_error("Could not read metadata!");
    }

    noodles = parse_noodles(file, nnoodles);
    shop = NoodleShop::create(npots, rent, expect, noodles);
    std::map<int, Noodle> noodleMap;
    for(unsigned long i = 0; i<noodles.size(); i++){
      noodleMap.insert(std::pair<int, Noodle>(i, noodles[i]));
    }

    unsigned int minute = 0;
    while(std::getline(file, line)) {
      std::istringstream linestream(line);
      
      //add tab delimiter
      int priority = -1;
      double temp = 0;
      int counter = 0;
      std::string temp_line;
      std::vector<double> info;
      while(std::getline(linestream, temp_line, '\t')){
          double temp1 = std::stod(temp_line);
          info.push_back(temp1);
          if(temp1 > temp){
            temp = temp1;
            priority = counter;
          }

          counter++;
      }
      bool same = true;
      for(unsigned long i = 1; i<info.size(); i++){
        if(info[i-1] != info[i]){
          same = false;
        }
      }

      //will push a "NULL" named noodle to the future vector if all values are the same (no predictibility)
      if(same){
        Noodle a;
        a.name = "NULL";
        future.push_back(a);
      }
      else{
        future.push_back(noodleMap[priority]);
      }
      minute += 1;
    }

    return future;
}

int main(int argc, char** argv) {
  if(argc != 2) {
    std::cerr << "USAGE: ./noodles [data-file]\n";
    std::exit(1);
  }

  // Change this to get more detailed logs!
  int verbosity = 0;

  unsigned int npots;
  unsigned int rent;
  unsigned int expect;
  unsigned int nnoodles;
  std::vector<Noodle> noodles;
  NoodleShop* shop = nullptr;

  try {
    std::string line;
    std::ifstream temp(argv[1]);
    std::vector<Noodle> future = getPriority(temp); //IMPORTANT
    // for (unsigned long i = 0; i<future.size(); i++){
    //   std::cout<<i <<" "<< future[i].name<<std::endl;
    // }
    // exit(0);

    std::ifstream file(argv[1]);
    //std::ifstream file("data/lunch-rush.tsv");

    if(!std::getline(file, line)) {
      throw std::runtime_error("Could not read file!");
    }

    std::istringstream metadata(line);
    if(!(metadata >> npots >> rent >> expect >> nnoodles)) {
      throw std::runtime_error("Could not read metadata!");
    }

    noodles = parse_noodles(file, nnoodles);
    Validator validator(npots, rent, noodles, verbosity);
    shop = NoodleShop::create(npots, rent, expect, noodles);

    unsigned int minute = 0;
    while(std::getline(file, line)) {
      std::istringstream linestream(line);
      auto in = parse_orders(linestream, noodles);

      std::cout<<"orders: "; 
      for(unsigned long i = 0; i< in.size(); i++){
        std::cout<<in[i].noodle << " ";
      }
      std::cout<<std::endl;

      auto ok = shop->orders(minute, in);

      std::vector<Order> accepted;
      std::set_intersection(
        in.begin(), in.end(), ok.begin(), ok.end(),
        std::inserter(accepted, accepted.begin())
      );

      std::cout<<"Accepted orders: ";
      for(unsigned long i = 0; i<accepted.size(); i++){
        std::cout<<accepted[i].noodle<< " ";
      }
      std::cout<<std::endl;

      validator.orders(minute, accepted);
      Action* action = shop->action(minute);
      validator.validate(action);

      std::cout<<minute<<std::endl;

      delete action;
      
      minute += 1;
      validator.printLog();
      // if(minute == 1){
      //   exit(0);
      // }
    }

    validator.summarize();
  }
  catch(const std::exception& e) {
    std::cerr << "ERROR: " << e.what() << "\n";
    std::exit(1);
  }

  delete shop;
  return 0;
}
