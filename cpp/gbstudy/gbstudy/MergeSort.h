#pragma once

#include "Sort.h"

namespace gb
{
	template <typename T>
	class MergeSort : public Sort<T> {

	public:
		// 소멸자에서 동적 할당된 메모리를 해제합니다.
		~MergeSort() override {
			if (aux != nullptr) {
				delete[] aux;
			}
		}

		// GBSort의 순수 가상 함수를 구현합니다.
		void sort(T* a, int n) override {
			// 보조 배열을 한 번만 할당합니다.
			if (aux == nullptr) {
				aux = new T[n];
			}
			_sort(a, 0, n - 1);
		}

	protected:
		// 두 정렬된 하위 배열 a[lo..mid]와 a[mid+1..hi]를 병합합니다.
		void merge(T* a, int lo, int mid, int hi) {
			// a[lo..hi]를 aux[]로 복사
			for (int k = lo; k <= hi; k++) {
				aux[k] = a[k];
			}

			// 다시 a[]로 병합
			int i = lo;
			int j = mid + 1;
			for (int k = lo; k <= hi; k++) {
				if (i > mid) {
					a[k] = aux[j++];
				}
				else if (j > hi) {
					a[k] = aux[i++];
				}
				else if (aux[j] < aux[i]) {
					a[k] = aux[j++];
				}
				else {
					a[k] = aux[i++];
				}
			}
		}

	private:

		// a[lo..hi]를 재귀적으로 정렬합니다.
		void _sort(T* a, int lo, int hi) {
			if (hi <= lo) return;
			int mid = lo + (hi - lo) / 2;
			_sort(a, lo, mid);
			_sort(a, mid + 1, hi);
			merge(a, lo, mid, hi);
		}

	protected:
		// 정렬에 필요한 보조 배열
		T* aux = nullptr;
	};
}
