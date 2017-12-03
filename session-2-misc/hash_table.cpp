// Since C++11, we have hash sets and hash maps.

#include <unordered_map>
#include <unordered_set>

#include <iostream>
#include <string>

int main() {
    // Similar API as std::set and std::map
    std::unordered_map<std::string, int> table;
    table.emplace("blah", 42);
    table.emplace("hello", 0);

    auto it = table.find("blah");
    if (it != table.end()) std::cout << "table['blah']=" << it->second << "\n";

    auto it2 = table.find("zzz");
    if (it2 == table.end()) std::cout << "table['zzz'] not found\n";

    return 0;
}

// Custom key
struct MyInt {
    int v;
};

#ifdef FAILS
// Fails to compile: must explain to stdlib how to hash and test equality
std::unordered_map<MyInt, int> table;
#endif

#ifdef GLOBAL
// Define hash and equality for everyone

bool operator==(const MyInt& l, const MyInt& r) { return l.v == r.v; }

namespace std {
    // Specialise std::hash class
    template <>
    struct hash<MyInt> {
        std::size_t operator()(const MyInt& i) const {
            // Usually defined by calling std::hash for values in key type and combining the hashes
            return std::hash<int>()(i.v);
            // Here only one sub hash, no combination required
            // cppreference page for std::hash gives examples of hash combinations
            // (uses xor and other bit manipulations)
        }
    };
}  // namespace std

std::unordered_map<MyInt, int> table;
#endif

#ifdef LOCAL
// Define hash and equality in "customization classes" used only in some map instances

struct MyIntEquality {
    bool operator()(const MyInt& l, const MyInt& r) const { return l.v == r.v; }
};

struct MyIntHash {
    // Same code as std::hash version above
    std::size_t operator()(const MyInt& i) const { return std::hash<int>()(i.v); }
};

// customized map. non hash std::map/std::set also have customizations
std::unordered_map<MyInt, int, MyIntHash, MyIntEquality> table;

// Can be partially customized too: global operator== + custom MyIntHash is a common case
#endif
