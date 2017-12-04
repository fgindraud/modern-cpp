#include <iostream>
#include <vector>
#include <list>

class MyObject {
    int data;

  public:
    MyObject(int data) : data(data) { std::cout << "constructed(" << data << ")\n"; }
    MyObject(const MyObject& other) : data(other.data) { std::cout << "copied(" << data << ")\n"; }
    // MyObject(const MyObject&) = delete;
};

int main() {
    std::vector<MyObject> v;
    v.reserve(10);
    v.push_back(MyObject(17));
    v.emplace_back(3);

    // std::list<MyObject> l;
    // l.push_front(MyObject(1));
    // l.emplace_front(2);
}
