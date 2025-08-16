#include "pch.h"
#include "CppUnitTest.h"

// 테스트할 MaxPQ 클래스가 dsa_lib 폴더에 있다고 가정합니다.
#include "../dsa_lib/MaxPQ.h" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gb;

namespace UnitTest
{
	TEST_CLASS(MaxPQTest)
	{
	public:
		
		TEST_METHOD(InsertAndSize)
		{
			// 준비 (Arrange)
			MaxPQ<int> pq(5);

			// 실행 (Act)
			pq.insert(10);
			pq.insert(20);

			// 검증 (Assert)
			Assert::AreEqual(2, pq.size(), L"Size should be 2 after inserting 2 items.");
			Assert::IsFalse(pq.is_empty(), L"PQ should not be empty.");

			pq.insert(30);
			pq.insert(40);
			pq.insert(50);

			Assert::AreEqual(5, pq.size(), L"Size should be 5 after filling the PQ.");
		}

		TEST_METHOD(DelMaxAndIsEmpty)
		{
			// 준비
			MaxPQ<int> pq(5);
			pq.insert(10);
			pq.insert(50);
			pq.insert(30);

			// 실행 & 검증: del_max
			Assert::AreEqual(50, pq.del_max(), L"The first max element should be 50.");
			Assert::AreEqual(2, pq.size(), L"Size should be 2 after one del_max call.");

			Assert::AreEqual(30, pq.del_max(), L"The second max element should be 30.");
			Assert::AreEqual(10, pq.del_max(), L"The third max element should be 10.");

			// 실행 & 검증: is_empty
			Assert::IsTrue(pq.is_empty(), L"PQ should be empty after deleting all items.");
			Assert::AreEqual(0, pq.size(), L"Size should be 0 for an empty PQ.");
		}

		TEST_METHOD(OrderOfDeletion)
		{
			// 준비
			MaxPQ<int> pq(10);
			int data[] = { 42, 10, 88, 23, 99, 5, 67 };
			for (int item : data)
			{
				pq.insert(item);
			}

			// 실행 & 검증
			Assert::AreEqual(99, pq.del_max(), L"Order of deletion test failed: Expected 99.");
			Assert::AreEqual(88, pq.del_max(), L"Order of deletion test failed: Expected 88.");
			Assert::AreEqual(67, pq.del_max(), L"Order of deletion test failed: Expected 67.");
			Assert::AreEqual(42, pq.del_max(), L"Order of deletion test failed: Expected 42.");
			Assert::AreEqual(23, pq.del_max(), L"Order of deletion test failed: Expected 23.");
			Assert::AreEqual(10, pq.del_max(), L"Order of deletion test failed: Expected 10.");
			Assert::AreEqual(5, pq.del_max(), L"Order of deletion test failed: Expected 5.");
		}

		TEST_METHOD(HandleDuplicates)
		{
			// 준비
			MaxPQ<int> pq(7);
			pq.insert(20);
			pq.insert(10);
			pq.insert(30);
			pq.insert(20);
			pq.insert(10);

			// 실행 & 검증
			Assert::AreEqual(5, pq.size(), L"Size should be 5 with duplicates.");
			Assert::AreEqual(30, pq.del_max(), L"Max should be 30.");
			Assert::AreEqual(20, pq.del_max(), L"Next max should be 20.");
			Assert::AreEqual(20, pq.del_max(), L"Next max should be the duplicate 20.");
			Assert::AreEqual(10, pq.del_max(), L"Next max should be 10.");
			Assert::AreEqual(10, pq.del_max(), L"Next max should be the duplicate 10.");
		}

		TEST_METHOD(ExceptionHandling)
		{
			// 준비
			MaxPQ<int> pq(2);
			pq.insert(1);
			pq.insert(2);

			// 검증: 꽉 찬 큐에 insert 시도
			Assert::ExpectException<std::overflow_error>(
				[&] { pq.insert(3); }, 
				L"Inserting into a full PQ should throw overflow_error."
			);

			// 준비
			pq.del_max();
			pq.del_max();

			// 검증: 빈 큐에서 del_max 시도
			Assert::IsTrue(pq.is_empty(), L"PQ should be empty before testing empty deletion.");
			Assert::ExpectException<std::out_of_range>(
				[&] { pq.del_max(); }, 
				L"Deleting from an empty PQ should throw out_of_range."
			);
		}
	};
}