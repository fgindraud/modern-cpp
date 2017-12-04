// Typedefs can now be done with the using syntax

// These are equivalent:
typedef int IntTypedef;
using IntTypedef2 = int;

// 'using' is clearer and less error prone than 'typedef'
// Especially for function pointer types:
typedef bool (*IntPredicateTypedef)(int);
using IntPredicateTypedef2 = bool (*)(int);
