#include <iostream>

using namespace std;

int main(int ac, char** av) {
    string name = av[1];
    name = string (name.rbegin (), name.rend ());
    cout <<"!" <<name << " ,olleH" << "\n";
    return 0;
}
