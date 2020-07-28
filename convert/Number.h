#ifndef NUMBER_H
#define NUMBER_H

#include"AST.h"

class Number: public AST {
  // Member Variables
    double Dnum;
public:
  // Constructor
    Number(const std::string& token);
  // Destructor?

  // Required helper functions.
    int arity()         const;
    int associativity() const;
    int precedence()    const;

  // Required member functions.
    std::string infix()   const;
    std::string postfix() const;
    std::string prefix()  const;
    std::string to_string() const;
};

#endif
