#include "AST.h"

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>


int main(int argc, char** argv) {
  // Check your command line arguments...
    if ((argc!=3)|| (strcmp(argv[1],"prefix")!=0 && strcmp(argv[1],"postfix")!=0)|| (strcmp(argv[2],"prefix")!=0 && strcmp(argv[2],"infix")!=0 && strcmp(argv[2],"postfix")!=0))
    {
        std::cout<<"USAGE: convert [input-format] [output-format]"<< std::endl <<"  Valid input formats:   prefix, postfix" <<std::endl <<
        "  Valid output formats:  prefix, infix, postfix" <<std::endl;
        return 0;
    }
        

  std::string line;
  while(std::getline(std::cin, line)) {
      std::cout<<line;
    std::istringstream tokens(line);

    // Convert the expression...
      if (strcmp(argv[1], "prefix")==0 && strcmp(argv[2], "prefix")==0)
      {
          AST* ast= AST::parse_prefix (tokens);
          if (ast==NULL)
              continue;
          std::string temp = ast->prefix();
          if (line.length()!=temp.length()){
              std::cout<<"Too many operands."<<std::endl;
              continue;
          }
              
        std::cout<<"=> "<<ast->prefix() <<std::endl;
      }
      if (strcmp(argv[1], "prefix")==0 && strcmp(argv[2], "infix")==0)
           {
               AST* ast= AST::parse_prefix (tokens);
               if (ast==NULL)
                   continue;
               std::string temp = ast->prefix();
               if (line.length()!=temp.length()){
                   std::cout<<"Too many operands."<<std::endl;
                   continue;
               }
               
               std::cout<<"=> "<<ast->infix() <<std::endl;
           }
      if (strcmp(argv[1], "prefix")==0 && strcmp(argv[2], "postfix")==0)
           {
               AST* ast= AST::parse_prefix (tokens);
               if (ast==NULL)
                   continue;
               std::string temp = ast->prefix();
               if (line.length()!=temp.length()){
                   std::cout<<"Too many operands."<<std::endl;
                   continue;
               }
               
               std::cout<<"=> "<<ast->postfix() <<std::endl;
           }
      if (strcmp(argv[1], "postfix")==0 && strcmp(argv[2], "prefix")==0)
           {
               AST* ast= AST::parse_postfix (tokens);
            
               if (ast==NULL)
                continue;
               std::cout<<"=> "<<ast->prefix() <<std::endl;
           }
      if (strcmp(argv[1], "postfix")==0 && strcmp(argv[2], "infix")==0)
           {
               AST* ast= AST::parse_postfix (tokens);
               
               if (ast==NULL)
                   continue;
               std::cout<<"=> "<<ast->infix() <<std::endl;
           }
      if (strcmp(argv[1], "postfix")==0 && strcmp(argv[2], "postfix")==0)
           {
               AST* ast= AST::parse_postfix (tokens);
               if (ast==NULL)
                   continue;
               std::cout<<"=> "<<ast->postfix() <<std::endl;
           }
    
  }
}
