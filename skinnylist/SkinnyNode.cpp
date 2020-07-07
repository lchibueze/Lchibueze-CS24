// Include the class we're implementing:
#include "SkinnyList.h"


SkinnyNode::SkinnyNode(const std::string& item, SkinnyNode* next) {
  // Whoever calls this provides the info we need.  Just copy it:
  mItem = item;
  mNext = next;
}

SkinnyNode::~SkinnyNode() {
  // A node "owns" the next node, so
  // it's in charge of deleting it.
  delete mNext;
}


std::string& SkinnyNode::item() {
  // This one is easy...
  return mItem;
}

SkinnyNode* SkinnyNode::next() const {
  // Also easy...
  return mNext;
}

void SkinnyNode::setNext(SkinnyNode* next) {
  // Does exactly what it says on the tin.
  mNext = next;
}
