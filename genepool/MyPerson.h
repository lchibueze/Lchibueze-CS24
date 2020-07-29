#ifndef MYPERSON_H
#define MYPERSON_H

#include "Person.h"

class MyPerson: public Person {
  // Member Variables

public:
  // Constructor
  // Destructor?

  // Required Functions
  const std::string& name()   const;
  Gender             gender() const;
  MyPerson*          mother();
  MyPerson*          father();

  // Required Relationship Functions
  std::set<Person*> ancestors(PMod pmod = PMod::ANY);
  std::set<Person*> aunts(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> brothers(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> children();
  std::set<Person*> cousins(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> daughters();
  std::set<Person*> descendants();
  std::set<Person*> grandchildren();
  std::set<Person*> granddaughters();
  std::set<Person*> grandfathers(PMod pmod = PMod::ANY);
  std::set<Person*> grandmothers(PMod pmod = PMod::ANY);
  std::set<Person*> grandparents(PMod pmod = PMod::ANY);
  std::set<Person*> grandsons();
  std::set<Person*> nephews(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> nieces(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> parents(PMod pmod = PMod::ANY);
  std::set<Person*> siblings(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> sisters(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);
  std::set<Person*> sons();
  std::set<Person*> uncles(PMod pmod = PMod::ANY, SMod smod = SMod::ANY);

  // Other Member Functions
};

#endif
