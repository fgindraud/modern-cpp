#include <iostream>
#include <vector>

class MyObject {
    int data;

  public:
    MyObject(int data) : data(data) { std::cout << "constructed(" << data << ")\n"; }
    MyObject(const MyObject& other) : data(other.data) { std::cout << "copied(" << data << ")\n"; }
};

int main() {
    std::vector<MyObject> v;
    v.push_back(MyObject(1));
    v.emplace_back(2);

    // TODO example with a list and a copy-deleted object?
}
