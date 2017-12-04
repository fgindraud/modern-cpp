#include <algorithm>
#include <iostream>
#include <vector>

struct EmptyStruct {};

bool call_int_predicate (bool (*pred) (int), int i) {
	return pred (i);
}

int user_int () {
	int i = 0;
	std::cout << "int ? ";
	std::cin >> i;
	return i;
}

int main () {
	std::cout << std::boolalpha;

	auto vec = std::vector<int>{0, 1, 2, 3, 4, 5, 6};

	// print_vec: print elements of a vector<int>
	// Defined as a lambda which returns void (no return statement).
	auto print_vec = [](const std::vector<int> & v) {
		// Using std::for_each from algorithm
		std::for_each (v.begin (), v.end (), [](int i) { std::cout << i << " "; });
		// Note that global variables can be accessed in the lambda (std::cout is global)
	};

	std::cout << "Vec: ";
	print_vec (vec);
	std::cout << "\n";

#ifdef STATELESS
	// Stateless lambda
	auto is_zero = [](int i) { return i == 0; };
	std::cout << "has_zero(v) = " << std::any_of (vec.begin (), vec.end (), is_zero) << "\n";

	// Equivalent to EmptyStruct
	std::cout << "sizeof (is_zero) = " << sizeof (is_zero) << "\n";
	std::cout << "sizeof (EmptyStruct) = " << sizeof (EmptyStruct) << "\n";

	// Casts to function pointer
	std::cout << "call_pred (is_zero, 0) = " << call_int_predicate (is_zero, 0) << "\n";
	std::cout << "call_pred (is_zero, 1) = " << call_int_predicate (is_zero, 1) << "\n";
	// Error:
	// std::cout << call_int_predicate(&is_zero, 0) << "\n";
#endif

#ifdef COPY_STATE
	int tested_int = user_int ();

	// has_tested_int(vec) ?
	// auto is_tested_int = [](int i) { return i == tested_int; }; // Compilation error
	auto is_tested_int = [tested_int](int i) { return i == tested_int; }; // tested_int in state
	std::cout << "has_tested_int(v) = " << std::any_of (vec.begin (), vec.end (), is_tested_int)
	          << "\n";

	// Equivalent to int
	std::cout << "sizeof (is_tested_int) = " << sizeof (is_tested_int) << "\n";
	std::cout << "sizeof (int) = " << sizeof (int) << "\n";

	// Does not cast to function pointer (compilation error)
	// std::cout << "call_pred (is_tested_int, 0) = " << call_int_predicate (is_tested_int, 0) <<
	// "\n";

	// int has been copied, changing it does not impact the lambda copy:
	tested_int = 0;
	std::cout << "tested_int = 0; is_tested_int (0) = " << is_tested_int (0) << "\n";
#endif

#ifdef NESTING
	// vec_has_int(i) ?
	// -> define a lambda that calls std::any_of
	auto vec_has_int = [vec](int i) {
		return std::any_of (vec.begin (), vec.end (), [i](int k) { return i == k; });
	};

	std::cout << "vec_has_int (0) = " << vec_has_int (0) << "\n";
	std::cout << "vec_has_int (42) = " << vec_has_int (42) << "\n";

	// Vector has been copied in the lambda
	std::cout << "sizeof (vec_has_int) = " << sizeof (vec_has_int) << "\n";
	std::cout << "sizeof (vector<int>) = " << sizeof (std::vector<int>) << "\n";

	// Deep copy is not affected by changes to original
	vec[0] = 42;
	std::cout << "vec_has_int (0) = " << vec_has_int (0) << "\n";
	std::cout << "vec_has_int (42) = " << vec_has_int (42) << "\n";
#endif

#ifdef REF_STATE
	// vec_has_int(i) without copy
	// -> same lambda, take vec by reference (note the '&')
	auto vec_has_int = [&vec](int i) {
		return std::any_of (vec.begin (), vec.end (), [i](int k) { return i == k; });
	};

	std::cout << "vec_has_int (0) = " << vec_has_int (0) << "\n";
	std::cout << "vec_has_int (42) = " << vec_has_int (42) << "\n";

	// Only reference stored in lambda
	std::cout << "sizeof (vec_has_int) = " << sizeof (vec_has_int) << "\n";
	std::cout << "sizeof (vector<int>*) = " << sizeof (std::vector<int> *) << "\n";

	// Can modify the lambda state then
	vec[0] = 42;
	std::cout << "vec_has_int (0) = " << vec_has_int (0) << "\n";
	std::cout << "vec_has_int (42) = " << vec_has_int (42) << "\n";
#endif

#ifdef THIS_STATE
	struct IntTester {
		int i;
		bool vec_has_int (const std::vector<int> & vec) const {
			return std::any_of (vec.begin (), vec.end (), [this](int k) { return i == k; });
		}
	};

	IntTester tester{4};
	std::cout << "tester.vec_has_int " << tester.i << ": " << tester.vec_has_int (vec) << "\n";
	tester.i = 42;
	std::cout << "tester.vec_has_int " << tester.i << ": " << tester.vec_has_int (vec) << "\n";
#endif

#ifdef FUNCTIONAL
	// A lambda can return a lambda
	auto vec_has_int_factory = [](int tested_int) {
		return [tested_int](const std::vector<int> & vec) {
			return std::any_of (vec.begin (), vec.end (),
			                    [tested_int](int i) { return i == tested_int; });
		};
	};

	auto vec_has_0 = vec_has_int_factory (0);
	auto vec_has_42 = vec_has_int_factory (42);
	std::cout << "vec_has_" << 0 << ": " << vec_has_0 (vec) << "\n";
	std::cout << "vec_has_" << 42 << ": " << vec_has_42 (vec) << "\n";
#endif

#ifdef AUTO_STATE
	const int a = 42;
	const int b = -333;
	const int c = 55;

	// Define a function using a lot of values
	auto f = [a, b, c](int & i) { i = ((a * i) + b) * c; };
	// auto f = [&](int & i) { i = ((a * i) + b) * c; }; // Take all external vars by reference

	std::for_each (vec.begin (), vec.end (), f);
	std::cout << "Vec f: ";
	print_vec (vec);
	std::cout << "\n";

	// '=' captures all by copy, EXCEPT class members ! dangerous...
	// auto f = [=](int & i) { i = ((a * i) + b) * c; };
#endif
	return 0;
}
