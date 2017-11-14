#include <iostream>

class IntList {
    int value;
    IntList* rest;

  public:
    IntList(int value, IntList* rest = nullptr) : value(value), rest(rest) {}

    void insert(int new_value) {
        rest = new IntList(value, rest);
        value = new_value;
    }

    int get() { return value; }

    IntList* next() { return rest; }

    ~IntList() {
        delete rest;
    }
};

int main() {
    IntList l(1);
    l.insert(3);
    l.insert(17);

    auto it = &l;
    while (it != nullptr) {
        std::cout << it->get() << '\n';
        it = it->next();
    }
}
