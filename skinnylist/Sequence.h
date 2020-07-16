#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>

// This class defines the abstract Sequence type.
// A Sequence is an ordered list of some type (here it's strings).

// The "virtual ... = 0" syntax basically means:
//  - I don't know how to implement this function yet (because
//    I don't know what concrete data type will be used).
//  - But all Sequence implementations are required to expose
//    these functions.

class Sequence {
public:
  // All sequences should know how many items there are.
  virtual int count() const = 0;

  // All sequences should have a way to insert an item at any index.
  virtual void insert(int index, const std::string& item) = 0;

  // All sequences should be able to find the item at any index.
  virtual std::string& lookup(int index) const = 0;

  // All sequences should be able to remove the item at any index.
  virtual void remove(int index) = 0;

  // Virtual destructor to ensure proper cleanup.
  virtual ~Sequence() {}
};

#endif
