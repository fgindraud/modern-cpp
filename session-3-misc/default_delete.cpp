#include <iostream>

using namespace std;

class MyClass {
  public:
    // MyClass() = default;

    MyClass(int a) { cout << "Got integer " << a << '\n'; }

    ~MyClass() { cout << "Am destructed\n"; }
};

int main() {
    // MyClass a;
    MyClass b(1);
    MyClass c(b);
}
