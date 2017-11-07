#include <algorithm>

// TODO
// remove_if + erase
// find_if
// sort + predicate on pointers


// Saved stuff
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
