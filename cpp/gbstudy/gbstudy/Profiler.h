// Profiler.h

#pragma once

#include <chrono>

namespace gb
{
	class Profiler
	{
	private:
		double& result;
		std::chrono::time_point<std::chrono::high_resolution_clock> start_time_point;

	public:
		Profiler(double& result_ref);
		~Profiler();
	};
}