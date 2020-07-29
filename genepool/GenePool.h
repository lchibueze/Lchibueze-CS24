#ifndef GENEPOOL_H
#define GENEPOOL_H

#include "Person.h"
#include <istream>
#include <string>

// This file describes the GenePool interface you need to implement.
// Don't edit this!  Your code goes in the MyGenePool.* files.


class GenePool {
public:
  // Read genealogy data from an input stream.
  // See the readme for file format information.
  static GenePool* create(std::istream& stream);
public:
  // Find a person in the database by name.
  // Return nullptr if there is no such person.
  virtual Person* find(const std::string& name) const = 0;

  // Don't forget!
  virtual ~GenePool() {}
};

#endif
