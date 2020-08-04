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

std::set<Person*> MyPerson::parents(PMod pmod = PMod::ANY) {
    std::set<Person*> temp;
    
    switch (pmod) {
        case PMod::MATERNAL:
            temp.insert(mymother);
            break;
            
        case PMod::PATERNAL:
            temp.insert(myfather);
            break;
            
        default:
            temp.insert(mymother);
            temp.insert(myfather);
            break;
    }
    return temp;
    
}

std::set<Person*> MyPerson::grandmothers(PMod pmod = PMod::ANY) {
    std::set<Person*> parent_set = parents(pmod);
    std::set<Person*> temp;
    
    for(auto it = parent_set.begin(); it != parent_set.end(); ++it){
        if (it != NULL) {
            std::set<Person*> temp2 = it->parents(PMod::MATERNAL);
            temp.insert(temp2.begin(),temp2.end());
        }
    }
    return temp;
    
    
}

std::set<Person*> MyPerson::grandfathers(PMod pmod = PMod::ANY) {
    std::set<Person*> parent_set = parents(pmod);
    std::set<Person*> temp;
    
    for(auto it = parent_set.begin(); it != parent_set.end(); ++it){
        if (it != NULL){
            std::set<Person*> temp2 = it->parents(PMod::PATERNAL);
            temp.insert(temp2.begin(),temp2.end());
        }
    }
    return temp;
    
    
}

std::set<Person*> MyPerson::grandparents(PMod pmod = PMod::ANY) {
    std::set<Person*> parent_set = parents(pmod);
    std::set<Person*> temp;
    
    for(auto it = parent_set.begin(); it != parent_set.end(); ++it){
        if (it != NULL){
            std::set<Person*> temp2 = it->parents(PMod::ANY);
            temp.insert(temp2.begin(),temp2.end());
        }
    }
    return temp;
    
    
}

std::set<Person*> MyPerson::sons() {
    std::set<Person*> temp;
    for (auto it = mychildren.begin(); it != mychildren.end(); ++it) {
        if (it != NULL){
            if (it->gender()==Gender::MALE)
                temp.insert(it);
        }
    }
    return temp;
    
}

std::set<Person*> MyPerson::daughters() {
    std::set<Person*> temp;
    for (auto it = mychildren.begin(); it != mychildren.end(); ++it) {
        if (it != NULL){
            if (it->gender()==Gender::FEMALE)
                temp.insert(it);
        }
    }
    return temp;
    
    
}

std::set<Person*> MyPerson::children() {
    return mychildren;
    
}

std::set<Person*> MyPerson::grandsons() {
    std::set<Person*> temp;
    for (auto it = mychildren.begin(); it != mychildren.end(); ++it) {
        if (it != NULL){
            temp.insert(it->sons());
        }
    }
    return temp;
    
}

std::set<Person*> MyPerson::granddaughters() {
    std::set<Person*> temp;
    for (auto it = mychildren.begin(); it != mychildren.end(); ++it) {
        if (it != NULL){
            temp.insert(it->daughters());
        }
    }
    return temp;
    
}

std::set<Person*> MyPerson::grandchildren() {
    std::set<Person*> temp;
    for (auto it = mychildren.begin(); it != mychildren.end(); ++it) {
        if (it != NULL){
        temp.insert(it->children());
        }
    }
    return temp;
    
}

std::set<Person*> MyPerson::brothers(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
    std::set<Person*> sibling_set = siblings(pmod,smod);
      std::set<Person*> bro;
      for (auto it = sibling_set.begin(); it != sibling_set.end(); ++it) {
          if (it != NULL){
              if (it->gender()==Gender::MALE)
                  bro.insert(it);
          }
      }
      return bro;
    
}

std::set<Person*> MyPerson::sisters(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
    std::set<Person*> sibling_set = siblings(pmod,smod);
    std::set<Person*> sis;
    for (auto it = sibling_set.begin(); it != sibling_set.end(); ++it) {
        if (it != NULL){
            if (it->gender()==Gender::FEMALE)
                sis.insert(it);
        }
    }
    return sis;
    
}

std::set<Person*> MyPerson::siblings(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
    std::set<Person*>child_mother = mymother->children();
    std::set<Person*>child_father = myfather->children();
    std::set<Person*>any_sibling;
    
    
    switch (smod) {
        case SMod::FULL:
            if ((child_mother!= NULL) && (child_father!= NULL))
                return child_mother;
            if ((child_father!= NULL) && (child_mother!= NULL))
                return child_father;
            
            std::set<Person*> intersection = (child_mother & child_father);
            return intersection;
            break;
        case SMod::HALF:
            switch(pmod) {
                 
                //std::set<Person*> all;
                    
                case PMod::MATERNAL:
                    std::set<Person*> set_difference = (child_mother - (child_mother & child_father));
                    return set_difference;
                    break;
                
                case PMod::PATERNAL:
                    std::set<Person*> set_difference2 = (child_father - (child_mother & child_father));
                    return set_difference2;
                    break;
                
                default:
                    /*std::set_union(std::begin(child_mother), std::end(child_mother),std::begin(child_father), std::end(child_father),std::inserter(all,std::begin(all)));*/
                    std::set<Person*> uni = ((child_mother | child_father) - (child_mother & child_father));
                    return uni;
                    break;
                    
            }
            
        default:
            switch(pmod) {
             
            case PMod::MATERNAL:
                return child_mother;
                break;
            
            case PMod::PATERNAL:
                return child_father;
                break;
            
            default:
                std::set<Person*> uni = (child_mother | child_father);
                return uni;
                break;
            }
           
            break;
    }
    
    
}

std::set<Person*> MyPerson::nieces(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
    std::set<Person*> sibling_set = siblings(pmod,smod);
    std::set<Person*> niece_set;
      for (auto it = sibling_set.begin(); it != sibling_set.end(); ++it) {
          if (it != NULL){
              niece_set.insert(it->daughters());
          }
      }
      return niece_set;
    
}

std::set<Person*> MyPerson::nephews(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
    std::set<Person*> sibling_set = siblings(pmod,smod);
    std::set<Person*> nephew_set;
      for (auto it = sibling_set.begin(); it != sibling_set.end(); ++it) {
          if (it != NULL){
              nephew_set.insert(it->sons());
          }
      }
      return nephew_set;
    
}

std::set<Person*> MyPerson::aunts(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
    switch (pmod) {
        case PMod::MATERNAL:
            if (mymother!=NULL)
                return mymother->sisters(PMod::ANY,smod);
            return NULL;
            break;
            
        case PMod::PATERNAL:
            if (myfather!=NULL)
                return myfather->sisters(PMod::ANY,smod);
            return NULL;
            break;
            
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
            
            return NULL;
                
            break;
    }
    
}

std::set<Person*> MyPerson::uncles(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
    switch (pmod) {
        case PMod::MATERNAL:
            if (mymother!=NULL)
                return mymother->brothers(PMod::ANY,smod);
            return NULL;
            break;
            
        case PMod::PATERNAL:
            if (myfather!=NULL)
                return myfather->brothers(PMod::ANY,smod);
            return NULL;
            break;
            
        default:
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
            
            return NULL;
                
            break;
    }
    
}

std::set<Person*> MyPerson::cousins(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
    std::set<Person*> parents_siblings = (aunts(pmod,smod)) | (uncles(pmod,smod));
    std::set<Person*> cousin_set;
    
    for (auto it = parents_siblings.begin(); it != parents_sibling.end(); ++it) {
        if (it != NULL){
            cousin_set.insert(it->children());
        }
    }
    return cousin_set;
    
}
//coming back
std::set<Person*> MyPerson::ancestors(PMod pmod = PMod::ANY) {
    std::set<Person*> parent_set = parents(pmod);
    std::set<Person*> temp;
    
    switch (pmod) {
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
    }
    

    for (auto it = parent_set.begin(); it !=parent_set.end(); ++it) {
        if (it != NULL){
            temp.insert(it);
            temp.insert(it->ancestors(PMod::ANY));
            }
    
    }
    if temp.size() != 0
        return temp;
    return NULL;
    
    
}

std::set<Person*> MyPerson::descendants() {
    std::set<Person*> descend = children();
    std::set<Person*> temp;
    for (auto it = descend.begin(); it !=descend(); ++it) {
        if (it != NULL) {
            temp.insert(it->descendants());
            }
    }
    if temp.size() != 0
        return temp;
    return NULL;
    
}