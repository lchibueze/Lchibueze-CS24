#include "Stack.h"
#include "MyStack.h"
#include <string>
#include <iostream>
#include <cmath>
#include <sstream>


// TODO: Calculator helper fuctions, if necessary.

void calculator(std::string equation){
    std::stringstream stream(equation);
    std::string token;
    MyStack Stack;
    
    
    
    while (stream>>token){
        //std::cout<<"\""<<token<<"\""<<std::endl;
        double num;
        std::string temp = "NULL";
        try {
            num = std::stod(token);
            temp =std::to_string(num);
            temp = temp.substr(0,token.length());
            if (token.compare(temp)==0){
                //std::cout<< num <<std::endl;
                Stack.push(num);
            }
            else {
                std::cout<<"Unknown token." <<std::endl;
                return;
            }
            
        }
        catch(const std::invalid_argument& e){
            if (temp == "NULL"){
                
                if ((token == "+" ||token== "-"||token== "*" || token== "/" ||token == "%" ||token=="~"||token =="^")) {
                    double result,num1,num2;
                    int count = 0;
                    
                    
                    
                    if (token== "~"){
                        if (Stack.count >=1){
                            num2 = Stack.top();
                            Stack.pop();
                            count +=1;
                            result = num2 * -1;
                            Stack.push (result);
                        }
                        
                        else {
                            std::cout<< "Not enough operands." << std::endl;
                            return;
                        }
                    }
                    else {
                        if (Stack.count >=2){
                            num2 = Stack.top();
                            Stack.pop();
                            count +=1;
                            
                            num1 = Stack.top();
                            Stack.pop();
                            count +=1;
                        }
                            
                        else {
                            std::cout<< "Not enough operands." << std::endl;
                            return;
                        }
                        
                    }
                    
                    
                    if (token=="+"){
                        result = num1 + num2;
                        Stack.push(result);
                    }
                    if (token== "-"){
                        result = num1 - num2;
                        Stack.push (result);
                    }
                    if (token== "*"){
                        result = num1 * num2;
                        Stack.push (result);
                    }
                    if (token== "/"){
                        if (num2==0){
                            std::cout<<"Division by zero." << std::endl;
                            return;
                        }
                        else {
                            result = num1 / num2;
                            Stack.push (result);
                        }
                        
                    }
                    if (token== "%"){
                        
                        if (num2==0) {
                            std::cout<<"Division by zero." <<std::endl;
                            return;
                        }
                        else {
                            result = std:: fmod(num1,num2);
                            Stack.push (result);
                        }
                        
                        
                    }
                    if (token== "^"){
                        result = pow(num1,num2);
                        Stack.push (result);
                    }
                    
                    
                }
                
                
                else {
                    std::cout <<"Unknown token." <<std::endl;
                    return;
                }
                
                
            }
            
            
        }
        
        
        
        
        
        
        
        
        
        
    }
    if (Stack.count !=1) {
        std::cout<<"Too many operands." <<std::endl;
        return;
    }
    
    std::cout<<"= " << Stack.top() <<std::endl;
    return;
    
}





int main() {
    // TODO: Implement a calculator!
    
    std::string equation;
    
    while (getline (std::cin,equation)){
        
        
        if (equation.length()==0) {
            std::cout<<"No Expression." << std::endl;
        }
        else{
        
            calculator(equation);
        }
        
        
        
    
        
    }
    return 0;
}
