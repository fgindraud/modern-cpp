#pragma once
#include <chrono>
#include <string>

template <typename Callable> std::string benchmark_function (Callable callable) {
	using namespace std::chrono;
	auto start = high_resolution_clock::now ();
	callable ();
	auto end = high_resolution_clock::now ();
	auto elapsed_ns = duration_cast<nanoseconds> (end - start).count ();
	return std::to_string (elapsed_ns) + "ns";
}
