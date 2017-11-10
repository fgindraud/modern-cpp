#pragma once
#include <chrono>
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
