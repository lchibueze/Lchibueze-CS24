#ifndef NUMBER_H
#define NUMBER_H

class Number: public AST {
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
