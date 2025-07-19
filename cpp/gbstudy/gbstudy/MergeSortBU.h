#pragma once

#include "MergeSort.h"
#include <algorithm> // std::min을 사용하기 위해 포함

namespace gb
{

	template <typename T>
	class MergeSortBU : public MergeSort<T> {
	public:
		// MergeSort의 소멸자가 가상 소멸자이므로 자식 클래스의 소멸자도 자동으로 가상이 됩니다.
		// 별도의 동적 할당 멤버가 없으므로 소멸자를 명시적으로 작성할 필요는 없습니다.

		/**
		 * @brief 배열을 Bottom-Up(상향식) 병합 정렬을 사용하여 오름차순으로 정렬합니다.
		 * 재귀를 사용하지 않고 반복문으로 정렬을 수행합니다.
		 * @param a 정렬할 배열
		 * @param n 배열의 크기
		 */
		void sort(T* a, int n) override {
			// 보조 배열을 한 번만 할당합니다.
			// 부모 클래스인 MergeSort에 aux 포인터가 protected로 선언되어 있어야 접근 가능합니다.
			// 만약 private이라면, 이 클래스에서 별도로 aux를 선언하거나 부모 클래스의 접근 지정자를 변경해야 합니다.
			// 여기서는 부모의 aux를 사용할 수 있다고 가정합니다.
			if (this->aux == nullptr) {
				this->aux = new T[n];
			}

			// sz는 병합할 하위 배열의 크기를 의미합니다. 1, 2, 4, 8, ... 순으로 증가합니다.
			for (int sz = 1; sz < n; sz = sz + sz) {
				// lo는 병합할 두 하위 배열 중 첫 번째 배열의 시작 인덱스입니다.
				for (int lo = 0; lo < n - sz; lo += sz + sz) {
					// mid: 첫 번째 하위 배열의 끝 인덱스
					int mid = lo + sz - 1;
					// hi: 두 번째 하위 배열의 끝 인덱스
					// 마지막 하위 배열이 배열의 전체 크기를 넘어가지 않도록 std::min()을 사용합니다.
					int hi = std::min(lo + sz + sz - 1, n - 1);
					
					this->merge(a, lo, mid, hi);
				}
			}
		}
	};

}