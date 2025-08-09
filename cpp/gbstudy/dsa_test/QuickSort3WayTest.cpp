#include "pch.h"
#include "CppUnitTest.h"

// 테스트할 QuickSort3Way 클래스를 포함합니다.
#include "../dsa_lib/Sort.h"        // Sort.h의 실제 경로로 수정하세요.
#include "../dsa_lib/QuickSort3Way.h" // QuickSort3Way.h의 실제 경로로 수정하세요.

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gb;

namespace UnitTest
{
	TEST_CLASS(QuickSort3WayTest)
	{
	public:

		TEST_METHOD(HandlesArrayWithManyDuplicates)
		{
			// 1. 준비 (Arrange)
			// 3-way 퀵 정렬이 가장 효과적인, 중복 키가 많은 배열
			int arr[] = { 2, 5, 5, 1, 9, 2, 5, 1, 8, 5 };
			int expected[] = { 1, 1, 2, 2, 5, 5, 5, 5, 8, 9 };
			int n = sizeof(arr) / sizeof(arr[0]);
			QuickSort3Way<int> sorter;

			// 2. 실행 (Act)
			sorter.sort(arr, n);

			// 3. 검증 (Assert)
			for (int i = 0; i < n; ++i) {
				Assert::AreEqual(expected[i], arr[i], L"Array with many duplicates test failed.");
			}
		}

		TEST_METHOD(HandlesArrayWithAllSameElements)
		{
			// 1. 준비 (Arrange)
			// 모든 원소가 동일한 엣지 케이스
			int arr[] = { 7, 7, 7, 7, 7, 7, 7 };
			int expected[] = { 7, 7, 7, 7, 7, 7, 7 };
			int n = sizeof(arr) / sizeof(arr[0]);
			QuickSort3Way<int> sorter;

			// 2. 실행 (Act)
			sorter.sort(arr, n);

			// 3. 검증 (Assert)
			for (int i = 0; i < n; ++i) {
				Assert::AreEqual(expected[i], arr[i], L"Array with all same elements test failed.");
			}
		}


		TEST_METHOD(HandlesUnsortedArray)
		{
			// 1. 준비 (Arrange)
			int arr[] = { 29, 10, 14, 37, 13, 1, 99, 5 };
			int expected[] = { 1, 5, 10, 13, 14, 29, 37, 99 };
			int n = sizeof(arr) / sizeof(arr[0]);
			QuickSort3Way<int> sorter;

			// 2. 실행 (Act)
			sorter.sort(arr, n);

			// 3. 검증 (Assert)
			for (int i = 0; i < n; ++i) {
				Assert::AreEqual(expected[i], arr[i], L"Unsorted array test failed.");
			}
		}

		TEST_METHOD(HandlesEmptyArray)
		{
			// 1. 준비 (Arrange)
			int* arr = nullptr;
			int n = 0;
			QuickSort3Way<int> sorter;

			// 2. 실행 (Act) & 3. 검증 (Assert)
			try
			{
				sorter.sort(arr, n);
				Assert::IsTrue(true);
			}
			catch (...)
			{
				Assert::Fail(L"Exception thrown for empty array.");
			}
		}

		TEST_METHOD(HandlesAlreadySortedArray)
		{
			// 1. 준비 (Arrange)
			int arr[] = { 10, 20, 30, 40, 50 };
			int expected[] = { 10, 20, 30, 40, 50 };
			int n = sizeof(arr) / sizeof(arr[0]);
			QuickSort3Way<int> sorter;

			// 2. 실행 (Act)
			sorter.sort(arr, n);

			// 3. 검증 (Assert)
			for (int i = 0; i < n; ++i) {
				Assert::AreEqual(expected[i], arr[i], L"Already sorted array test failed.");
			}
		}

		TEST_METHOD(HandlesSingleElementArray)
		{
			// 1. 준비 (Arrange)
			int arr[] = { 42 };
			int expected[] = { 42 };
			int n = sizeof(arr) / sizeof(arr[0]);
			QuickSort3Way<int> sorter;

			// 2. 실행 (Act)
			sorter.sort(arr, n);

			// 3. 검증 (Assert)
			Assert::AreEqual(expected[0], arr[0], L"Single element array test failed.");
		}
	};
}