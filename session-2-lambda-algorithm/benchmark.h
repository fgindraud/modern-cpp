#pragma once
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

template <typename Callable> std::string benchmark_function (Callable callable) {
	using namespace std::chrono;
	auto start = high_resolution_clock::now ();
	callable ();
	auto end = high_resolution_clock::now ();
	auto elapsed_ns = duration_cast<nanoseconds> (end - start).count ();
	return std::to_string (elapsed_ns) + "ns";
}

inline std::vector<int> make_non_zero_random_vector (std::size_t size) {
	std::random_device rd;
	std::mt19937 gen{rd ()};
	std::uniform_int_distribution<int> dis (1, 100000);

	std::vector<int> vec (size);
	for (auto & i : vec)
		i = dis (gen);
	return vec;
}

template <typename Predicate> void benchmark_predicate_on_non_zero_random_vector (Predicate pred) {
	std::vector<int> non_zero = make_non_zero_random_vector (10000);
	bool r = false;
	auto s = benchmark_function ([&non_zero, &r, &pred]() { r = pred (non_zero); });
	std::cout << "bench: " << s << " (r=" << r << ")\n";
}
