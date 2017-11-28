# Session 2

## Langage

### List initialization
New syntax to initialize objects using curly braces.
It is really useful to initialize data structures such as vectors with explicit data.

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

### `nullptr`

### `using` syntax for typedef
An improved syntax is available for typedef statements: [typedef.cpp](typedef.cpp).

### `noexcept`
`throw(...)` specifications have been replaced by `noexcept`: [noexcept.cpp](noexcept.cpp).


## Standard library

### Sampling from distributions

### Regexp

### emplace
