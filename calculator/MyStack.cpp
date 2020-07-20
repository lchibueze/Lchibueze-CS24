#include "MyStack.h"
#include <cmath>
#include <stdexcept>


// TODO: Implement MyStack member functions here.

MyStack::MyStack(){
    topnode=NULL;
    count=0;
};

 // Remove everything from the stack.
void MyStack::clear() {
    while (count != 0) {
        pop();
    }
};

  // Is this stack empty?
bool MyStack::is_empty() const{
    if (count==0)
        return true;
    
    else
        return false;
        
};

  // Push an item onto the top of the stack.
void MyStack::push(double item){
    MyNode* temp = new MyNode();
    temp->value = item;
    temp->below = topnode;
    topnode=temp;
    count++;
};


  // Pop an item off the top of the stack and return it.
  // If the stack is empty, throw std::underflow_error.
double MyStack::pop(){
    if (!is_empty()) {
        double temp1 = topnode->value;
        MyNode* temp2 = topnode;
        topnode = topnode ->below;
        count--;
        delete temp2;
        return (temp1);
    }
    else
        throw std::underflow_error ("underflow_error");
};

  // Return the item currently on top of the stack.
  // If the stack is empty, throw std::underflow_error.
double MyStack::top() const {
    if (!is_empty ())
        return topnode -> value;
    else
        throw std::underflow_error ("underflow error");

};


  // Don't forget!
MyStack::~MyStack() {
    clear();
}
;
