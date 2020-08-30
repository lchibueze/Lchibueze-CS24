#include "MyScheduler.h"
#include <map>

#define INFINITY INT16_MAX

Scheduler* Scheduler::create(
  unsigned int                        deadline,
  std::map<std::string, unsigned int> cities,
  std::vector<std::string>            factories,
  std::vector<Route>                  routes
) {
  return new MyScheduler(deadline, cities, factories, routes);
}

// MyScheduler Member Functions

MyScheduler::MyScheduler(unsigned int deadline, std::map<std::string, unsigned int> cities, std::vector<std::string> factories, std::vector<Route> routes) {
  mdeadline=deadline;
  mfactories=factories;
  mroutes=routes;


// bool MyScheduler::verify_route (mroutes.id) {
  
for (const auto &pair : cities) 
{
  City city;
  city.name       = pair.first;
  city.factory    = false;
  city.population = pair.second;
  city.arrivals   = new unsigned int[deadline+1]();
  city.vaccines   = 0;

  mcities[pair.first]= city;
}

for (const auto &name: factories)
{
  mcities[name].factory=true;
}
}

int minimumDays (int days[], bool visited []) 
{
  days[]= path.days();
  Route path;
  int min = INFINITY, index;

    for (i=0; i<mdeadline; i++)
    {
      if (visited[i] == false && days[i]<=min)
      {
        min = days[i];
        index=i;
      }
    }
  return index;
}

void MyScheduler::dijkstra(int source) {
  Shipment Ship;
  Route path; 
  source = Ship.source();

  source =0;
}

std::vector<Shipment> MyScheduler::schedule() {
  //Step 1a: Set all routes to cities of infinity
  //Step 1b: Create a map that stores the routes for all cities  
  std::map<std::string,int> fastestRoute;
  std::map<std::string, std::vector<int>> cityRoutes;
  for (const auto &pair : mcities ){
    fastestRoute[pair.first] = INFINITY;

    std::vector<int> temp; //empty vector 
    cityRoutes[pair.first] = temp;
    

    }

  //Step 2: iterate through factory cities
  for (const auto &factory : mfactories ) 
  {
    //Perform Dijkstra's algorithm, source node is factory
  }


  }

}

MyScheduler::~MyScheduler(){}

