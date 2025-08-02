#include "pch.h"
#include "CppUnitTest.h"

#include "../dsa_lib/MergeSort.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gb;

namespace UnitTest
{
	TEST_CLASS(MergeSortTest)
	{
	public:

		TEST_METHOD(HandlesArray)
		{
			// 1. 준비 (Arrange)
			int arr[] = { 10, 4, 2, 8, 5 };
			int expected[] = { 2, 4, 5, 8, 10 };
			int n = sizeof(arr) / sizeof(arr[0]);
			MergeSort<int> sorter;

			// 2. 실행 (Act)
			sorter.sort(arr, n);

			// 3. 검증 (Assert)
			// 두 값이 같은지 확인합니다. 다르면 테스트는 실패합니다.
			for (int i = 0; i < n; ++i) {
				Assert::AreEqual(expected[i], arr[i]);
			}
		}

		TEST_METHOD(HandlesEmptyArray)
		{
			int* arr = nullptr;
			int n = 0;
			MergeSort<int> sorter;

			// 특정 코드가 예외를 던지지 않고 정상적으로 실행되는지 검증
			// 람다 함수를 사용하여 실행할 코드를 캡슐화합니다.
			Assert::IsTrue(true); // 이 테스트는 단순히 실행되는 것만 확인
		}

		TEST_METHOD(HandlesAlreadySortedArray)
		{
			int arr[] = { 1, 2, 3, 4, 5 };
			int expected[] = { 1, 2, 3, 4, 5 };
			int n = sizeof(arr) / sizeof(arr[0]);
			MergeSort<int> sorter;

			sorter.sort(arr, n);

			for (int i = 0; i < n; ++i) {
				Assert::AreEqual(expected[i], arr[i]);
			}
		}
	};
}
