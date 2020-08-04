#include "MyGenePool.h"
#include "MyPerson.h"
#include <sstream>
#include <map>

// This is here to avoid having yet another object file:
GenePool* GenePool::create(std::istream& stream) {
  // TODO!
    return new MyGenePool(stream);
}


// MyGenePool Member Functions

MyGenePool::MyGenePool(std::istream& stream){
    std::string line,name,gender,mother,father;
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
        
        MyPerson* temp = new MyPerson(name,my_gender,motherptr,fatherptr);
        
        if (motherptr != NULL)
            motherptr->addchild (temp);
        
        if (fatherptr !=NULL)
            fatherptr->addchild (temp);
        
        MyMap.insert(std::pair<std::string, MyPerson*> (name, temp));
    }
}

MyPerson* MyGenePool::find(const std::string& name) const{
    auto temp = MyMap.find(name);
    if (temp==MyMap.end()){
        return NULL;
    }
    return temp->second;
}


