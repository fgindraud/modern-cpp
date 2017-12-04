#include <iostream>

class ThreeFloats {
    float f0, f1, f2;

  public:
    ThreeFloats(float f0, float f1, float f2) : f0(f0), f1(f1), f2(f2) {}

  private:
    struct Iter {
        int index;
        ThreeFloats& container;

        bool operator!=(const Iter& it) {
            return (it.index != index) or (&it.container != &container);
        }

        float operator*() {
            if (index == 0)
                return container.f0;
            else if (index == 1)
                return container.f1;
            else
                return container.f2;
        }

        void operator++() { index++; }
    };

  public:
    Iter begin() {
        Iter it = {0, *this};
        return it;
    }

    Iter end() {
        Iter it = {3, *this};
        return it;
    }
};

int main() {
    ThreeFloats ff(1.2, 2.3, 17.17);
    for (auto f : ff) {
        std::cout << f << '\n';
    }
}
