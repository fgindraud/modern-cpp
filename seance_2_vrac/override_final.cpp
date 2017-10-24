#include <iostream>

class IntInterface {
  public:
    virtual int value() const { return -1; };
};

class Int : public IntInterface {
    int data;

  public:
    explicit Int(int data) : data(data) {}
    int value() { return data; }
};

// class Zero : public Int {
// public:
//     Zero() : Int(0) {}
//     int value() const { return 0; }
// };

int main() {
    Int my_int(17);
    IntInterface *ptr = &my_int;  // implicit upcasting
    std::cout << ptr->value() << '\n';
}
