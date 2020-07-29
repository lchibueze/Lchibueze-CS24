#ifndef MYGENEPOOL_H
#define MYGENEPOOL_H

#include "GenePool.h"
#include "MyPerson.h"
#include <map>

class MyGenePool: public GenePool {
  // Member Variables

public:
  // Constructor
  // Destructor

  // Required Function
  MyPerson* find(const std::string& name) const;

  // Other Member Functions
};

#endif
