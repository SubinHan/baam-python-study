#pragma once

namespace gb
{

	template <typename T>
	class Sort {
	public:
		virtual ~Sort() {}

		// 순수 가상 함수로, 자식 클래스에서 반드시 구현해야 합니다.
		virtual void sort(T arr[], int n) = 0;

	protected:
		// 두 원소의 위치를 바꾸는 swap 함수
		void swap(T arr[], int i, int j) {
			T temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}

		// 배열이 정렬되었는지 확인하는 디버깅용 함수
		bool is_sorted(T arr[], int n) {
			for (int i = 1; i < n; i++) {
				if (arr[i] < arr[i - 1]) {
					return false;
				}
			}
			return true;
		}
	};

}
