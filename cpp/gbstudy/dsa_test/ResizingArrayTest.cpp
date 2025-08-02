#include "pch.h"
#include "CppUnitTest.h"

// 테스트할 ResizingArray 클래스를 포함합니다.
#include "../dsa_lib/ResizingArray.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gb;

namespace UnitTest
{
	TEST_CLASS(ResizingArrayTest)
	{
	public:

		TEST_METHOD(HandlesInitialization)
		{
			// 1. 준비 (Arrange) & 2. 실행 (Act)
			ResizingArray<int> arr;

			// 3. 검증 (Assert)
			Assert::AreEqual(0, arr.size(), L"Initial size should be 0.");
			Assert::AreEqual(1, arr.capacity(), L"Initial capacity should be 1.");
			Assert::IsTrue(arr.is_empty(), L"Array should be empty initially.");
		}

		TEST_METHOD(HandlesPushBackAndAccess)
		{
			// 1. 준비 (Arrange)
			ResizingArray<int> arr;

			// 2. 실행 (Act)
			arr.push_back(10);
			arr.push_back(20);

			// 3. 검증 (Assert)
			Assert::AreEqual(2, arr.size(), L"Size should be 2 after two pushes.");
			Assert::IsFalse(arr.is_empty(), L"Array should not be empty.");
			Assert::AreEqual(10, arr[0], L"First element should be 10.");
			Assert::AreEqual(20, arr[1], L"Second element should be 20.");
		}

		TEST_METHOD(HandlesAutomaticResizing)
		{
			// 1. 준비 (Arrange)
			ResizingArray<int> arr;
			Assert::AreEqual(1, arr.capacity(), L"Initial capacity should be 1.");

			// 2. 실행 (Act) & 3. 검증 (Assert)
			arr.push_back(1); // Capacity: 1, Size: 1
			Assert::AreEqual(1, arr.capacity(), L"Capacity should remain 1.");

			arr.push_back(2); // Triggers resize
			Assert::AreEqual(2, arr.capacity(), L"Capacity should double to 2.");
			Assert::AreEqual(2, arr.size(), L"Size should be 2.");

			arr.push_back(3); // Triggers resize
			Assert::AreEqual(4, arr.capacity(), L"Capacity should double to 4.");
			Assert::AreEqual(3, arr.size(), L"Size should be 3.");
			Assert::AreEqual(3, arr[2], L"Third element should be accessible after resize.");
		}
		
		TEST_METHOD(HandlesPopBack)
		{
			// 1. 준비 (Arrange)
			ResizingArray<int> arr;
			arr.push_back(10);
			arr.push_back(20);
			arr.push_back(30);

			// 2. 실행 (Act)
			arr.pop_back();

			// 3. 검증 (Assert)
			Assert::AreEqual(2, arr.size(), L"Size should be 2 after one pop.");
			Assert::AreEqual(20, arr[arr.size() - 1], L"The new last element should be 20.");
			
			arr.pop_back();
			Assert::AreEqual(1, arr.size(), L"Size should be 1 after two pops.");
			Assert::AreEqual(10, arr[arr.size() - 1], L"The new last element should be 10.");
		}

		TEST_METHOD(HandlesShrinking)
		{
			// 1. 준비 (Arrange)
			ResizingArray<int> arr;
			for (int i = 0; i < 9; ++i) { // 9개의 요소를 추가
				arr.push_back(i);
			}
			// Size: 9, Capacity: 16 (1 -> 2 -> 4 -> 8 -> 16)
			Assert::AreEqual(16, arr.capacity(), L"Capacity should be 16.");
			
			// 2. 실행 (Act)
			// 요소를 4개로 줄여서 (16 / 4) 축소 조건을 만족시킵니다.
			for (int i = 0; i < 5; ++i) {
				arr.pop_back();
			}
			// Size: 4
			Assert::AreEqual(4, arr.size(), L"Size should be 4.");
			
			// 다음 pop_back에서 축소가 발생합니다.
			arr.pop_back(); 
			
			// 3. 검증 (Assert)
			// Size: 3, Capacity: 8 (16 / 2)
			Assert::AreEqual(8, arr.capacity(), L"Capacity should shrink to 8.");
		}


		TEST_METHOD(HandlesExceptionOnOutOfRange)
		{
			// 1. 준비 (Arrange)
			ResizingArray<int> arr;
			arr.push_back(5);

			// 2. 실행 & 3. 검증
			// 유효하지 않은 인덱스 접근 시 std::out_of_range 예외가 발생하는지 확인
			Assert::ExpectException<std::out_of_range>([&] {
				int val = arr[1]; // Index 1 is out of bounds
			}, L"Accessing out of bounds index should throw.");

			// 비어있는 배열에서 pop_back 시도 시 예외 확인
			ResizingArray<int> empty_arr;
			Assert::ExpectException<std::out_of_range>([&] {
				empty_arr.pop_back();
			}, L"Popping from an empty array should throw.");
		}

		TEST_METHOD(HandlesCopyConstructor)
		{
			// 1. 준비 (Arrange)
			ResizingArray<int> original;
			original.push_back(100);
			original.push_back(200);

			// 2. 실행 (Act)
			ResizingArray<int> copy = original; // 복사 생성자 호출

			// 3. 검증 (Assert)
			Assert::AreEqual(original.size(), copy.size(), L"Copy should have the same size.");
			Assert::AreEqual(100, copy[0], L"Copied element is incorrect.");

			// 복사본을 수정해도 원본은 바뀌지 않아야 함 (깊은 복사)
			copy[0] = 999;
			Assert::AreEqual(100, original[0], L"Original should not be changed after copy is modified.");
			Assert::AreNotEqual(original[0], copy[0], L"Original and copy should be different after modification.");
		}
		
		TEST_METHOD(HandlesRangeBasedForLoop)
		{
			// 1. 준비 (Arrange)
			ResizingArray<int> arr;
			arr.push_back(1);
			arr.push_back(2);
			arr.push_back(3);
			int sum = 0;
			int expected_sum = 6;

			// 2. 실행 (Act)
			// 범위 기반 for문으로 모든 요소 순회
			for (int val : arr) {
				sum += val;
			}

			// 3. 검증 (Assert)
			Assert::AreEqual(expected_sum, sum, L"Range-based for loop did not iterate correctly.");
		}
	};
}