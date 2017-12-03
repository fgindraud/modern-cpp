#include <iostream>
#include <type_traits>
#include <typeinfo>

struct NoisyInt {
    int v;
    NoisyInt(int i) : v(i) { std::cout << "create " << v << "\n"; }
    NoisyInt(const NoisyInt &i) : v(i.v) { std::cout << "copy " << v << "\n"; }
    NoisyInt &operator=(const NoisyInt &i) {
        v = i.v;
        std::cout << "assign " << v << "\n";
        return *this;
    }
};

template <typename T>
void show_type(const std::string name) {
    std::cout << name << ": ";
    if (std::is_same<T, NoisyInt>::value) {
        std::cout << "NoisyInt";
    } else if (std::is_same<T, const NoisyInt &>::value) {
        std::cout << "const NoisyInt&";
    } else if (std::is_same<T, NoisyInt &>::value) {
        std::cout << "NoisyInt&";
    } else if (std::is_same<T, NoisyInt &&>::value) {
        std::cout << "NoisyInt&&";
    } else if (std::is_same<T, const NoisyInt *>::value) {
        std::cout << "const NoisyInt*";
    } else if (std::is_same<T, NoisyInt *>::value) {
        std::cout << "NoisyInt*";
    } else {
        std::cout << "Unknown";
    }
    std::cout << "\n";
}

int main() {
    // Create a value, a ref, a const_ref
    NoisyInt value{1};
    NoisyInt const_ref_value{2};
    const NoisyInt &const_ref = const_ref_value;
    NoisyInt ref_value{3};
    NoisyInt &ref = ref_value;

#ifdef AUTO  // Build values (non references) from input
    auto a = value;
    auto b = const_ref;
    auto c = ref;
    auto d = NoisyInt(4);
#endif

#ifdef AUTO_REF  // Build mutable references from input
    auto &a = value;
    auto &b = const_ref;
    auto &c = ref;
    auto &d = NoisyInt(4);  // Fails on temporary
#endif

#ifdef AUTO_CONST_REF  // Build const reference from input
    const auto &a = value;
    const auto &b = const_ref;
    const auto &c = ref;
    const auto &d = NoisyInt(4);  // const reference to temporary value
#endif

#ifdef AUTO_UNIV_REF  // universal reference, binds to everything in the most permissive way
    auto &&a = value;
    auto &&b = const_ref;
    auto &&c = ref;
    auto &&d = NoisyInt(4);  // reference to temporary value (move semantics)
#endif

#ifdef AUTO_PTR  // binds to pointers ONLY, by value
    auto *a = &value;
    auto *b = &const_ref;
    auto *c = &ref;
    auto *d = &NoisyInt(4);  // Fails
    auto *e = 42;            // Fails, not a pointer
#endif

#ifdef AUTO_PTR_IMPLICIT  // will bind to pointers, but not checked
    auto a = &value;
    auto b = &const_ref;
    auto c = &ref;
    auto d = &NoisyInt(4);  // Fails
    auto e = 42;            // Ok, an int
#endif

    show_type<decltype(a)>("a");
    show_type<decltype(b)>("b");
    show_type<decltype(c)>("c");
#if defined(AUTO) || defined(AUTO_CONST_REF) || defined(AUTO_UNIV_REF)
    show_type<decltype(d)>("d");
#endif
    return 0;
}
