#ifndef MYSTACK_H
#define MYSTACK_H

#include "Stack.h"
#include <string>
#include <stack>

class MyNode{

public:
    double value;
    MyNode* below;
};

class MyStack: public Stack {
  // TODO: Member Variables
    MyNode* topnode;
    
    
    
public:
    int count;
  // TODO: Constructor & Destructor
    MyStack();

  // Required Stack functions.
  // See Stack.h for descriptions.

  void   clear();
  bool   is_empty() const;
  void   push(double item);
  double pop();
  double top() const;
    
    ~MyStack();

  // TODO: Add helper functions if necessary.
};

#endif
