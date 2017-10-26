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

struct Test {
	std::vector<int> vec;
	std::vector<int> filter_ints (std::vector<int> ints_to_test) const;
};

int main () {
	std::vector<int> vec{0, 1, 2, 3, 4, 5, 6};
	std::cout << std::boolalpha;

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

#ifdef FUNCTIONAL
	// TODO lambda returning lambda ?
#endif

#ifdef THIS_STATE
	// print_vec: print elements of a vector<int>
	// Defined as a lambda which returns void (no return statement).
	auto print_vec = [](const std::vector<int> & v) {
		// Using std::for_each from algorithm
		std::for_each (v.begin (), v.end (), [](int i) { std::cout << i << " "; });
	};

	// List initialisation of struct
	Test test_value{vec};
	auto ints_present_in_vec = test_value.filter_ints ({0, 42, 4});
	print_vec (ints_present_in_vec);
	std::cout << "\n";
#endif

	// TODO glob capture modes ? dangerous
	return 0;
}

std::vector<int> Test::filter_ints (std::vector<int> ints_to_test) const {
	// Define vec_has_not_int (i) -> !vec_has_int (i)
	auto vec_has_not_int = [/* not &vec */ this](int i) {
		return std::all_of (vec.begin (), vec.end (), [i](int j) { return i != j; });
	};

	// Instead of building a new vector with ints found in vec, we remove ints not found.
	auto new_end_point = std::remove_if (ints_to_test.begin (), ints_to_test.end (), vec_has_not_int);
	// std::remove_if moves all "removed" values to the end of the vector (swaps)
	// it returns the new "end" iterator
	// we must call vector<int>::erase to update the
	ints_to_test.erase (new_end_point, ints_to_test.end ());

	return ints_to_test;
}
