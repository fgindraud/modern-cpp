// How to store lambda for future use
#include <functional>
#include <iostream>
#include <vector>

int main () {
	std::cout << std::boolalpha;

	// Contraints : int -> bool
	auto positive = [](int i) { return i >= 0; };
	auto positive_strict = [](int i) { return i > 0; };
	auto interval = [](int begin, int end) {
		// Returns a lambda with the checking function
		return [begin, end](int i) { return begin <= i && i < end; };
	};

#ifdef FUNCTION_POINTER
	// Can only store stateless lambdas :(
	using LambdaStoredType = bool (*) (int);
	// -> fails for interval(i,j) lambdas...
#endif

#ifdef STD_FUNCTION
	// Still costly, can store anything !
	using LambdaStoredType = std::function<bool(int)>;
#endif

#ifdef TEMPLATE
	// We can use decltype to get a lambda type.
	// Lambdas types are all different.
	// -> same problem as FUNCTION_POINTER
	using LambdaStoredType = decltype (positive); // Fails for positive_strict / interval(i,j)
	// using LambdaStoredType = decltype (interval (0, 0)); // Fails for positive/positive_strict
#endif

	std::vector<LambdaStoredType> constraints;
	constraints.push_back (positive);
	constraints.push_back (positive_strict);
	constraints.push_back (interval (0, 10));
	constraints.push_back (interval (-10, 10));

	auto tested_values = std::vector<int>{-1, 0, 1, 42};
	for (auto it = tested_values.begin (); it != tested_values.end (); ++it) {
		std::cout << *it << ": ";
		for (auto & constraint : constraints)
			std::cout << constraint (*it) << " ";
		std::cout << "\n";
	}

	// Stored lambdas are opaque types: no way to retrieve their state
	// -> not a replacement for a class describing a concept like IntervalConstraint
	auto my_interval = interval (42, 90);
	// [clang autocomplete methods]

	// Careful with stateful lambdas stored for later use:
	auto leaks_local_variables = [](int k) {
		// int k is a local variable, destroyed at the end of leaks_local_variables()
		return [&k](int i) { return i == k; }; // return reference to local variable: UB !
	};

	return 0;
}
