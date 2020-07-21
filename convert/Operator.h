#ifndef OPERATOR_H
#define OPERATOR_H

class Operator: public AST {
  // Member Variables
public:
  // Constructor
  // Destructor?

  // Required helper functions.
  int arity()         const;
  int associativity() const;
  int precedence()    const;

  // Required member functions.
  std::string infix()   const;
  std::string postfix() const;
  std::string prefix()  const;
};

#endif
