#include "AST.h"
#include "Number.h"
#include "Operator.h"
#include <cctype>
#include <stack>
#include <string>
#include <iostream>

// Helper functions (recommended):
// bool is_operator(const std::string& token);
// bool is_number(const std::string& token);

bool is_operator(const std::string& token){
    if ((token=="+")||(token=="-")||(token=="*")||(token=="/")||(token=="%")||(token=="~")||(token=="^"))
        return true;
    else
        return false;
    
};


bool is_number(const std::string& token){
  int counter = 0;
    if(token[0] == '-' || token[0] == '+'){
      for (std::string::size_type i=1; i<token.size(); i++){
        if(token[i] == '.'){
          counter++;
        }
          if(!isdigit(token[i]) && token[i] != '.'){
            return false;
          }

      }

      if(counter > 1){
        return false;
      }
      return true;
    }

    for (std::string::size_type i=0; i<token.size(); i++){
      if(token[i] == '.'){
        counter++;
      }
        if(!isdigit(token[i]) && token[i] != '.'){
          return false;
        }

    }
    if(counter > 1){
      return false;
    }
    return true;


};
AST* AST::parse_prefix(std::istream& tokens) {
    std::string token;
    if (tokens>>token) {
        if (token=="~") {
            AST* rdn = AST::parse_prefix (tokens);
            return (new Operator ("~",nullptr,rdn));
        }
        else if (is_operator(token)) {
            AST* ldn = AST::parse_prefix (tokens);
            AST* rdn = AST::parse_prefix (tokens);
            return (new Operator (token,ldn,rdn));

            
        }
        else if (is_number(token)){
            return new Number (token);
        }
        else{
            std::cout<<"Invalid token: "<<token<<std::endl;
            return NULL;
        }
    
    
    }
    return NULL;
};

AST* AST::parse_postfix(std::istream& tokens) {
    std::stack<AST*> Stack;
    std::string token;
        
        while(tokens>>token){
            
            if (token == "~"){
                if (Stack.size()<1){
                    std::cout<<"Not enough operands."<<std::endl;
                    return NULL;
                }
                AST* rdn = Stack.top();
                Stack.pop();
                
                AST* ast = new Operator("~",nullptr,rdn);
                Stack.push(ast);
            }
            
            if (is_operator(token)){
                if (Stack.size()<2){
                    std::cout<<"Not enough operands."<<std::endl;
                    return NULL;
                }
                AST* rdn = Stack.top();
                Stack.pop();
                
                AST* ldn = Stack.top();
                Stack.pop();
                
                AST* ast = new Operator(token,ldn,rdn);
                Stack.push(ast);
                
            }
            else if (is_number(token)){
                Stack.push(new Number(token));
            }
            else{
                std::cout<<"Invalid token: "<<token<<std::endl;
                return NULL;
                }
                
        }
    if (Stack.size()!=1){
        std::cout<<"Too many operands."<<std::endl;
        return NULL;
    }
    
        return Stack.top();

};


