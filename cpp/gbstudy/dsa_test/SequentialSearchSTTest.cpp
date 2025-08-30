#include "pch.h"
#include "CppUnitTest.h"

#include "../dsa_lib/SequentialSearchST.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gb;

namespace UnitTest
{
	TEST_CLASS(SequentialSearchSTTest)
	{
	public:
		
		TEST_METHOD(PutAndGetNewKey)
		{
			// 준비 (Arrange)
			SequentialSearchST<char, int> st;

			// 실행 (Act)
			st.put('A', 10);
			int* result = st.get('A');

			// 검증 (Assert)
			Assert::IsNotNull(result, L"Getting an existing key should not return null.");
			Assert::AreEqual(10, *result, L"The value for key 'A' should be 10.");
		}

		TEST_METHOD(UpdateExistingKey)
		{
			// 준비
			SequentialSearchST<std::string, double> st;
			st.put("pi", 3.14);

			// 실행
			st.put("pi", 3.14159);
			double* result = st.get("pi");

			// 검증
			Assert::IsNotNull(result, L"Getting an updated key should not return null.");
			Assert::AreEqual(3.14159, *result, L"The value for key 'pi' should be updated.");
		}

		TEST_METHOD(GetNonExistentKey)
		{
			// 준비
			SequentialSearchST<int, std::string> st;
			st.put(1, "one");

			// 실행
			std::string* result = st.get(2);

			// 검증
			Assert::IsNull(result, L"Getting a non-existent key should return null.");
		}

		TEST_METHOD(ImageTraceTestCase)
		{
			// 준비: 이미지의 시나리오를 재현합니다.
			SequentialSearchST<char, int> st;
			char keys[] =   { 'S', 'E', 'A', 'R', 'C', 'H', 'E', 'X', 'A', 'M', 'P', 'L', 'E' };
			int values[] =  { 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12  };

			// 실행: 순서대로 put 연산을 수행합니다.
			for (int i = 0; i < 13; ++i)
			{
				st.put(keys[i], values[i]);
			}

			// 검증: 이미지의 최종 상태와 일치하는지 확인합니다.
			// 1. 변경된 값 확인
			int* val_e = st.get('E');
			Assert::IsNotNull(val_e, L"Key 'E' should exist.");
			Assert::AreEqual(12, *val_e, L"Final value for 'E' should be 12.");

			int* val_a = st.get('A');
			Assert::IsNotNull(val_a, L"Key 'A' should exist.");
			Assert::AreEqual(8, *val_a, L"Final value for 'A' should be 8.");

			// 2. 변경되지 않은 값 확인
			int* val_s = st.get('S');
			Assert::IsNotNull(val_s, L"Key 'S' should exist.");
			Assert::AreEqual(0, *val_s, L"Value for 'S' should remain 0.");

			int* val_l = st.get('L');
			Assert::IsNotNull(val_l, L"Key 'L' should exist.");
			Assert::AreEqual(11, *val_l, L"Value for 'L' should be 11.");

			// 3. 존재하지 않는 키 확인
			int* val_z = st.get('Z');
			Assert::IsNull(val_z, L"Key 'Z' should not exist and return null.");
		}
	};
}