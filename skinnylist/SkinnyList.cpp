// Include the class we're implementing:
#include "SkinnyList.h"

// To get std::out_of_range:
#include <stdexcept>


SkinnyList::SkinnyList() {
  // We're creating an empty list.
  // An empty list has no nodes:
  mHead = nullptr;

  // An empty list has no items:
  mCount = 0;
}

SkinnyList::~SkinnyList() {
  // The list "owns" its head node, so
  // it's in charge of cleaning it up.
  delete mHead;
}


int SkinnyList::count() const {
  // This one's easy as long as we keep mCount accurate.
  return mCount;
}

void SkinnyList::insert(int index, const std::string& item) {
  if(index < 0 || index > mCount) {
    // Invalid index!  Throw an exception.
    throw std::out_of_range("Invalid index.");
  }

  if(index == 0) {
    // Inserting at the very beginning is a special case.
    mHead = new SkinnyNode(item, mHead);
  }
  else{
    // Typical case: follow the list and count...
    // Stop right BEFORE where we want to insert.
    SkinnyNode* node = mHead;
    for(int i = 0; i < index-1; ++i) {
      node = node->next();
    }

    // Make a new node to hold our new item.
    // Its next should be our current node's next.
    SkinnyNode* newnode = new SkinnyNode(item, node->next());

    // Update our current node to point at the new node.
    node->setNext(newnode);
  }

  // Don't forget to update count!
  mCount += 1;
}

std::string& SkinnyList::lookup(int index) const {
  if(index < 0 || index >= mCount) {
    // Invalid index!  Throw an exception.
    throw std::out_of_range("Invalid index.");
  }

  // Follow the list and count...
  // Stop at the node that has our data.
  SkinnyNode* node = mHead;
  for(int i = 0; i < index; ++i) {
    node = node->next();
  }

  // This must be it!
  return node->item();
}

void SkinnyList::remove(int index) {
  if(index < 0 || index >= mCount) {
    // Invalid index!  Throw an exception.
    throw std::out_of_range("Invalid index.");
  }

  // A variable to store the node we're going to kill:
  SkinnyNode* dead;

  if(index == 0) {
    // Deleting the head node is a special case.
    dead  = mHead;
    mHead = dead->next();
  }
  else {
    // Typical case: follow the list and count...
    // Stop right BEFORE the node we want to delete.
    SkinnyNode* node = mHead;
    for(int i = 0; i < index-1; ++i) {
      node = node->next();
    }

    // The next node is the one we want to remove.
    dead = node->next();

    // Update the current node to point past the dead one.
    node->setNext(dead->next());
  }

  // Update the dead node so that it has no next pointer.
  // If we don't, it's destructor would delete the rest of the list!
  dead->setNext(nullptr);

  // Now we can safely delete it.
  delete dead;

  // And finally...
  mCount -= 1;
}
