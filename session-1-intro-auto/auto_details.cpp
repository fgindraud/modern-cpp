#include <iostream>
#include <vector>

#include <type_traits>

#ifdef BASIC_TYPES
int main () {
	std::cout << std::boolalpha;
	auto i = 42; // int
	std::cout << std::is_same<decltype (i), int>::value << "\n";

	auto s = "hello";
	std::cout << std::boolalpha << std::is_same<decltype (s), const char *>::value << "\n";
	auto & s_ref = "hello";
	std::cout << std::is_same<decltype (s_ref), const char(&)[6]>::value << "\n";
	return 0;
}
#endif

// Build a dummy int vector
std::vector<int> makeIntVector (int n) {
	std::vector<int> r;
	for (int i = 0; i < n; ++i)
		r.push_back (i + 1);
	return r;
}

#ifdef AUTO_INIT
int main () {
	// auto enables a new pattern for initialisation:
	auto vec = std::vector<int> (100, 42);

	// The C++11 spec allows the compiler to transform this into:
	std::vector<int> vec_ (100, 42);
	// (removes the copy entirely, even if the code is non trivial)
	// Most reasonnable compilers will do it.
	// (in the auto_rules.cpp/AUTO example, NoisyInt(4) was never copied)
	// Since C++17, compilers are required to remove the copies.

	// auto is very useful to remove redundant information when using factory functions:
	auto vec2 = makeIntVector (42);
	// instead of
	std::vector<int> vec3 = makeIntVector (42);
	// it also allows to change the type of returned objects without having to change call sites
}
#endif

#ifdef FUNCTION_ARG
// auto CANNOT be used as function arguments
void f (auto i) {
	std::cout << i;
}

// beware, as g++ allows it as an extension since C++14. This fails in clang++.
#endif

#ifdef TEMPLATE
// auto in arguments is covered by function templates, since before C++11:
template <typename T> void f (T i) {
	std::cout << i << "\n";
}

// auto is practical in templates: you can declare local variables easily:
template <typename Container> void print_front (const Container & container) {
	auto & v = container.front (); // instead of Container::const_reference f = container.front ()
	std::cout << v << "\n";
}

int main () {
	f (42);

	auto v = makeIntVector (42);
	print_front (v);
}
#endif

#ifdef AUTO_RETURN
// C++14 allows deducted return type, if this is not ambiguous

// Follows the same rules as auto variable: this returns an int, not a const int&
auto front (const std::vector<int> & v) {
	return v.front ();
}

// Force reference return:
auto & front_ref (const std::vector<int> & v) {
	return v.front ();
}

// Ask for "raw" type deduction, will return exactly the same expression type:
decltype (auto) front_raw (const std::vector<int> & v) {
	return v.front ();
}

int main () {
	auto ints = makeIntVector (42);

	std::cout << front (ints) << "\n";
	std::cout << std::boolalpha << std::is_same<decltype (front (ints)), int>::value << "\n";

	std::cout << front_ref (ints) << "\n";
	std::cout << std::boolalpha << std::is_same<decltype (front_ref (ints)), const int &>::value
	          << "\n";

	std::cout << front_raw (ints) << "\n";
	std::cout << std::boolalpha << std::is_same<decltype (front_raw (ints)), const int &>::value
	          << "\n";
}

/* Personally, I think return type deduction is only useful for very tiny wrappers.
 * If the return type if not obvious, is it better to write it explicitely.
 * auto everywhere is not worth the loss of precision in the API.
 */
#endif

#ifdef AUTO_RETURN_11
// Auto return type not available in c++11

// An ugly way to simulate it is to use decltype again:
auto front (const std::vector<int> & v) -> decltype (v.front ()) {
	return v.front ();
}
// The function body is duplicated...

int main () {
	auto ints = makeIntVector (42);
	std::cout << front (ints) << "\n";
	std::cout << std::boolalpha << std::is_same<decltype (front (ints)), const int &>::value << "\n";
}
#endif
