#include "pch.h"
#include "CppUnitTest.h"

// 테스트할 클래스들을 포함합니다.
#include "../dsa_lib/MergeSortLinkedList.h"
#include "../dsa_lib/LinkedList.h"

#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gb;

namespace UnitTest
{
	TEST_CLASS(MergeSortLinkedListTest)
	{
	public:

		// 테스트 헬퍼 함수: 두 벡터가 동일한지 확인합니다.
		void AssertVectorsAreEqual(const std::vector<int>& expected, const std::vector<int>& actual, const wchar_t* message)
		{
			Assert::AreEqual(expected.size(), actual.size(), L"Vector sizes do not match.");
			for (size_t i = 0; i < expected.size(); ++i)
			{
				Assert::AreEqual(expected[i], actual[i], message);
			}
		}

		TEST_METHOD(HandlesUnsortedList)
		{
			// 1. 준비 (Arrange)
			auto list = LinkedList<int>::from_vector({ 29, 10, 14, 37, 13, 1, 99, 5 });
			std::vector<int> expected = { 1, 5, 10, 13, 14, 29, 37, 99 };
			MergeSortLinkedList<int> sorter;

			// 2. 실행 (Act)
			Node<int>* sorted_head = sorter.sort(list.get_head());
			list.set_head(sorted_head); // 정렬된 헤드로 교체
			std::vector<int> actual = list.to_vector();

			// 3. 검증 (Assert)
			AssertVectorsAreEqual(expected, actual, L"Unsorted list test failed.");
		}

		TEST_METHOD(HandlesEmptyList)
		{
			// 1. 준비 (Arrange)
			auto list = LinkedList<int>::from_vector({});
			std::vector<int> expected = {};
			MergeSortLinkedList<int> sorter;

			// 2. 실행 (Act)
			Node<int>* sorted_head = sorter.sort(list.get_head());
			list.set_head(sorted_head);
			std::vector<int> actual = list.to_vector();

			// 3. 검증 (Assert)
			AssertVectorsAreEqual(expected, actual, L"Empty list test failed.");
		}

		TEST_METHOD(HandlesAlreadySortedList)
		{
			// 1. 준비 (Arrange)
			auto list = LinkedList<int>::from_vector({ 10, 20, 30, 40, 50 });
			std::vector<int> expected = { 10, 20, 30, 40, 50 };
			MergeSortLinkedList<int> sorter;

			// 2. 실행 (Act)
			Node<int>* sorted_head = sorter.sort(list.get_head());
			list.set_head(sorted_head);
			std::vector<int> actual = list.to_vector();

			// 3. 검증 (Assert)
			AssertVectorsAreEqual(expected, actual, L"Already sorted list test failed.");
		}

		TEST_METHOD(HandlesListWithDuplicates)
		{
			// 1. 준비 (Arrange)
			auto list = LinkedList<int>::from_vector({ 5, 2, 8, 2, 9, 5, 8 });
			std::vector<int> expected = { 2, 2, 5, 5, 8, 8, 9 };
			MergeSortLinkedList<int> sorter;

			// 2. 실행 (Act)
			Node<int>* sorted_head = sorter.sort(list.get_head());
			list.set_head(sorted_head);
			std::vector<int> actual = list.to_vector();
			
			// 3. 검증 (Assert)
			AssertVectorsAreEqual(expected, actual, L"List with duplicates test failed.");
		}

		TEST_METHOD(HandlesSingleElementList)
		{
			// 1. 준비 (Arrange)
			auto list = LinkedList<int>::from_vector({ 42 });
			std::vector<int> expected = { 42 };
			MergeSortLinkedList<int> sorter;
			
			// 2. 실행 (Act)
			Node<int>* sorted_head = sorter.sort(list.get_head());
			list.set_head(sorted_head);
			std::vector<int> actual = list.to_vector();

			// 3. 검증 (Assert)
			AssertVectorsAreEqual(expected, actual, L"Single element list test failed.");
		}
	};
}