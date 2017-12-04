#include <iostream>

using namespace std;

void f(int*) { cout << "int array\n"; }

void f(long) { cout << "long\n"; }

void f(int) { cout << "int\n"; }

int main() {
    int i = 12;
    int* table = new int[7];

    f(i);
    f(table);
    f(NULL);
    // f(nullptr);
}
