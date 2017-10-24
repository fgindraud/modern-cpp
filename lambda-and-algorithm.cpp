#!/usr/bin/env bash
#if 0
tmp_cpp_file=$(mktemp "$0.XXXXX")
tmp_exe_file=$(mktemp "$0.out.XXXXX")
function cleanup {
	rm -f "$tmp_cpp_file" "$tmp_exe_file"
}
trap cleanup EXIT
tail -n +2 "$0" > "$tmp_cpp_file"
if "${CXX:-g++}" -x c++ $CXXFLAGS -o "$tmp_exe_file" "$tmp_cpp_file" "$@"; then
	"$tmp_exe_file"
fi
exit
#endif

/* Exemple: test if a vector<int> contains a 0
 */
#include <iostream>
#include <vector>

bool has_zero (const std::vector<int> & vec);

int main () {
	std::vector<int> with_zero{1, 2, 3, 0, 4, 0};
	std::vector<int> no_zero{1, 2, 3, 4, 5, 6};
	std::cout << std::boolalpha;
	std::cout << "with_zero: " << has_zero (with_zero) << "\n";
	std::cout << "no_zero: " << has_zero (no_zero) << "\n";
	return 0;
}

#ifdef MANUAL
// C++03 index version
bool has_zero (const std::vector<int> & vec) {
	for (int i = 0; i < vec.size (); ++i)
		if (vec[i] == 0)
			return true;
	return false;
}
// -Wall : signed vs unsigned comparison
#endif

#ifdef ITERATOR
// C++03 iterator version
bool has_zero (const std::vector<int> & vec) {
	for (std::vector<int>::const_iterator it = vec.begin (); it != vec.end (); ++it)
		if (*it == 0)
			return true;
	return false;
}
#endif

#ifdef AUTO_ITERATOR
// C++11 auto iterator version
bool has_zero (const std::vector<int> & vec) {
	for (auto it = vec.begin (); it != vec.end (); ++it)
		if (*it == 0)
			return true;
	return false;
}
#endif

#ifdef FOR_RANGE
// C++11 for-range version
bool has_zero (const std::vector<int> & vec) {
	for (auto i : vec)
		if (i == 0)
			return true;
	return false;
}
#endif

// Use what is already made for us.
#include <algorithm>

#ifdef ANY_OF
// C++11 std::any_of version
bool is_zero (int i) {
	return i == 0;
}
bool has_zero (const std::vector<int> & vec) {
	return std::any_of (vec.begin (), vec.end (), is_zero);
}
#endif

#ifdef ANY_OF_LAMBDA
// C++11 any_of with temporary lambda
bool has_zero (const std::vector<int> & vec) {
	return std::any_of (vec.begin (), vec.end (), [](int i) { return i == 0; });
}
#endif

#ifdef ANY_OF_STORED_LAMBDA
// C++11 any_of with stored lambda
bool has_zero (const std::vector<int> & vec) {
	auto is_zero = [](int i) { return i == 0; };
	return std::any_of (vec.begin (), vec.end (), is_zero);
}
#endif

/* TODO:
 * - add Phase 1 / 2 /... ifdefs
 * - more algorithm : foreach, find_if
 * - closure (is_int (n) ?)
 * - closure by ref, value, this
 * - store / transmit lambdas (std::function, function pointer for stateless, Callable &&)
 *
 * Advanced: functor analogy ? Auto lambda args of c++14 ?
 */
