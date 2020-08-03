#include "MyGenePool.h"
#include "MyPerson.h"
#include <sstream>

// This is here to avoid having yet another object file:
GenePool* GenePool::create(std::istream& stream) {
  // TODO!
    return new MyGenePool(stream);
}


// MyGenePool Member Functions

MyGenePool::MyGenePool(istream& stream){
    string line,name,gender,mother,father;
    while (getline(stream,line)){
        if (line.length() ==0){
            continue;
        }
        
        if (line[0]=='#'){
            continue;
        }
        std::istringstream ss (line);
        getline(ss,name,'\t');
        getline(ss,gender,'\t');
        getline(ss,mother,'\t');
        getline(ss,father,'\t');
        
        MyPerson* motherptr;
        MyPerson* fatherptr;
        
        Gender my_gender;
        
        if (gender.compare("female")==0)
            my_gender = Gender::FEMALE;
        
        if (gender.compare("male")==0)
            my_gender = Gender::MALE;
        
        if (mother.compare("???") == 0)
            motherptr=NULL;
        else
            motherptr=find(mother);
             
        if (father.compare("???") == 0)
            fatherptr=NULL;
        else
            fatherptr=find(father);
        
        MyPerson* temp = new MyPerson (name,my_gender,mother,father);
        
        if (motherptr != NULL)
            motherptr->addchild (temp);
        
        if (fatherptr !=NULL)
            fatherptr->addchild (temp);
        
        
    }
}

MyPerson* MyGenePool::find(const std::string& name) const{
    
}


