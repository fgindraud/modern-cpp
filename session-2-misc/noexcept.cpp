#include <exception>

struct MyException1 : public std::exception {};
struct MyException2 : public std::exception {};

#ifdef THROW_SPEC
// Old C++ throw specification are verbose.
// All possible exceptions should be listed, comma separated:
void f() throw(MyException1) {
    // Do something
}

// Easy to get wrong, as the list must include exceptions thrown by sub function calls:
void g() throw(MyException2) { f(); }

// Define a function as not throwing
void do_not_throw() throw() {}
#endif

#ifdef NOEXCEPT
// C++11: throw(...) deprecrated (warning by default in GCC >= 7)
// Replaced by noexcept (or absence of "noexcept" for "may throw" functions):
void f() {}
void g() {}
void do_not_throw() noexcept {}
#endif

int main() {
    f();
    g();
    do_not_throw();
    return 0;
}
