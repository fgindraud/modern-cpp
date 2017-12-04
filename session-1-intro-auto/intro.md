# Session 1

These sessions are only intended to present some language and library features in a practical way.
For more information :
* [cppreference.com](http://en.cppreference.com): reference for C++ language constructs and the STL; has examples but not a tutorial
* Effective C++ / Effective Modern C++ (books by Scott Meyers): detailed discussion on language constructs and part of the STL; not as complete as cppreference, but more readable. The _modern_ book describes only C++11 and C++14.

## Whats new in C++

### C++11

Lots of new features:
* Type deduction with `auto` (session 1)
* For range (session 3)
* Anonymous functions: lambdas (session 2)
* Smart pointers: `std::unique_ptr<T>`, `std::shared_ptr<T>` (session 4)
* _Small features_ (spread over all sessions):
	* `override` and `final` for virtual classes
	* `emplace ()` methods on STL containers
	* list initialization
	* hash maps / sets : `std::unordered_map<K, V>` and `std::unordered_set<T>`
	* Random number generation
	* `throw(...)` function specifications replaced by `noexcept`
	* `using` syntax

Not discussed here, but interesting to know it exists:
* Variadic templates
* Tuple: generalised `std::pair`
* Threading: `thread`, `mutex`, `thread_local`, atomics
* Move semantics: let APIs detect _temporary objects_ and act differently (memory reuse, etc)
* Constexpr: perform computations at compile time

### C++14

Lots of small improvements and fixes:
* More type deduction : `auto` in lambdas, function return type
* Improved lambdas (`auto`, variadic)
* `make_unique<T>` which was forgotten in C++11
* Extended `constexpr`

### C++17

Usable with recent GCC / Clang, but will not be discussed.
Adds lots of features mostly on the library side, along with improvements to previous features like lambda & constexpr.

## Compiler support

Detailed support: [cppreference](http://en.cppreference.com/w/cpp/compiler_support).

Overall support:
* C++11: almost all useful compilers
* C++14: most compilers, but a lot of Linux distributions still use old compilers
* C++17: recent GCC & Clang with partial support

GCC / G++:
* 4.8.1: C++11 support; missing library-side stuff (regex)
* 5.0: C++11 and C++14 full support
* 6.1: C++14 by default
* 7.0: Most of C++17

Clang / Clang++ (LLVM):
* 3.3: C++11 support
* 3.4: C++14 support
* 5.0: Most of C++17

How to enable:
* `-std=c++11` for C++11
* `-std=c++14` for C++14

Compilers with the experimental equivalents (`-std=c++0x` and `-std=c++1y`) are likely to only have partial support: this may lead to weird bugs and crashes, use at your own risk.

## Support in common distributions

Based on GCC / G++ version as most people use them by default.
If you use clang on Linux you sually know what you are doing =).
This only lists distribution versions which are still supported (for example Ubuntu 12.04 precise is not supported anymore, and thus not included).

Ubuntu:
* C++11: >= 14.04 LTS (Trusty)
* C++14: >= 16.04 LTS (Xenial)

Debian:
* C++11: >= jessie (oldstable)
* C++14: >= stretch (stable)

Fedora:
* C++11 & C++14: >= 25

## Auto (type deduction)

Introduction with motivation: [auto_intro.cpp](auto_intro.cpp)

Deduction rules: [auto_rules.cpp](auto_rules.cpp)

Details and usages: [auto_details.cpp](auto_details.cpp)

