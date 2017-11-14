#include <iostream>
#include <memory>
using std::cout;

struct MyInt {
    MyInt(int value) : value(value) {}
    int value;
};

int main() {
    std::unique_ptr<MyInt> p1(new MyInt(3));
    // auto p1 = std::unique_ptr<MyInt>(new MyInt(3)); // equivalent to line above
    // cout << p1->value << '\n';

    auto p2 = std::make_unique<MyInt>(5);  // C++14 only!
    // cout << p2->value << '\n';

    MyInt* ptr = p2.get();
    // cout << ptr->value << '\n';

    auto p3 = std::move(p2);
    // cout << p2->value << ", ";
    // cout << p3->value << ", " << ptr->value << '\n';
}
