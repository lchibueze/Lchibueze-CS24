#include <iostream>

using namespace std;

int main() {
    string name;
    getline (cin,name);
    name = string (name.rbegin (), name.rend ());
    cout <<"!" <<name << " ,olleH" << "\n";
    return 0;
}
