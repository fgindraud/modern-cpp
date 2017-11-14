#include <iostream>
// #include <memory>

class IntList {
    int value;
    IntList* rest{nullptr};
    // std::unique_ptr<IntList> rest;

  public:
    IntList(int value) : value(value) {}
    // IntList(int value, std::unique_ptr<IntList>& rest): value(value), rest(std::move(rest)) {}
    IntList(int value, IntList* rest) : value(value), rest(rest) {}

    void insert(int new_value) {
        // rest = std::unique_ptr<IntList>(new IntList(value, rest));
        // rest = std::make_unique<IntList>(value, rest); // C++14 only!
        rest = new IntList(value, rest);
        value = new_value;
    }

    int get_element() { return value; }

    IntList* next() {
        return rest;
        // return rest.get();
    }

    // IntList(const IntList&) = delete;
    // void operator=(const IntList&) = delete;

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
        std::cout << it->get_element() << '\n';
        it = it->next();
    }
}
