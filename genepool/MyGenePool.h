#ifndef MYGENEPOOL_H
#define MYGENEPOOL_H

#include "GenePool.h"
#include "MyPerson.h"
#include <map>

class MyGenePool: public GenePool {
  // Member Variables
    std::map<std::string, MyPerson*> MyMap;
   

public:
  // Constructor
    MyGenePool(std::istream& stream);
  // Destructor
  //  ~MyGenePool();

  // Required Function
  MyPerson* find(const std::string& name) const;

  // Other Member Functions
};

#endif
