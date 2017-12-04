// Useful functions from...
#include <algorithm>
// But not exhaustive !

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

template <typename T, typename Show>
void print_vec (const std::string & s, const std::vector<T> & v, Show show) {
	std::cout << s << " {";
	for (auto it = v.begin (); it != v.end (); ++it) {
		show (std::cout, *it);
		std::cout << " ";
	}
	std::cout << "}\n";
}
template <typename T> void print_vec (const std::string & s, const std::vector<T> & v) {
	auto default_show = [](std::ostream & os, const T & t) { os << t; };
	print_vec (s, v, default_show);
}

int main () {
	// Our guinea-pig
	std::vector<int> vec;
	vec.push_back (0);
	vec.push_back (42);
	vec.push_back (-3);
	vec.push_back (10);
	vec.push_back (10000);
	print_vec ("start", vec);

#ifdef SORT
	{
		auto copy = vec;

		std::sort (copy.begin (), copy.end ());
		print_vec ("sorted", copy);

		std::sort (copy.begin (), copy.end (),
		           [](int l, int r) { return std::abs (l) < std::abs (r); });
		print_vec ("abs() sorted", copy);

		std::vector<int *> pointers{new int(42), new int(3), new int(-4)}; // Bad, use unique_ptr<int>
		auto show_pointed_value = [](std::ostream & os, const int * p) { os << *p; };
		print_vec ("pointers unsorted", pointers, show_pointed_value);

		std::sort (pointers.begin (), pointers.end ()); // Sort with pointers values (UB)
		print_vec ("pointers « sorted »", pointers, show_pointed_value);

		std::sort (pointers.begin (), pointers.end (),
		           [](const int * l, const int * p) { return *l < *p; });
		print_vec ("pointers sorted", pointers, show_pointed_value);
	}
#endif

#ifdef REMOVE
	{
		// Remove all values >20

		// Naive, potentially O(n^2), complex due to iterator invalidation rules
		auto copy = vec;
		for (auto it = copy.begin (); it != copy.end ();) {
			if (*it > 20) {
				it = copy.erase (it); // O(n)
			} else {
				++it;
			}
		}
		print_vec ("removed naive style", copy);

		// Algorithm to the rescue !
		auto copy2 = vec;
		auto new_end = std::remove_if (copy2.begin (), copy2.end (), [](int i) { return i > 20; });
		print_vec ("« moves » all kept values to the front", copy2);
		copy2.erase (new_end, copy2.end ());
		print_vec ("erase tail", copy2);
		// Both are O(n).
	}
#endif

#ifdef MINMAX
	auto min_it = std::min_element (vec.begin (), vec.end ());
	std::cout << "min: " << std::distance (vec.begin (), min_it) << " " << *min_it << "\n";
	auto max_it = std::max_element (vec.begin (), vec.end ());
	std::cout << "max: " << std::distance (vec.begin (), max_it) << " " << *max_it << "\n";

	std::cout << "abs() min: " << *std::min_element (vec.begin (), vec.end (), [](int l, int r) {
		return std::abs (l) < std::abs (r);
	}) << "\n";
#endif

#ifdef SEARCHING
	auto predicate = [](int i) { return i > 20; };
	std::cout << "count: " << std::count_if (vec.begin (), vec.end (), predicate) << "\n";
	auto it = std::find_if (vec.begin (), vec.end (), predicate);
	std::cout << "find: " << *it << "\n";
	it = std::find_if (++it, vec.end (), predicate);
	std::cout << "find: " << *it << "\n";
#endif

	return 0;
}
