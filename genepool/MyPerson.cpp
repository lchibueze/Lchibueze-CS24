#include "MyPerson.h"
#include "SetOperators.h"
#include <set>
#include <algorithm>
// MyPerson Member Functions

MyPerson::MyPerson(std::string& name, Gender gender, MyPerson* mother, MyPerson* father) {
    
    myname=name;
    mygender=gender;
    mymother=mother;
    myfather=father;

}

void MyPerson::addchild(MyPerson* child){
    mychildren.insert(child);
}


const std::string& MyPerson::name() const {
    return myname;
    }

Gender MyPerson::gender() const {
    return mygender;
}

MyPerson* MyPerson::mother() {
    return mymother;
}

MyPerson* MyPerson::father() {
    return myfather;
}

std::set<Person*> MyPerson::parents(PMod pmod  ) {
    std::set<Person*> temp;
    
    switch (pmod) {
        case PMod::MATERNAL:{
            if (mymother!=NULL){
                temp.insert(mymother);
            }
            break;
        }
        case PMod::PATERNAL:{
            if (myfather!= NULL){
                temp.insert(myfather);
            }
            break;
        }
            
        default:{
            if (mymother!=NULL)
                temp.insert(mymother);
            if (myfather!=NULL)
                temp.insert(myfather);
            break;
        }
    }
    return temp;
    
}

std::set<Person*> MyPerson::grandmothers(PMod pmod  ) {
    std::set<Person*> parent_set = parents(pmod);
    std::set<Person*> temp;
    
    for(auto it = parent_set.begin(); it != parent_set.end(); ++it){
        if ((*it) != NULL) {
            std::set<Person*> temp2 = (*it)->parents(PMod::MATERNAL);
            temp.insert(temp2.begin(),temp2.end());
        }
    }
    return temp;
    
    
}

std::set<Person*> MyPerson::grandfathers(PMod pmod  ) {
    std::set<Person*> parent_set = parents(pmod);
    std::set<Person*> temp;
    
    for(auto it = parent_set.begin(); it != parent_set.end(); ++it){
        if ((*it) != NULL){
            std::set<Person*> temp2 = (*it)->parents(PMod::PATERNAL);
            temp.insert(temp2.begin(),temp2.end());
        }
    }
    return temp;
    
    
}

std::set<Person*> MyPerson::grandparents(PMod pmod  ) {
    std::set<Person*> parent_set = parents(pmod);
    std::set<Person*> temp;
    
    for(auto it = parent_set.begin(); it != parent_set.end(); ++it){
        if ((*it) != NULL){
            std::set<Person*> temp2 = (*it)->parents(PMod::ANY);
            temp.insert(temp2.begin(),temp2.end());
        }
    }
    return temp;
    
    
}

std::set<Person*> MyPerson::sons() {
    std::set<Person*> temp;
    for (auto it = mychildren.begin(); it != mychildren.end(); ++it) {
        if ((*it) != NULL){
            if ((*it)->gender()==Gender::MALE)
                temp.insert(*it);
        }
    }
    return temp;
    
}

std::set<Person*> MyPerson::daughters() {
    std::set<Person*> temp;
    for (auto it = mychildren.begin(); it != mychildren.end(); ++it) {
        if ((*it) != NULL){
            if ((*it)->gender()==Gender::FEMALE)
                temp.insert(*it);
        }
    }
    return temp;
    
    
}

std::set<Person*> MyPerson::children() {
    std::set<Person*> temp;
    for (auto i = mychildren.begin(); i != mychildren.end(); ++i){
        temp.insert(*i);
        
    }
    return temp;
    
}

std::set<Person*> MyPerson::grandsons() {
    std::set<Person*> temp;
    for (auto it = mychildren.begin(); it != mychildren.end(); ++it) {
        if ((*it) != NULL){
            std::set<Person*> son_set = (*it)->sons();
            temp.insert(son_set.begin(), son_set.end());
        }
    }
    return temp;
    
}

std::set<Person*> MyPerson::granddaughters() {
    std::set<Person*> temp;
    for (auto it = mychildren.begin(); it != mychildren.end(); ++it) {
        if ((*it) != NULL){
            std::set<Person*> daughter_set = (*it)->daughters();
            temp.insert(daughter_set.begin(), daughter_set.end());
        }
    }
    return temp;
    
}

std::set<Person*> MyPerson::grandchildren() {
    std::set<Person*> temp;
    for (auto it = mychildren.begin(); it != mychildren.end(); ++it) {
        if ((*it) != NULL){
        std::set<Person*> children_set = (*it)->children();
        temp.insert(children_set.begin(), children_set.end());;
        }
    }
    return temp;
    
}

std::set<Person*> MyPerson::brothers(PMod pmod  , SMod smod  ) {
    std::set<Person*> sibling_set = siblings(pmod,smod);
      std::set<Person*> bro;
      for (auto it = sibling_set.begin(); it != sibling_set.end(); ++it) {
          if ((*it) != NULL){
              if ((*it)->gender()==Gender::MALE)
                  bro.insert(*it);
          }
      }
      return bro;
    
}

std::set<Person*> MyPerson::sisters(PMod pmod  , SMod smod  ) {
    std::set<Person*> sibling_set = siblings(pmod,smod);
    std::set<Person*> sis;
    for (auto it = sibling_set.begin(); it != sibling_set.end(); ++it) {
        if ((*it) != NULL){
            if ((*it)->gender()==Gender::FEMALE)
                sis.insert(*it);
        }
    }
    return sis;
    
}

std::set<Person*> MyPerson::siblings(PMod pmod  , SMod smod  ) {
    std::set<Person*>child_mother;
    std::set<Person*>child_father;
    std::set<Person*>me;
    me.insert(this);
    
    if (mymother!=NULL){
        child_mother = mymother->children() - me;
        
    }
    if (myfather!=NULL){
        child_father = myfather->children() - me;
    }
    std::set<Person*>any_sibling;
    
    
    switch (smod) {
        case SMod::FULL: {
            if ((mymother!= NULL) && (myfather== NULL))
                return child_mother;
            if ((myfather!= NULL) && (mymother== NULL))
                return child_father;
            
            std::set<Person*> intersection = (child_mother & child_father);
            return intersection;
            break;
        }
        case SMod::HALF:
            switch(pmod) {
                
                case PMod::MATERNAL:{
                    std::set<Person*> set_difference = (child_mother - (child_mother & child_father));
                    return set_difference;
                    break;
                }
                case PMod::PATERNAL:{
                    std::set<Person*> set_difference2 = (child_father - (child_mother & child_father));
                    return set_difference2;
                    break;
                }
                default:{
                    /*std::set_union(std::begin(child_mother), std::end(child_mother),std::begin(child_father), std::end(child_father),std::inserter(all,std::begin(all)));*/
                    std::set<Person*> uni = ((child_mother | child_father) - (child_mother & child_father));
                    return uni;
                    break;
                }
            }
            
        default:{
            switch(pmod) {
             
            case PMod::MATERNAL:
                return child_mother;
                break;
            
            case PMod::PATERNAL:
                return child_father;
                break;
            
            
            default: {
                std::set<Person*> uni = (child_mother | child_father);
                return uni;
                break;
            }
            }
           
            break;
    }
    }
    
    return (child_mother | child_father);
}

std::set<Person*> MyPerson::nieces(PMod pmod  , SMod smod  ) {
    std::set<Person*> sibling_set = siblings(pmod,smod);
    std::set<Person*> niece_set;
    std::set<Person*> temp;
      for (auto it = sibling_set.begin(); it != sibling_set.end(); ++it) {
          if ((*it) != NULL){
              niece_set = (*it)->daughters();
              temp.insert(niece_set.begin(), niece_set.end());
          }
      }
      return temp;
    
}

std::set<Person*> MyPerson::nephews(PMod pmod  , SMod smod  ) {
    std::set<Person*> sibling_set = siblings(pmod,smod);
    std::set<Person*> nephew_set;
    std::set<Person*> temp;
      for (auto it = sibling_set.begin(); it != sibling_set.end(); ++it) {
          if ((*it) != NULL){
              nephew_set=(*it)->sons();
              temp.insert(nephew_set.begin(), nephew_set.end());
          }
      }
      return temp;
    
}

std::set<Person*> MyPerson::aunts(PMod pmod  , SMod smod  ) {
    switch (pmod) {
        case PMod::MATERNAL:{
            if (mymother!=NULL)
                return mymother->sisters(PMod::ANY,smod);
            std::set<Person*> nullset;
            return nullset;
            break;
        }
            
        case PMod::PATERNAL: {
            if (myfather!=NULL)
                return myfather->sisters(PMod::ANY,smod);
            std::set<Person*> nullset;
            return nullset;
            break;
        }
            
        default:
            if ((mymother!=NULL) && (myfather!=NULL)) {
                std::set<Person*> uni = (mymother->sisters(PMod::ANY,smod) & myfather->sisters(PMod::ANY,smod));
                return uni;
            }
            else if ((mymother!=NULL)){
                return mymother->sisters(PMod::ANY,smod);
            }
            else if ((myfather!=NULL)){
                return myfather->sisters(PMod::ANY,smod);
            }
            
            std::set<Person*> nullset;
            return nullset;;
                
            break;
    }
    
}

std::set<Person*> MyPerson::uncles(PMod pmod  , SMod smod  ) {
    switch (pmod) {
        case PMod::MATERNAL:{
            if (mymother!=NULL){
                return mymother->brothers(PMod::ANY,smod);
            }
            std::set<Person*> nullset;
            return nullset;
            break;
        }
        
        case PMod::PATERNAL: {
            if (myfather!=NULL) {
                return myfather->brothers(PMod::ANY,smod);
            }
            std::set<Person*> nullset;
            return nullset;
            break;
        }
            
        default: {
            if ((mymother!=NULL) && (myfather!=NULL)) {
                std::set<Person*> uni = (mymother->sisters(PMod::ANY,smod) & myfather->brothers(PMod::ANY,smod));
                return uni;
            }
            else if ((mymother!=NULL)){
                return mymother->brothers(PMod::ANY,smod);
            }
            else if ((myfather!=NULL)){
                return myfather->brothers(PMod::ANY,smod);
            }
            
            std::set<Person*> nullset;
            return nullset;
            break;
        }
        
    }
}
    

std::set<Person*> MyPerson::cousins(PMod pmod  , SMod smod  ) {
    std::set<Person*> parents_siblings = (aunts(pmod,smod)) | (uncles(pmod,smod));
    std::set<Person*> cousin_set;
    std::set<Person*> temp;
    
    for (auto it = parents_siblings.begin(); it != parents_siblings.end(); ++it) {
        if ((*it) != NULL){
            
            cousin_set=(*it)->children();
            temp.insert(cousin_set.begin(), cousin_set.end());
        }
    }
    return temp;
    
}
//coming back
std::set<Person*> MyPerson::ancestors(PMod pmod  ) {
    std::set<Person*> parent_set = parents(pmod);
    std::set<Person*> temp;
    
   /* switch (pmod) {
        case PMod::MATERNAL:
            parent_set.insert(mymother);
            break;
        case PMod::PATERNAL:
            parent_set.insert(myfather);
            break;
        default:
            parent_set.insert(mymother);
            parent_set.insert(myfather);
            break;
    } */
    

    for (auto it = parent_set.begin(); it !=parent_set.end(); ++it) {
        if ((*it) != NULL){
            temp.insert(*it);
            std::set<Person*> temp2 = (*it)->ancestors(PMod::ANY);
            
            if (temp2.size() != 0){
                temp.insert(temp2.begin(), temp2.end());
            }
        }
        
    }
    return temp;
    
}

std::set<Person*> MyPerson::descendants() {
    std::set<Person*> descend = children();
    std::set<Person*> temp;
    std::set<Person*> temp2;
    for (auto it = descend.begin(); it !=descend.end(); ++it) {
        if ((*it) != NULL) {
            temp.insert(*it);
            std::set<Person*> temp2 = (*it)->descendants();
            }
    }
                         
    if (temp2.size() != 0){
                temp.insert(temp2.begin(), temp2.end());
            }
    return temp;
    
}

MyPerson::~MyPerson(){};
