// UnitTest/LinkedListTest.cpp
#include "pch.h"
#include "CppUnitTest.h"

#include "../dsa_lib/LinkedList.h" // 테스트할 LinkedList 클래스 포함

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gb;

namespace UnitTest
{
	TEST_CLASS(LinkedListTest)
	{
	public:
		
		TEST_METHOD(AppendAndSize)
		{
			// 준비 (Arrange)
			LinkedList<int> list;

			// 실행 (Act)
			list.append(10);
			list.append(20);
			list.append(30);

			// 검증 (Assert)
			Assert::AreEqual(3, list.size(), L"Size should be 3 after appending 3 items.");
		}

		TEST_METHOD(GetAndSetItem)
		{
			// 준비
			LinkedList<int> list;
			list.append(10);
			list.append(20);
			list.append(30);

			// 실행 & 검증 (Act & Assert) - Get
			Assert::AreEqual(10, list[0], L"Item at index 0 should be 10.");
			Assert::AreEqual(20, list[1], L"Item at index 1 should be 20.");
			Assert::AreEqual(30, list[2], L"Item at index 2 should be 30.");

			// 실행 & 검증 (Act & Assert) - Set
			list[1] = 99;
			Assert::AreEqual(99, list[1], L"Item at index 1 should be 99 after setting.");
		}

		TEST_METHOD(RemoveItem)
		{
			// 준비
			LinkedList<int> list;
			list.append(10);
			list.append(20);
			list.append(30);
			list.append(40);

			// 실행 1: 중간 항목 삭제
			list.remove_at(1); // 20 삭제

			// 검증 1
			Assert::AreEqual(3, list.size(), L"Size should be 3 after removing one item.");
			Assert::AreEqual(10, list[0], L"Item at index 0 should be 10.");
			Assert::AreEqual(30, list[1], L"Item at index 1 should now be 30.");
			Assert::AreEqual(40, list[2], L"Item at index 2 should now be 40.");

			// 실행 2: 첫 항목 삭제
			list.remove_at(0); // 10 삭제
			
			// 검증 2
			Assert::AreEqual(2, list.size(), L"Size should be 2 after removing the head.");
			Assert::AreEqual(30, list[0], L"New head should be 30.");
		}

		TEST_METHOD(NegativeIndexing)
		{
			// 준비
			LinkedList<int> list;
			list.append(10);
			list.append(20);
			list.append(30);

			// 실행 & 검증 - Get
			Assert::AreEqual(30, list[-1], L"Item at index -1 should be the last item (30).");
			Assert::AreEqual(20, list[-2], L"Item at index -2 should be 20.");

			// 실행 & 검증 - Set
			list[-1] = 99;
			Assert::AreEqual(99, list[2], L"Setting item at -1 should change the last item.");

			// 실행 & 검증 - Remove
			list.remove_at(-2); // 20 삭제
			Assert::AreEqual(2, list.size(), L"Size should be 2 after removing item at -2.");
			Assert::AreEqual(10, list[0], L"First item should still be 10.");
			Assert::AreEqual(99, list[1], L"Second item should now be 99.");
		}

		TEST_METHOD(IndexOutOfRange)
		{
			// 준비
			LinkedList<int> list;
			list.append(10);

			// 실행 & 검증
			Assert::ExpectException<std::out_of_range>([&] { list[2]; }, L"Accessing index 2 should throw out_of_range.");
			Assert::ExpectException<std::out_of_range>([&] { list[-3]; }, L"Accessing index -3 should throw out_of_range.");
			Assert::ExpectException<std::out_of_range>([&list] { list.remove_at(1); }, L"Removing at index 1 should throw out_of_range.");
		}
	};
}