#include "MyStack.h"

// TODO: Implement MyStack member functions here.

void clear() ;

  // Is this stack empty?
bool is_empty() const;

  // Push an item onto the top of the stack.
void push(double item);

  // Pop an item off the top of the stack and return it.
  // If the stack is empty, throw std::underflow_error.
double pop();

  // Return the item currently on top of the stack.
  // If the stack is empty, throw std::underflow_error.
double top() const;

  // Don't forget!
virtual ~MyStack() {}
};
