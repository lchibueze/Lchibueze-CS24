#ifndef MYSTACK_H
#define MYSTACK_H

#include "Stack.h"

class MyStack: public Stack {
  // TODO: Member Variables
public:
  // TODO: Constructor & Destructor

  // Required Stack functions.
  // See Stack.h for descriptions.
  void   clear();
  bool   is_empty() const;
  void   push(double item);
  double pop();
  double top() const;

  // TODO: Add helper functions if necessary.
};

#endif
