#include "pch.h"
#include "CppUnitTest.h"

#include "../dsa_lib/QuickSelect.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gb;

namespace UnitTest
{
	TEST_CLASS(QuickSelectTest)
	{
	public:

		TEST_METHOD(FindMedianElement)
		{
			// 1. 준비 (Arrange)
			int arr[] = { 29, 10, 14, 37, 13, 1, 99, 5 };
			int n = sizeof(arr) / sizeof(arr[0]);
			int k = n / 2; // 중앙값 인덱스 (0-based)
			int expected_median = 14; // 정렬 시: 1, 5, 10, 13, [14], 29, 37, 99
			QuickSelect<int> selector;

			// 2. 실행 (Act)
			int result = selector.select(arr, n, k);

			// 3. 검증 (Assert)
			Assert::AreEqual(expected_median, result, L"Finding median element failed.");
		}

		TEST_METHOD(FindFirstElement)
		{
			// 1. 준비 (Arrange)
			int arr[] = { 29, 10, 14, 37, 13, 1, 99, 5 };
			int n = sizeof(arr) / sizeof(arr[0]);
			int k = 0; // 가장 작은 원소
			int expected_min = 1;
			QuickSelect<int> selector;

			// 2. 실행 (Act)
			int result = selector.select(arr, n, k);

			// 3. 검증 (Assert)
			Assert::AreEqual(expected_min, result, L"Finding first element (min) failed.");
		}

		TEST_METHOD(FindLastElement)
		{
			// 1. 준비 (Arrange)
			int arr[] = { 29, 10, 14, 37, 13, 1, 99, 5 };
			int n = sizeof(arr) / sizeof(arr[0]);
			int k = n - 1; // 가장 큰 원소
			int expected_max = 99;
			QuickSelect<int> selector;

			// 2. 실행 (Act)
			int result = selector.select(arr, n, k);

			// 3. 검증 (Assert)
			Assert::AreEqual(expected_max, result, L"Finding last element (max) failed.");
		}

		TEST_METHOD(HandlesArrayWithDuplicates)
		{
			// 1. 준비 (Arrange)
			int arr[] = { 5, 2, 8, 2, 9, 5, 8 };
			int n = sizeof(arr) / sizeof(arr[0]);
			int k = 3; // 정렬 시: 2, 2, 5, [5], 8, 8, 9
			int expected_value = 5;
			QuickSelect<int> selector;

			// 2. 실행 (Act)
			int result = selector.select(arr, n, k);

			// 3. 검증 (Assert)
			Assert::AreEqual(expected_value, result, L"Select on array with duplicates failed.");
		}

		TEST_METHOD(ThrowsOnInvalidK)
		{
			// 1. 준비 (Arrange)
			int arr[] = { 10, 20, 30 };
			int n = sizeof(arr) / sizeof(arr[0]);
			QuickSelect<int> selector;

			// 2. 실행 & 3. 검증 (Act & Assert)
			// k가 범위를 벗어날 때 std::invalid_argument 예외가 발생하는지 확인
			Assert::ExpectException<std::invalid_argument>([&]() {
				selector.select(arr, n, -1); // k < 0
			}, L"Did not throw for k < 0.");

			Assert::ExpectException<std::invalid_argument>([&]() {
				selector.select(arr, n, n); // k >= n
			}, L"Did not throw for k >= n.");
		}
	};
}