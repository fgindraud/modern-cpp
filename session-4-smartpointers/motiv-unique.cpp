#include <iostream>
#include <memory>

class IntList {
    int value;
    // IntList* rest;
    std::unique_ptr<IntList> rest;

  public:
    IntList(int value) : value(value) {}
    IntList(int value, std::unique_ptr<IntList>& rest) : value(value), rest(std::move(rest)) {}

    void insert(int new_value) {
        rest = std::unique_ptr<IntList>(new IntList(value, rest));
        value = new_value;
    }

    int get() { return value; }

    IntList* next() { return rest.get(); }

    // ~IntList() {
    //     delete rest;
    // }
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
