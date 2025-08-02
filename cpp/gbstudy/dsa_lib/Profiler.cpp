// Profiler.cpp

#include "Profiler.h"

namespace gb
{
	// 생성자 구현
	Profiler::Profiler(double& result_ref)
		: result(result_ref) // 멤버 변수 초기화
	{
		// 생성 시점의 시간을 기록
		start_time_point = std::chrono::high_resolution_clock::now();
	}

	// 소멸자 구현
	Profiler::~Profiler()
	{
		// 소멸 시점의 시간을 기록
		auto end_time_point = std::chrono::high_resolution_clock::now();

		// 시작 시간과 끝 시간의 차이를 마이크로초(long long) 단위로 계산
		long long start_us = std::chrono::time_point_cast<std::chrono::microseconds>(start_time_point).time_since_epoch().count();
		long long end_us = std::chrono::time_point_cast<std::chrono::microseconds>(end_time_point).time_since_epoch().count();
		
		// 경과 시간 계산
		long long duration_us = end_us - start_us;
		
		// 결과를 밀리초(double) 단위로 변환하여 참조하고 있던 외부 변수에 저장
		result = duration_us * 0.001;
	}
}