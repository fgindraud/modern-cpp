#include "benchmark.h"
#include <iostream>

// How to store lambdas, and how have lambda function arguments
// AKA write your own <algorithm> !

#include <vector>

#ifdef FUNCTION_POINTER
bool my_any_of (const std::vector<int> & v, bool (*predicate) (int)) {
	for (auto i : v)
		if (predicate (i))
			return true;
	return false;
}
// Fails with stateful lambdas...
#endif

#ifdef STD_FUNCTION
#include <functional>
bool my_any_of (const std::vector<int> & v, std::function<bool(int)> predicate) {
	for (auto i : v)
		if (predicate (i))
			return true;
	return false;
}
// Supports most lambdas, but costly
#endif

#ifdef TEMPLATE
template <typename Predicate> bool my_any_of (const std::vector<int> & v, Predicate predicate) {
	for (auto i : v)
		if (predicate (i))
			return true;
	return false;
}
// Supports most lambdas, but costly
#endif

int main () {
	std::cout << std::boolalpha;
	const std::vector<int> vec{1, 2, 3, 4, 5};

	// Stateless
	std::cout << "my_any_of (is_0) = " << my_any_of (vec, [](int i) { return i == 0; }) << "\n";
	std::cout << "my_any_of (is_1) = " << my_any_of (vec, [](int i) { return i == 1; }) << "\n";

	// Stateful
	int k = 42;
	std::cout << "my_any_of (is_k) = " << my_any_of (vec, [k](int i) { return i == k; }) << "\n";

	// Small benchmark
	std::vector<int> all_ones (10000, 1);
	bool r = false;
	auto s = benchmark_function (
	    [&all_ones, &r]() { r = my_any_of (all_ones, [](int i) { return i == 0; }); });
	std::cout << "bench: " << s << " (r=" << r << ")\n";

	return 0;
}

// TODO storage for std::function. Fix minibench with volatile
