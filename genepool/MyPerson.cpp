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
        std::set<Person*> temp2 = it->parents(PMod::MATERNAL);
        temp.insert(temp2.begin(),temp2.end());
    }
    return temp;
    
    
}

std::set<Person*> MyPerson::grandfathers(PMod pmod = PMod::ANY) {
    std::set<Person*> parent_set = parents(pmod);
    std::set<Person*> temp;
    
    for(auto it = parent_set.begin(); it != parent_set.end(); ++it){
        std::set<Person*> temp2 = it->parents(PMod::PATERNAL);
        temp.insert(temp2.begin(),temp2.end());
    }
    return temp;
    
    
}

std::set<Person*> MyPerson::grandparents(PMod pmod = PMod::ANY) {
    std::set<Person*> parent_set = parents(pmod);
    std::set<Person*> temp;
    
    for(auto it = parent_set.begin(); it != parent_set.end(); ++it){
        std::set<Person*> temp2 = it->parents(PMod::ANY);
        temp.insert(temp2.begin(),temp2.end());
    }
    return temp;
    
    
}

std::set<Person*> MyPerson::sons() {
    std::set<Person*> temp;
    for (auto it = mychildren.begin(); it != mychildren.end(); ++it) {
        if (it->gender()==Gender::MALE)
            temp.insert(it);
    }
    return temp;
    
}

std::set<Person*> MyPerson::daughters() {
    std::set<Person*> temp;
    for (auto it = mychildren.begin(); it != mychildren.end(); ++it) {
        if (it->gender()==Gender::FEMALE)
            temp.insert(it);
    }
    return temp;
    
    
}

std::set<Person*> MyPerson::children() {
    return mychildren;
    
}

std::set<Person*> MyPerson::grandsons() {
    std::set<Person*> temp;
    for (auto it = mychildren.begin(); it != mychildren.end(); ++it) {
        temp.insert(it->sons());
    }
    return temp;
    
}

std::set<Person*> MyPerson::granddaughters() {
    std::set<Person*> temp;
    for (auto it = mychildren.begin(); it != mychildren.end(); ++it) {
        temp.insert(it->daughters());
    }
    return temp;
    
}

std::set<Person*> MyPerson::grandchildren() {
    std::set<Person*> temp;
    for (auto it = mychildren.begin(); it != mychildren.end(); ++it) {
        temp.insert(it->children());
    }
    return temp;
    
}

std::set<Person*> MyPerson::brothers(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
    
}

std::set<Person*> MyPerson::sisters(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
    
}

std::set<Person*> MyPerson::siblings(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
    std::set<Person*>child_mother = mymother->children();
    std::set<Person*>child_father = myfather->children();
    std::set<Person*>any_sibling;
    

    std::vector<Person*> v_child_mother(child_mother.begin(), child_mother.end());
        
    std::vector<Person*> v_child_father(child_father.begin(), child_father.end());
        
    std::sort(v_child_mother.begin(), v_child_mother.end());
    std::sort(v_child_father.begin(), v_child_father.end());
    
    std::vector<Person*> intersect;
        
    std::set_intersection(v_child_mother.begin(), v_child_mother.end(), v_child_father.begin(), v_child_father.end(), std::back_inserter(intersect));
    
    
        

   // std::set<Person*> all;
    
    switch (smod) {
        case SMod::FULL:
            std::set<Person*> temp (intersect.begin(),intersect.end());
            return temp;
            break;
        case SMod::HALF:
            switch(pmod) {
                 
                std::set<Person*> all;
                    
                case PMod::MATERNAL:
                    return child_mother;
                    break;
                
                case PMod::PATERNAL:
                    return child_father;
                    break;
                
                default:
                    std::set_union(std::begin(child_mother), std::end(child_mother),std::begin(child_father), std::end(child_father),std::inserter(all,std::begin(all)));
                    return all;
                    break;
                    
            }
            
        default:
            
            break;
    }
    
    
    
}

std::set<Person*> MyPerson::nieces(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
    
}

std::set<Person*> MyPerson::nephews(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
    
}

std::set<Person*> MyPerson::aunts(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
    
}

std::set<Person*> MyPerson::uncles(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
    
}

std::set<Person*> MyPerson::cousins(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) {
    
}

std::set<Person*> MyPerson::ancestors(PMod pmod = PMod::ANY) {
    
}

std::set<Person*> descendants() {
    
}
