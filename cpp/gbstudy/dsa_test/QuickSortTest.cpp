#include "pch.h"
#include "CppUnitTest.h"

#include "../dsa_lib/QuickSort.h"  

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gb;

namespace UnitTest
{
	TEST_CLASS(QuickSortTest)
	{
	public:

		TEST_METHOD(HandlesUnsortedArray)
		{
			// 1. 준비 (Arrange)
			int arr[] = { 29, 10, 14, 37, 13, 1, 99, 5 };
			int expected[] = { 1, 5, 10, 13, 14, 29, 37, 99 };
			int n = sizeof(arr) / sizeof(arr[0]);
			QuickSort<int> sorter;

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
			QuickSort<int> sorter;

			// 2. 실행 (Act) & 3. 검증 (Assert)
			// 빈 배열(크기 0)에 대해 sort를 호출해도 크래시가 발생하지 않아야 합니다.
			try
			{
				sorter.sort(arr, n);
				Assert::IsTrue(true); // 코드가 예외 없이 실행되었음을 확인
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
			QuickSort<int> sorter;

			// 2. 실행 (Act)
			sorter.sort(arr, n);

			// 3. 검증 (Assert)
			for (int i = 0; i < n; ++i) {
				Assert::AreEqual(expected[i], arr[i], L"Already sorted array test failed.");
			}
		}

		TEST_METHOD(HandlesArrayWithDuplicates)
		{
			// 1. 준비 (Arrange)
			int arr[] = { 5, 2, 8, 2, 9, 5, 8 };
			int expected[] = { 2, 2, 5, 5, 8, 8, 9 };
			int n = sizeof(arr) / sizeof(arr[0]);
			QuickSort<int> sorter;

			// 2. 실행 (Act)
			sorter.sort(arr, n);

			// 3. 검증 (Assert)
			for (int i = 0; i < n; ++i) {
				Assert::AreEqual(expected[i], arr[i], L"Array with duplicates test failed.");
			}
		}

		TEST_METHOD(HandlesSingleElementArray)
		{
			// 1. 준비 (Arrange)
			int arr[] = { 42 };
			int expected[] = { 42 };
			int n = sizeof(arr) / sizeof(arr[0]);
			QuickSort<int> sorter;

			// 2. 실행 (Act)
			sorter.sort(arr, n);

			// 3. 검증 (Assert)
			Assert::AreEqual(expected[0], arr[0], L"Single element array test failed.");
		}

        TEST_METHOD(HandlesReverseSortedArray)
        {
            // 1. 준비 (Arrange)
            int arr[] = { 50, 40, 30, 20, 10 };
            int expected[] = { 10, 20, 30, 40, 50 };
            int n = sizeof(arr) / sizeof(arr[0]);
            QuickSort<int> sorter;

            // 2. 실행 (Act)
            sorter.sort(arr, n);

            // 3. 검증 (Assert)
            for (int i = 0; i < n; ++i) {
                Assert::AreEqual(expected[i], arr[i], L"Reverse sorted array test failed.");
            }
        }
	};
}