#include <iostream>
#include <vector>
#include <list>
using namespace std;

class IntCounter {
    int data{0};

public:
    int get() { return ++data; }
    // IntCounter() = default;
    // IntCounter(const IntCounter&) = delete;
// private:
//     IntCounter(const IntCounter&) = default;
};

class Hello {
    IntCounter& counter;

public:
    Hello(IntCounter& counter) : counter(counter) {}

    void hello() {
        cout << "Hello " << counter.get() << '\n';
    }
};


int main() {
    IntCounter w;
    // vector<IntCounter> wv;
    // wv.push_back(IntCounter());
    // wv.emplace_back();
    // auto& w = wv.back();

    // list<IntCounter> wl;
    // wl.emplace_front();
    // auto& w = wl.front();

    Hello h(w);
    Hello h2(w);
    h.hello();
    h2.hello();

    // wv.push_back(IntCounter());
    // wv.emplace_back();
    // wl.emplace_front();

    h.hello();
    h2.hello();
}

// BONUS
// class MyFancyInterface {
//     virtual void some_fancy_virtual_thing() = 0;
//     ~MyFancyInterface() = default;
// };
