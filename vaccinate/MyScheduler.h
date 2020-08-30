#ifndef MYSCHEDULER_H
#define MYSCHEDULER_H

#include "Scheduler.h"

class MyScheduler: public Scheduler {
  Struct City{
    std::string   name;
    bool          factory;
    unsigned int  population;
    unsigned int  vaccines;
    unsigned int* arrivals;
  };
  
  // Member Variables
  unsigned int mdeadline; //global deadline
  std::map<std::string, City> mcities;
  //std::map<std::string, int> city_vaccines; // will store the number of vaccines left to deliver to a city per city
  std::vector<std::string> mfactories;
  std::vector<Route> mroutes;
  //std::map<std::string, std::vector<int> > efficient_route; //fastest/cheapest route as well
  //std::map<std::string, unsigned int> find_cheaproute; 

public:
  // Constructor
  MyScheduler(unsigned int deadline, std::map<std::string, unsigned int> cities, std::vector<std::string> factories, std::vector<Route> routes);
  // Destructor?
  ~MyScheduler();

  // Required Member Function
  std::vector<Shipment> schedule();
  //bool verify_route (/*vector<int> */mroutes.id);

  int minimumDays(int days [], bool visited []);
  void dijkstra ();
};

#endif
