# Session 2

## Langage

### List initialization
New syntax to initialize objects using curly braces.
It is really useful to initialize data structures such as vectors with explicit data.

Example file: [init_list.cpp](init_list.cpp)

### Range-based `for`
C++11 introduced a new syntax to go through the elements of a data structure using a for loop.
This new syntax is a lot shorter, especially combined with the use of auto.

Example files [for_range.cpp](for_range.cpp) (basic example) ans [for_range_custom.cpp](for_range_custom.cpp) (custom data structure)

### `override` / `final`
Keywords used to ensure that a method correctly overwrites a virtual method of a parent class.

Example file: [override_final.cpp](override_final.cpp)

### `default` / `delete`
Keywords used to ensure a specific member function is present in its default version (with `default`) or forbidden (with `delete`).
This is particularly useful when dealing with multiple constructors.

Example file: [default_delete.cpp](default_delete.cpp)

### `nullptr`
New pointer literal that denotes an unitialized or invalid pointer.
Should be used instead of `0` or `NULL`.
`nullptr` is a lot safer and helps avoiding weird typing bugs.

Example file: [nullptr.cpp](nullptr.cpp)

### `using` syntax for typedef
An improved syntax is available for typedef statements: [typedef.cpp](typedef.cpp).

### `noexcept`
`throw(...)` specifications have been replaced by `noexcept`: [noexcept.cpp](noexcept.cpp).


## Standard library

### Hash tables
C++11 added `std::unordered_set` and `std::unordered_map`, hash table variants of `std::set` and `std::map`.
Basic map/set API is similar. Small example file: [hash_table.cpp](hash_table.cpp)

### Sampling from distributions
C++11 greatly expands the random number generation compared to older C++.
New functions range from low-level specification of random engines to functions to draw into common distirbutions.

Reference: [cppreference.com](http://en.cppreference.com/w/cpp/numeric/random)

Example file: [random.cpp](random.cpp)

### Regexp

### emplace
