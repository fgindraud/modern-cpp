#include "benchmark.h"
#include <iostream>

// How to have lambda function arguments
// AKA write your own <algorithm> !

#include <vector>

#ifdef FUNCTION_POINTER
bool my_any_of (const std::vector<int> & v, bool (*predicate) (int)) {
	for (auto it = v.begin (); it != v.end (); ++it)
		if (predicate (*it))
			return true;
	return false;
}
// Fails with stateful lambdas...
#endif

#ifdef STD_FUNCTION
#include <functional>
bool my_any_of (const std::vector<int> & v, std::function<bool(int)> predicate) {
	for (auto it = v.begin (); it != v.end (); ++it)
		if (predicate (*it))
			return true;
	return false;
}
// Supports most lambdas, but costly : virtual class and malloc internally
#endif

#ifdef TEMPLATE
template <typename Predicate> bool my_any_of (const std::vector<int> & v, Predicate predicate) {
	for (auto it = v.begin (); it != v.end (); ++it)
		if (predicate (*it))
			return true;
	return false;
}
// Supports all lambdas, but template with all template caveats (header only, etc)
#endif

int main () {
	std::cout << std::boolalpha;

	auto vec = std::vector<int>{1, 2, 3, 4, 5};

	// Stateless
	std::cout << "my_any_of (is_0) = " << my_any_of (vec, [](int i) { return i == 0; }) << "\n";
	std::cout << "my_any_of (is_1) = " << my_any_of (vec, [](int i) { return i == 1; }) << "\n";

	// Stateful
	int k = 42;
	// std::cout << "my_any_of (is_k) = " << my_any_of (vec, [k](int i) { return i == k; }) << "\n";

	// Small benchmark
	benchmark_predicate_on_non_zero_random_vector (my_any_of);
	return 0;
}
