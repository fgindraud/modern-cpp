#include <iostream>
#include <random>

int main() {
    std::random_device rd;   // default random generator...
    std::mt19937 gen(rd());  // ...used to seed a Mersenne twister

    std::normal_distribution<> distrib(5, 2); // declaring the distribution

    for (int i=0; i<10; i++) {
        std::cout << distrib(gen) << '\n';
    }
}
