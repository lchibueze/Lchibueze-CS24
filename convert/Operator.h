#ifndef OPERATOR_H
#define OPERATOR_H

#include "AST.h"

class Operator: public AST {
  // Member Variables
    std::string mToken;
    AST* mLDN;
    AST* mRDN;
public:
  // Constructor
    Operator(const std::string& token, AST* ldn, AST* rdn);
  // Destructor?
    ~Operator();

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
