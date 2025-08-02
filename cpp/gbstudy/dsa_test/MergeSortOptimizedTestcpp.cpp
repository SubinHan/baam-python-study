#include "pch.h"
#include "CppUnitTest.h"
#include "../dsa_lib/MergeSortOptimized.h" // 테스트할 클래스 포함

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gb;

namespace UnitTest
{
    TEST_CLASS(MergeSortOptimizedTest)
    {
    public:

        TEST_METHOD(HandlesUnsortedArray)
        {
            // 준비
            int arr[] = { 29, 10, 14, 37, 13, 1, 99, 5, 42, 15, 63, 8, 22, 49, 11 };
            int expected[] = { 1, 5, 8, 10, 11, 13, 14, 15, 22, 29, 37, 42, 49, 63, 99 };
            int n = sizeof(arr) / sizeof(arr[0]);
            MergeSortOptimized<int> sorter;

            // 실행
            sorter.sort(arr, n);

            // 검증
            for (int i = 0; i < n; ++i)
            {
                Assert::AreEqual(expected[i], arr[i], L"Unsorted array test failed.");
            }
        }

        TEST_METHOD(HandlesEmptyArray)
        {
            // 준비
            int* arr = nullptr;
            int n = 0;
            MergeSortOptimized<int> sorter;

            // 실행 & 검증
            try
            {
                sorter.sort(arr, n);
                Assert::IsTrue(true, L"Successfully handled empty array.");
            }
            catch (...)
            {
                Assert::Fail(L"Exception thrown for empty array.");
            }
        }

        TEST_METHOD(HandlesAlreadySortedArray)
        {
            // 준비
            int arr[] = { 10, 20, 30, 40, 50, 60, 70 };
            int expected[] = { 10, 20, 30, 40, 50, 60, 70 };
            int n = sizeof(arr) / sizeof(arr[0]);
            MergeSortOptimized<int> sorter;

            // 실행
            sorter.sort(arr, n);

            // 검증
            for (int i = 0; i < n; ++i)
            {
                Assert::AreEqual(expected[i], arr[i], L"Already sorted array test failed.");
            }
        }

        TEST_METHOD(HandlesArrayWithDuplicates)
        {
            // 준비
            int arr[] = { 5, 2, 8, 2, 9, 5, 8, 5 };
            int expected[] = { 2, 2, 5, 5, 5, 8, 8, 9 };
            int n = sizeof(arr) / sizeof(arr[0]);
            MergeSortOptimized<int> sorter;

            // 실행
            sorter.sort(arr, n);

            // 검증
            for (int i = 0; i < n; ++i)
            {
                Assert::AreEqual(expected[i], arr[i], L"Array with duplicates test failed.");
            }
        }

        TEST_METHOD(HandlesSingleElementArray)
        {
            // 준비
            int arr[] = { 42 };
            int n = 1;
            MergeSortOptimized<int> sorter;

            // 실행
            sorter.sort(arr, n);

            // 검증
            Assert::AreEqual(42, arr[0], L"Single element array test failed.");
        }

        TEST_METHOD(HandlesCutoffBoundary)
        {
            // 준비 (CUTOFF 값인 7과 같거나 작은 크기의 배열)
            int arr[] = { 5, 2, 4, 6, 1, 3 };
            int expected[] = { 1, 2, 3, 4, 5, 6 };
            int n = sizeof(arr) / sizeof(arr[0]);
            MergeSortOptimized<int> sorter;

            // 실행
            sorter.sort(arr, n);

            // 검증
            for (int i = 0; i < n; ++i)
            {
                Assert::AreEqual(expected[i], arr[i], L"Cutoff boundary test failed.");
            }
        }
    };
}