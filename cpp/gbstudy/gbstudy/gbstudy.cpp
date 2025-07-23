#include <iostream>
#include "Profiler.h"

int main() 
{
	long long result = 0;
	double elapsed_time_ms = 0.0;

	{
		gb::Profiler profiler(elapsed_time_ms);
		for (int i = 1; i <= 100000000; ++i)
		{
			result += i;
		}
	}

	std::cout << "result: " << result << " elapsed time: " << elapsed_time_ms << "ms" << std::endl;

	return 0;
}