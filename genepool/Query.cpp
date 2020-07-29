#include "Query.h"
#include "Person.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>

// This file provides query parsing and execution.
// You can edit it if you want, but you shouldn't need to.
// Gradescope will use the original version.


// Helper function that throws an error if a read fails:
void read_term(std::istream& stream, std::string& term) {
  if(!(stream >> term)) {
    throw std::invalid_argument("Too few terms in query.");
  }
}

// Construct a query by parsing text:
Query::Query(const std::string& text) {
  std::istringstream stream(text);

  pmod = PMod::ANY;
  smod = SMod::ANY;

  std::string term;
  read_term(stream, name);
  read_term(stream, term);

  // Translate underscores to spaces:
  std::replace(name.begin(), name.end(), '_', ' ');

  size_t pos = name.length() - 2;
  if(name.find("'s", pos) == pos) {
    name = name.substr(0, pos);
  }

  if(term == "maternal") {
    pmod = PMod::MATERNAL;
    read_term(stream, term);
  }
  else if(term == "paternal") {
    pmod = PMod::PATERNAL;
    read_term(stream, term);
  }

  if(term == "full") {
    smod = SMod::FULL;
    read_term(stream, term);
  }
  else if(term == "half") {
    smod = SMod::HALF;
    read_term(stream, term);
  }

  relationship = term;
  if(stream >> term) {
    throw std::invalid_argument("Too many terms in query.");
  }

  validate();
}

// Construct a query directly:
Query::Query(const std::string& name, const std::string& relationship, PMod pmod, SMod smod) {
  this->name         = name;
  this->relationship = relationship;
  this->pmod         = pmod;
  this->smod         = smod;

  validate();
}

// Run a query against a gene pool:
std::set<Person*> Query::run(const GenePool& pool) const {
  Person* person = pool.find(name);
  if(person == nullptr) {
    throw std::invalid_argument("No such person: " + name);
  }

  if(relationship == "ancestors") {
    return person->ancestors(pmod);
  }
  else if(relationship == "aunts") {
    return person->aunts(pmod, smod);
  }
  else if(relationship == "brothers") {
    return person->brothers(pmod, smod);
  }
  else if(relationship == "children") {
    return person->children();
  }
  else if(relationship == "cousins") {
    return person->cousins(pmod, smod);
  }
  else if(relationship == "daughters") {
    return person->daughters();
  }
  else if(relationship == "descendants") {
    return person->descendants();
  }
  else if(relationship == "father") {
    Person* father = person->father();
    std::set<Person*> result;
    if(father != nullptr) {
      result.insert(father);
    }

    return result;
  }
  else if(relationship == "grandchildren") {
    return person->grandchildren();
  }
  else if(relationship == "granddaughters") {
    return person->granddaughters();
  }
  else if(relationship == "grandfathers") {
    return person->grandfathers(pmod);
  }
  else if(relationship == "grandmothers") {
    return person->grandmothers(pmod);
  }
  else if(relationship == "grandparents") {
    return person->grandparents(pmod);
  }
  else if(relationship == "grandsons") {
    return person->grandsons();
  }
  else if(relationship == "mother") {
    Person* mother = person->mother();
    std::set<Person*> result;
    if(mother != nullptr) {
      result.insert(mother);
    }

    return result;
  }
  else if(relationship == "nephews") {
    return person->nephews(pmod, smod);
  }
  else if(relationship == "nieces") {
    return person->nieces(pmod, smod);
  }
  else if(relationship == "parents") {
    return person->parents(pmod);
  }
  else if(relationship == "siblings") {
    return person->siblings(pmod, smod);
  }
  else if(relationship == "sisters") {
    return person->sisters(pmod, smod);
  }
  else if(relationship == "sons") {
    return person->sons();
  }
  else if(relationship == "uncles") {
    return person->uncles(pmod, smod);
  }
  else {
    throw std::invalid_argument("Unknown relationship: " + relationship);
  }
}

void Query::validate(bool allow_pmod, bool allow_smod) const {
  if(allow_pmod == false && pmod != PMod::ANY) {
    throw std::invalid_argument("Parent modifier is not allowed in " + relationship + " queries.");
  }

  if(allow_smod == false && smod != SMod::ANY) {
    throw std::invalid_argument("Sibling modifier is not allowed in " + relationship + " queries.");
  }
}

void Query::validate() const {
  if(relationship == "ancestors") {
    validate(true, false);
  }
  else if(relationship == "aunts") {
    validate(true, true);
  }
  else if(relationship == "brothers") {
    validate(true, true);
  }
  else if(relationship == "children") {
    validate(false, false);
  }
  else if(relationship == "cousins") {
    validate(true, true);
  }
  else if(relationship == "daughters") {
    validate(false, false);
  }
  else if(relationship == "descendants") {
    validate(false, false);
  }
  else if(relationship == "father") {
    validate(false, false);
  }
  else if(relationship == "grandchildren") {
    validate(false, false);
  }
  else if(relationship == "granddaughters") {
    validate(false, false);
  }
  else if(relationship == "grandfathers") {
    validate(true, false);
  }
  else if(relationship == "grandmothers") {
    validate(true, false);
  }
  else if(relationship == "grandparents") {
    validate(true, false);
  }
  else if(relationship == "grandsons") {
    validate(false, false);
  }
  else if(relationship == "mother") {
    validate(false, false);
  }
  else if(relationship == "nephews") {
    validate(true, true);
  }
  else if(relationship == "nieces") {
    validate(true, true);
  }
  else if(relationship == "parents") {
    validate(true, false);
  }
  else if(relationship == "siblings") {
    validate(true, true);
  }
  else if(relationship == "sisters") {
    validate(true, true);
  }
  else if(relationship == "sons") {
    validate(false, false);
  }
  else if(relationship == "uncles") {
    validate(true, true);
  }
  else {
    throw std::invalid_argument("Unknown relationship: " + relationship);
  }
}

// Generate a query string:
std::string Query::to_string() const {
  std::string result = name + "'s ";

  if(this->pmod == PMod::MATERNAL) {
    result += "maternal ";
  }
  else if(this->pmod == PMod::PATERNAL) {
    result += "paternal ";
  }

  if(this->smod == SMod::FULL) {
    result += "full ";
  }
  else if(this->smod == SMod::HALF) {
    result += "half ";
  }

  result += relationship;
  return result;
}
