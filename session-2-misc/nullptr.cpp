#include <iostream>

using namespace std;

void f(int*) {
    cout << "char pointer\n";
}

void f(int) {
    cout << "int\n";
}


int main() {
    int i = 12;
    f(i);
    // f(NULL);
    f(nullptr);
}
