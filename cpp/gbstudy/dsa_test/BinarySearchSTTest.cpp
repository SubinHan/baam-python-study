#include "pch.h"
#include "CppUnitTest.h"

// 테스트할 BinarySearchST 클래스가 dsa_lib 폴더에 있다고 가정합니다.
#include "../dsa_lib/BinarySearchST.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gb;

namespace UnitTest
{
	TEST_CLASS(BinarySearchSTTest)
	{
	public:

		TEST_METHOD(PutAndGetNewKey)
		{
			// 준비 (Arrange)
			BinarySearchST<char, int> st(5);

			// 실행 (Act)
			st.put('C', 30);
			st.put('A', 10);
			st.put('B', 20);

			int* result_a = st.get('A');
			int* result_b = st.get('B');
			int* result_c = st.get('C');

			// 검증 (Assert)
			Assert::AreEqual(3, st.size(), L"Size should be 3.");
			Assert::IsNotNull(result_a, L"Key 'A' should exist.");
			Assert::AreEqual(10, *result_a, L"Value for 'A' should be 10.");
			Assert::IsNotNull(result_b, L"Key 'B' should exist.");
			Assert::AreEqual(20, *result_b, L"Value for 'B' should be 20.");
			Assert::IsNotNull(result_c, L"Key 'C' should exist.");
			Assert::AreEqual(30, *result_c, L"Value for 'C' should be 30.");
		}

		TEST_METHOD(UpdateExistingKey)
		{
			// 준비
			BinarySearchST<std::string, double> st(5);
			st.put("apple", 1.0);
			st.put("banana", 2.0);

			// 실행
			st.put("apple", 1.5);
			double* result = st.get("apple");

			// 검증
			Assert::AreEqual(2, st.size(), L"Size should remain 2 after update.");
			Assert::IsNotNull(result, L"Getting an updated key should not return null.");
			Assert::AreEqual(1.5, *result, L"The value for key 'apple' should be updated.");
		}

		TEST_METHOD(GetNonExistentKey)
		{
			// 준비
			BinarySearchST<int, std::string> st(5);
			st.put(10, "ten");
			st.put(20, "twenty");

			// 실행
			std::string* result = st.get(15);

			// 검증
			Assert::IsNull(result, L"Getting a non-existent key should return null.");
		}

		TEST_METHOD(RankFunctionality)
		{
			// 준비
			BinarySearchST<char, int> st(10);
			char keys[] = { 'A', 'C', 'E', 'H', 'L', 'M', 'P', 'R', 'S', 'X' };
			for (int i = 0; i < 10; ++i)
			{
				st.put(keys[i], i);
			}

			// 실행 & 검증
			Assert::AreEqual(0, st.rank('A'), L"Rank of 'A' should be 0.");
			Assert::AreEqual(3, st.rank('H'), L"Rank of 'H' should be 3.");
			Assert::AreEqual(9, st.rank('X'), L"Rank of 'X' should be 9.");
			
			// 테이블에 없는 키의 rank 검증
			Assert::AreEqual(1, st.rank('B'), L"Rank of 'B' (not in table) should be 1.");
			Assert::AreEqual(10, st.rank('Z'), L"Rank of 'Z' (not in table) should be 10.");
			Assert::AreEqual(0, st.rank('0'), L"Rank of '0' (not in table) should be 0.");
		}

		TEST_METHOD(AutoResize)
		{
			// 준비
			BinarySearchST<int, int> st(2); // 작은 용량으로 시작
			st.put(10, 100);
			st.put(20, 200);

			// 실행: 용량을 초과하여 삽입
			st.put(30, 300);
			st.put(5, 50);

			// 검증
			Assert::AreEqual(4, st.size(), L"Size should be 4 after resizing.");
			
			int* val_5 = st.get(5);
			Assert::IsNotNull(val_5, L"Key 5 should exist after resize.");
			Assert::AreEqual(50, *val_5, L"Value for 5 should be 50.");

			int* val_30 = st.get(30);
			Assert::IsNotNull(val_30, L"Key 30 should exist after resize.");
			Assert::AreEqual(300, *val_30, L"Value for 30 should be 300.");
		}
	};
}