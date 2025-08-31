#include "pch.h"
#include "CppUnitTest.h"

#include "../dsa_lib/Bst.h" 
#include <vector>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gb;

namespace UnitTest
{
	TEST_CLASS(BstTest)
	{
	private:
		// 테스트 메서드들에서 공통적으로 사용할 BST 인스턴스를 생성하는 헬퍼 함수
		void populate_test_tree(Bst<char, int>& bst)
		{
			bst.put('S', 0);
			bst.put('E', 1);
			bst.put('X', 2);
			bst.put('A', 3);
			bst.put('R', 4);
			bst.put('C', 5);
			bst.put('H', 6);
			bst.put('M', 7);
			// 최종 트리 구조:
			//      S
			//    /   \
			//   E     X
			//  / \   /
			// A   R
			//  \ /
			//  C H
			//    \
			//     M
		}

	public:

		TEST_METHOD(TestPutAndGet)
		{
			// 1. 기본 연산: put(), get() 테스트
			Bst<std::string, int> bst;

			// 새 키-값 쌍 추가
			bst.put("hello", 10);
			bst.put("world", 20);
			Assert::AreEqual(2, bst.size(), L"Size should be 2 after putting two new keys.");
			Assert::AreEqual(10, bst.get("hello"), L"Value for 'hello' should be 10.");
			Assert::AreEqual(20, bst.get("world"), L"Value for 'world' should be 20.");

			// 기존 키의 값 업데이트
			bst.put("hello", 100);
			Assert::AreEqual(2, bst.size(), L"Size should remain 2 after updating a key.");
			Assert::AreEqual(100, bst.get("hello"), L"Value for 'hello' should be updated to 100.");

			// 존재하지 않는 키에 대해 get() 호출 시 예외 발생 검증
			Assert::ExpectException<std::runtime_error>([&]
				{
					bst.get("nonexistent");
				}, L"Getting a non-existent key should throw a runtime_error.");
		}

		TEST_METHOD(TestMinMax)
		{
			// 2. min(), max() 테스트
			Bst<char, int> bst;
			populate_test_tree(bst);

			Assert::AreEqual('A', bst.min(), L"The minimum key should be 'A'.");
			Assert::AreEqual('X', bst.max(), L"The maximum key should be 'X'.");

			Bst<int, int> empty_bst;
			Assert::ExpectException<std::runtime_error>([&] { empty_bst.min(); }, L"min() on empty tree should throw.");
			Assert::ExpectException<std::runtime_error>([&] { empty_bst.max(); }, L"max() on empty tree should throw.");
		}

		TEST_METHOD(TestOrderOperations)
		{
			// 3. ceiling(), floor(), rank(), select() 테스트
			Bst<char, int> bst;
			populate_test_tree(bst); // Keys: A, C, E, H, M, R, S, X

			// floor() 테스트
			Assert::AreEqual('E', bst.floor('F'), L"floor of 'F' should be 'E'.");
			Assert::AreEqual('H', bst.floor('H'), L"floor of 'H' should be 'H'.");
			Assert::AreEqual('A', bst.floor('B'), L"floor of 'B' should be 'A'.");

			// ceiling() 테스트
			Assert::AreEqual('H', bst.ceiling('G'), L"ceiling of 'G' should be 'H'.");
			Assert::AreEqual('A', bst.ceiling('A'), L"ceiling of 'A' should be 'A'.");

			// rank() 테스트 (key보다 작은 키의 수)
			Assert::AreEqual(0, bst.rank('A'), L"rank of 'A' should be 0.");
			Assert::AreEqual(2, bst.rank('E'), L"rank of 'E' should be 2.");
			Assert::AreEqual(4, bst.rank('M'), L"rank of 'M' should be 4.");
			Assert::AreEqual(8, bst.rank('Z'), L"rank of 'Z' (non-existent) should be 8.");

			// select() 테스트 (k번째 순위의 키)
			Assert::AreEqual('A', bst.select(0), L"select(0) should be 'A'.");
			Assert::AreEqual('H', bst.select(3), L"select(3) should be 'H'.");
			Assert::AreEqual('X', bst.select(7), L"select(7) should be 'X'.");
			Assert::ExpectException<std::runtime_error>([&] { bst.select(8); }, L"select() with out-of-bounds rank should throw.");
		}

		TEST_METHOD(TestDeleteMinMax)
		{
			// 4-1. delete_min(), delete_max() 테스트
			Bst<char, int> bst;
			populate_test_tree(bst);// Keys: A, C, E, H, M, R, S, X

			// delete_min()
			bst.delete_min(); // 'A' 삭제
			Assert::AreEqual(7, bst.size(), L"Size should be 7 after deleting min.");
			Assert::AreEqual('C', bst.min(), L"New minimum key should be 'C'.");

			// delete_max()
			bst.delete_max(); // 'X' 삭제
			Assert::AreEqual(6, bst.size(), L"Size should be 6 after deleting max.");
			Assert::AreEqual('S', bst.max(), L"New maximum key should be 'S'.");
		}

		TEST_METHOD(TestDeleteKey)
		{
			// 4-2. delete_key() 테스트
			Bst<char, int> bst;
			populate_test_tree(bst);

			// Case 1: 자식이 없는 노드 삭제 ('M')
			bst.delete_key('M');
			Assert::AreEqual(7, bst.size(), L"Size should be 7 after deleting a leaf node.");
			Assert::ExpectException<std::runtime_error>([&] { bst.get('M'); }, L"Node 'M' should be deleted.");

			// Case 2: 자식이 하나인 노드 삭제 ('R')
			bst.delete_key('R'); // 'R'을 삭제하면 'M'이 그 자리를 채운 상태(위에서 M을 삭제했으니 H가 올라옴)
			Assert::AreEqual(6, bst.size(), L"Size should be 6 after deleting a node with one child.");
			Assert::ExpectException<std::runtime_error>([&] { bst.get('R'); }, L"Node 'R' should be deleted.");
			Assert::AreEqual(6, bst.get('H'), L"Value of H should remain unchanged."); // H의 부모였던 E의 자식으로 H가 연결되었는지 간접 확인

			// Case 3: 자식이 둘인 노드 삭제 ('E')
			bst.delete_key('E'); // 후임자(successor)인 'H'가 'E'의 자리를 대체
			Assert::AreEqual(5, bst.size(), L"Size should be 5 after deleting a node with two children.");
			Assert::ExpectException<std::runtime_error>([&] { bst.get('E'); }, L"Node 'E' should be deleted.");
			Assert::AreEqual(6, bst.get('H'), L"'H' should replace 'E', its value should be 6.");
		}

		TEST_METHOD(TestKeys)
		{
			// 5. keys() 테스트
			Bst<char, int> bst;
			populate_test_tree(bst); // Keys: A, C, E, H, M, R, S, X

			// Case 1: 모든 키 가져오기
			std::vector<char> all_keys = bst.keys();
			std::vector<char> expected_all = { 'A', 'C', 'E', 'H', 'M', 'R', 'S', 'X' };
			Assert::IsTrue(all_keys == expected_all, L"keys() should return all keys in sorted order.");

			// Case 2: 범위 내의 키 가져오기
			std::vector<char> range_keys = bst.keys('F', 'T');
			std::vector<char> expected_range = { 'H', 'M', 'R', 'S' };
			Assert::IsTrue(range_keys == expected_range, L"keys('F', 'T') should return keys within the range.");

			// Case 3: 비어있는 범위
			std::vector<char> empty_range_keys = bst.keys('N', 'Q');
			Assert::IsTrue(empty_range_keys.empty(), L"keys() on an empty range should return an empty vector.");
		}
	};
}