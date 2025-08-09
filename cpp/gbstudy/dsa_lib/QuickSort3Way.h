#pragma once

#include "Sort.h"       // 부모 클래스
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // 난수 시드 생성

namespace gb
{

	/**
	 * @brief 3-way 퀵 정렬 클래스. 중복 키가 많은 경우에 효과적입니다.
	 * @tparam T 정렬할 데이터 타입
	 */
	template <typename T>
	class QuickSort3Way : public Sort<T>
	{
	public:
		/**
		 * @brief 배열을 3-way 퀵 정렬합니다.
		 * @param arr 정렬할 배열
		 * @param n 배열의 크기
		 */
		void sort(T arr[], int n) override
		{
			// 최악의 경우를 피하기 위해 배열을 무작위로 섞습니다.
			unsigned seed = 
				std::chrono::system_clock::now()
				.time_since_epoch()
				.count();
			std::shuffle(
				arr, 
				arr + n, 
				std::default_random_engine(seed)
			);

			sort_internal(arr, 0, n - 1);
		}

	private:
		/**
		 * @brief arr[low..high] 범위를 재귀적으로 3-way 퀵 정렬합니다.
		 */
		void sort_internal(T arr[], int low, int high)
		{
			// 기저 사례: 배열 크기가 1 이하이면 종료
			if (high <= low)
			{
				return;
			}

			// 3-way 파티셔닝을 위한 포인터와 피벗 설정
			int lt = low;       // 피벗보다 작은 부분의 끝
			int i = low + 1;    // 현재 탐색 위치
			int gt = high;      // 피벗보다 큰 부분의 시작
			T pivot = arr[low];

			// 파티셔닝 루프: i 포인터가 gt 포인터를 넘어설 때까지 반복
			while (i <= gt)
			{
				if (arr[i] < pivot)
				{
					// arr[i]가 피벗보다 작으면 lt 섹션으로 보냄
					this->swap(arr, lt++, i++);
				}
				else if (arr[i] > pivot)
				{
					// arr[i]가 피벗보다 크면 gt 섹션으로 보냄
					// i는 증가시키지 않음 (바꿔온 gt 위치의 값을 다시 확인해야 함)
					this->swap(arr, i, gt--);
				}
				else // arr[i] == pivot
				{
					// arr[i]가 피벗과 같으면 i만 증가시켜 피벗 섹션에 포함
					i++;
				}
			}

			// 파티셔닝 후, 3개의 부분으로 나뉨:
			// arr[low..lt-1] < pivot = arr[lt..gt] < arr[gt+1..high]

			// 피벗보다 작은 부분과 큰 부분을 재귀적으로 정렬
			sort_internal(arr, low, lt - 1);
			sort_internal(arr, gt + 1, high);
		}
	};

}