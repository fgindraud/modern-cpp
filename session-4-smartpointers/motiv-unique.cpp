#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <numeric>
#include <vector>
#include <memory>

struct Animal {
    virtual int nb_legs() = 0;
    virtual ~Animal() = default;
};

struct Panda : public Animal {
    virtual int nb_legs() override { return 4; }
};

struct Spider : public Animal {
    virtual int nb_legs() override { return 8; }
};

class GroupOfAnimals {
    // std::vector<Animal*> animals;
    std::vector<std::unique_ptr<Animal>> animals;

  public:
    GroupOfAnimals(int number) {
        for (int i = 0; i < number; i++)
            if (rand() % 2 == 1)
                animals.emplace_back(new Spider());
                // animals.push_back(new Spider());
            else
                animals.emplace_back(new Panda());
                // animals.push_back(new Panda());
    }

    int nb_legs() {
        int acc = 0;
        // for (auto ptr : animals) {
        //     acc += ptr->nb_legs();
        // }
        for (auto& ptr : animals) {
            acc += ptr->nb_legs();
        }
        return acc;
    }

    // ~GroupOfAnimals() {
    //     for (auto ptr : animals) {
    //         delete ptr;
    //     }
    // }
};

int main() {
    srand(time(NULL));

    GroupOfAnimals group(50);
    std::cout << group.nb_legs() << '\n';
}
