#ifndef PERSON_H
#define PERSON_H

#include <set>
#include <string>

// This file describes the Person interface you need to implement.
// Don't edit this!  Your code goes in the MyPerson.* files.


// Type to represent gender.
enum class Gender {
  MALE,
  FEMALE,
  ANY
};

// Type to represent parent modifiers.
enum class PMod {
  MATERNAL,
  PATERNAL,
  ANY
};

// Type to represent sibling modifiers.
enum class SMod {
  FULL,
  HALF,
  ANY
};


class Person {
public:
  // Required functions:
  virtual const std::string& name()   const = 0;
  virtual Gender             gender() const = 0;
  virtual Person*            mother() = 0;
  virtual Person*            father() = 0;

  // Required relationship queries (see the readme for details):
  virtual std::set<Person*> ancestors(PMod pmod = PMod::ANY) = 0;
  virtual std::set<Person*> aunts(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) = 0;
  virtual std::set<Person*> brothers(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) = 0;
  virtual std::set<Person*> children() = 0;
  virtual std::set<Person*> cousins(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) = 0;
  virtual std::set<Person*> daughters() = 0;
  virtual std::set<Person*> descendants() = 0;
  virtual std::set<Person*> grandchildren() = 0;
  virtual std::set<Person*> granddaughters() = 0;
  virtual std::set<Person*> grandfathers(PMod pmod = PMod::ANY) = 0;
  virtual std::set<Person*> grandmothers(PMod pmod = PMod::ANY) = 0;
  virtual std::set<Person*> grandparents(PMod pmod = PMod::ANY) = 0;
  virtual std::set<Person*> grandsons() = 0;
  virtual std::set<Person*> nephews(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) = 0;
  virtual std::set<Person*> nieces(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) = 0;
  virtual std::set<Person*> parents(PMod pmod = PMod::ANY) = 0;
  virtual std::set<Person*> siblings(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) = 0;
  virtual std::set<Person*> sisters(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) = 0;
  virtual std::set<Person*> sons() = 0;
  virtual std::set<Person*> uncles(PMod pmod = PMod::ANY, SMod smod = SMod::ANY) = 0;

  // Don't forget!
  virtual ~Person() {}
};

#endif
