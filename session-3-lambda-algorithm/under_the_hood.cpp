#include <iostream>

int main () {
	/* Lambdas are implemented as function objects.
	 *
	 * These two are equivalent:
	 */
	auto hello_world_lambda = []() { std::cout << "[lambda] hello world !\n"; };

	struct HelloWorldFunctionObject {
		void operator() () const { std::cout << "[object] hello world !\n"; }
	};
	auto hello_world_object = HelloWorldFunctionObject{};

	hello_world_lambda ();
	hello_world_object ();

	/* The lambda is obviously shorter.
	 * Its struct is implicitely generated, and the name is internal to the compiler.
	 *
	 * Now with state and arguments:
	 */
	int tested_value = 42;

	auto is_tested_value_lambda = [tested_value](int i) { return i == tested_value; };

	struct CompareToReferenceInt {
		int reference;
		bool operator() (int i) const { return i == reference; }
	};
	auto is_tested_value_object = CompareToReferenceInt{tested_value};

	std::cout << std::boolalpha;
	std::cout << "[lambda] " << is_tested_value_lambda (0) << " " << is_tested_value_lambda (42)
	          << "\n";
	std::cout << "[object] " << is_tested_value_object (0) << " " << is_tested_value_object (42)
	          << "\n";

	/* Function object is verbose.
	 * But the type is explicit: useful for storage, passing to non template functions, etc.
	 * State can be accessed for later changes if needed.
	 * State layout, choice of value / reference / pointers / etc can be precisely done too.
	 */
}

#ifdef CPP14
/* C++14: Auto lambdas are functions objects with template operator().
 */

auto auto_lambda = [](auto i) { return i > 0; };

struct Positive {
	template <typename T> bool operator() (const T & t) const { return t > 0; }
};
#endif
