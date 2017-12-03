#include <iostream>
#include <map>
#include <string>
#include <vector>

#include <type_traits> // tools for comparing types, not explained

int main () {
	std::cout << std::boolalpha;
#ifdef MAP_FIND
	{
		// map: string -> vector<int>
		std::map<std::string, std::vector<int>> my_map;
		std::vector<int> v;
		v.push_back (42);
		my_map.insert (std::make_pair ("a", v));

		// find returns an iterator
		// type is veeeeeerrrryyyy long
		std::map<std::string, std::vector<int>>::iterator it = my_map.find ("a");
		std::cout << "my_map[a].front ()=" << it->second.front () << "\n";

		// before C++11, you could shorten it by using a typedef

		// C++11 introduced (in fact, reused) the "auto keyword" to make LOCAL type deductions:
		auto it2 = my_map.find ("a");
		std::cout << "my_map[a].front ()=" << it2->second.front () << "\n";
		// it2 has the same type as it, without the long declaration

		// check that it and it2 have the same type using type_traits
		// (decltype (expr) returns the type of the expression)
		std::cout << std::is_same<decltype (it), decltype (it2)>::value << "\n";
	}
#endif
#ifdef VECTOR
	{
		// simplifies iterator loops
		std::vector<int> ints;
		ints.push_back (1);
		ints.push_back (2);
		ints.push_back (3);

		for (std::vector<int>::iterator it = ints.begin (); it != ints.end (); ++it)
			std::cout << *it << ",";
		std::cout << "\n";

		for (auto it = ints.begin (); it != ints.end (); ++it)
			std::cout << *it << ",";
		std::cout << "\n";

		// If you want to force use of const_iterator, use cbegin():
		std::vector<int>::const_iterator const_it_old_version = ints.begin ();
		auto const_it_with_auto = ints.cbegin ();

		// type_trait check
		std::cout << std::is_same<decltype (const_it_old_version), decltype (const_it_with_auto)>::value
		          << "\n";

		// auto by default copies the values (see auto_rules.cpp for details)
		// there are reference versions:
		int & front_explicit = ints[0];
		auto & front_auto = ints[0];
		std::cout << front_explicit << " " << front_auto << "\n";
		front_auto = 42;
		// const references as well
		const int & cfront_explicit = ints[0];
		auto & cfront_auto = ints[0];
		std::cout << cfront_explicit << " " << cfront_auto << "\n";
	}
#endif
	return 0;
}
