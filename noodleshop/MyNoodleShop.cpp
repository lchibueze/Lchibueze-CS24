#include "MyNoodleShop.h"

// This is here to avoid creating yet another object file.
NoodleShop* NoodleShop::create(int npots, int rent, int customers, std::vector<Noodle> noodles) {
  return new MyNoodleShop(/* TODO */);
}


// MyNoodleShop Member Functions
