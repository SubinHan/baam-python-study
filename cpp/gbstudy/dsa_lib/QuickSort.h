#pragma once

#include "Sort.h"       // 제공된 부모 클래스
#include <algorithm>    // std::shuffle 사용
#include <random>       // std::default_random_engine 사용
#include <chrono>       // 난수 시드 생성을 위해 사용

namespace gb
{

	template <typename T>
	class QuickSort : public Sort<T>
	{
	public:
		/**
		 * @brief 배열을 퀵 정렬합니다.
		 * @param arr 정렬할 배열
		 * @param n 배열의 크기
		 */
		void sort(T arr[], int n) override
		{
			// 입력 의존성을 없애기 위해 배열을 무작위로 섞습니다. (Python의 random.shuffle)
			unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
			std::shuffle(arr, arr + n, std::default_random_engine(seed));

			// 재귀 정렬을 시작합니다.
			sort_internal(arr, 0, n - 1);
		}

	private:
		/**
		 * @brief arr[lo..hi] 범위를 재귀적으로 정렬합니다.
		 */
		void sort_internal(T arr[], int lo, int hi)
		{
			// 기저 사례: 부분 배열의 크기가 1 이하이면 종료
			if (hi <= lo)
			{
				return;
			}

			// 파티션을 수행하고 피벗의 최종 위치를 받습니다.
			int j = partition(arr, lo, hi);

			// 피벗을 기준으로 나눠진 두 부분 배열에 대해 재귀 호출
			sort_internal(arr, lo, j - 1);
			sort_internal(arr, j + 1, hi);
		}

		/**
		 * @brief arr[lo..hi]를 파티션하고 피벗의 최종 인덱스를 반환합니다.
		 * Hoare-partition scheme을 사용합니다.
		 * @return 피벗의 최종 인덱스
		 */
		int partition(T arr[], int lo, int hi)
		{
			int i = lo;
			int j = hi + 1;
			T pivot = arr[lo]; // 첫 번째 원소를 피벗으로 선택

			while (true)
			{
				// 왼쪽에서 오른쪽으로 스캔: 피벗보다 크거나 같은 원소를 찾습니다.
				i++;
				while (i <= hi && arr[i] < pivot)
				{
					i++;
				}
				
				// 오른쪽에서 왼쪽으로 스캔: 피벗보다 작거나 같은 원소를 찾습니다.
				j--;
				while (j >= lo && arr[j] > pivot)
				{
					j--;
				}
				
				// 포인터가 교차되면 루프를 탈출합니다.
				if (i >= j)
				{
					break;
				}

				// 찾은 두 원소의 위치를 교환합니다.
				this->swap(arr, i, j);
			}

			// 피벗(arr[lo])을 최종 위치(j)로 이동시킵니다.
			this->swap(arr, lo, j);

			// 피벗의 최종 위치를 반환합니다.
			return j;
		}
	};

}