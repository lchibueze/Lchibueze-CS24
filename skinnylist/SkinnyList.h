#ifndef SKINNYLIST_H
#define SKINNYLIST_H

#include <string>

// This class represents a single node in the list.
// It's simple enough that we could have made it a struct
// with public member variables, but we didn't.
class SkinnyNode {
  // Private member variables
  std::string mItem;
  SkinnyNode* mNext;

public:
  // Constructor
  SkinnyNode(const std::string& item, SkinnyNode* next);

  // Destructor
  ~SkinnyNode();

  // Get a reference to the item stored here.
  std::string& item();

  // Get a pointer to the next node in the list.
  // Returns nullptr if this is the last node.
  SkinnyNode* next() const;

  // Set the next pointer to point elsewhere.
  void setNext(SkinnyNode* next);
};

// This class represents an entire singly linked list.
// It keeps track of its first node, and also a count of
// items for easy access.
class SkinnyList {
  // Private member variables
  SkinnyNode* mHead;
  int         mCount;

public:
  // Constructor
  SkinnyList();

  // Destructor
  ~SkinnyList();

  // How many items are in this list?
  int count() const;

  // Add an item to the list at a given index.
  // Throws std::out_of_range if index is invalid.
  void insert(int index, const std::string& item);

  // Get a reference to the item at the given index.
  // Throws std::out_of_range if index is invalid.
  std::string& lookup(int index) const;

  // Remove the item at the given index.
  // Throws std::out_of_range if index is invalid.
  void remove(int index);
};

#endif
