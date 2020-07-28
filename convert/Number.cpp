#include "Number.h"
#include <string>
#include <sstream>

// Implement Number member functions here.

Number::Number(const std::string& token){
    Dnum = std::stod(token);
}

//Required helper functions.

int Number::arity() const {
    return 0;
}
int Number::associativity() const {
    return 0;
}

int Number::precedence() const {
    return 4;
}

// Required member functions.
std::string Number::infix() const {
    return to_string ();
}
std::string Number::postfix() const {
    return to_string();
}
std::string Number::prefix()  const {
    return to_string();
}

std::string Number::to_string() const {
    std::ostringstream stream;
    stream<<Dnum;
    return stream.str();
}
