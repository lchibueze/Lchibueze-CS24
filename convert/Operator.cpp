#include "Operator.h"
#include <iostream>
// Implement Operator member functions here.

Operator::Operator(const std::string& token, AST* ldn, AST* rdn){
    mToken=token;
    mLDN=ldn;
    mRDN=rdn;
};
 
   

 // Required helper functions.
int Operator::arity() const {
    if(mToken == "~")
        return 1;
      return 2;
    };
 
int Operator::associativity() const {
    if ((mToken=="~")||(mToken=="^"))
        return 1; //1 equals right
    return -1;
        };
int Operator::precedence() const{
    if ((mToken=="+")||(mToken=="-"))
        return 0;//0 is the lowest
    if ((mToken=="*")||(mToken=="/")||(mToken=="%"))
        return 1;//1 is second lowest
    if (mToken=="~")
        return 2; //2 is medium
    if (mToken=="^")
        return 3; //3 is highest
    return -1; //for safety measures
};

 // Required member functions.
std::string Operator::infix()  const {
    if (mToken=="~"){
        if (mRDN==NULL){
            std::cout<<"Not enough operands."<<std::endl;
            exit(0);
        }
        return "~ " + mRDN->infix();
    }
    if (mLDN==NULL||mRDN==NULL){
        std::cout<<"Not enough operands."<<std::endl;
        exit(0);
    }
    if (mLDN->precedence()<=precedence() && mRDN->precedence()<=precedence())
        return std::string("(")+mLDN->infix() + std::string (") (") + mToken + std::string(" ") + mRDN->infix() std::string(")");
        
  if (mLDN->precedence() <= precedence()){
         return std::string("(")+mLDN->infix() + std::string (") ") + mToken + std::string(" ") + mRDN->infix();
     }
     if(mRDN->precedence() <= precedence()){
         return mLDN->infix() + std::string (" ") + mToken + std::string(" (") + mRDN->infix() + std::string(")");
     }
     else{
         return mLDN->infix() + std::string (" ") + mToken + std::string(" ") + mRDN->infix();
     }
    }
std::string Operator::postfix() const {
    if (mToken=="~"){
        if (mRDN==NULL){
            std::cout<<"Not enough operands."<<std::endl;
            exit(0);
        }
        return mRDN->postfix() + " ~";
    }
    if (mLDN==NULL||mRDN==NULL){
        std::cout<<"Not enough operands."<<std::endl;
        exit(0);
    }
    return
    mLDN->postfix() + std::string(" ") + mRDN->postfix() + std::string(" ") + mToken;
    }
std::string Operator::prefix()  const {
    if (mToken == "~"){
        if (mRDN==NULL){
            std::cout<<"Not enough operands."<<std::endl;
            exit(0);
        }
        return "~ " + mRDN->prefix();
    }
    if (mLDN==NULL||mRDN==NULL){
        std::cout<<"Not enough operands."<<std::endl;
        exit(0);
    }
    return
    mToken + std::string(" ") + mLDN->prefix() + std::string(" ") + mRDN->prefix();
}

Operator::~Operator(){
    
};
