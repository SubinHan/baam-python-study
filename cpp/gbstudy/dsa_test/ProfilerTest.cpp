#include "pch.h"
#include "CppUnitTest.h"
#include "../dsa_lib/Profiler.h"

#include <thread>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gb;

namespace UnitTest
{
	TEST_CLASS(ProfilerTest)
	{
	public:

		TEST_METHOD(UpdatesVariableOnDestruction)
		{
			// 1. 준비 (Arrange)
			double elapsed_time_ms = 0.0;

			// 2. 실행 (Act)
			{
				Profiler profiler(elapsed_time_ms);
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}

			// 3. 검증 (Assert)
			Assert::IsTrue(elapsed_time_ms >= 100.0, L"Elapsed time should be at least 20ms.");
			Assert::IsTrue(elapsed_time_ms < 115.0, L"Elapsed time should be reasonable.");
		}

		TEST_METHOD(WorksWithNoDelay)
		{
			// 1. 준비 (Arrange)
			double elapsed_time_ms = -1.0;

			// 2. 실행 (Act)
			{
				Profiler profiler(elapsed_time_ms);
			}

			// 3. 검증 (Assert)
			Assert::IsTrue(elapsed_time_ms >= 0.0, L"Elapsed time should be non-negative.");
			Assert::IsTrue(elapsed_time_ms < 1.0, L"Elapsed time should be very small.");
		}
	};
}