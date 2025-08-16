#pragma once

#include <stdexcept>    // std::invalid_argument 예외 처리를 위해 사용
#include <algorithm>    // std::shuffle 사용
#include <random>       // std::default_random_engine 사용
#include <chrono>       // 난수 시드 생성을 위해 사용

namespace gb
{

	/**
	 * @brief Quick Select 알고리즘을 구현한 클래스.
	 * 배열에서 k번째로 작은 원소를 평균 O(n) 시간 복잡도로 찾습니다.
	 * @tparam T 선택할 데이터 타입
	 */
	template <typename T>
	class QuickSelect
	{
	public:
		/**
		 * @brief arr에서 k번째로 작은 원소를 찾아 반환합니다. (k는 0-based 인덱스)
		 * @param arr 원소를 찾을 대상 배열. (내용이 변경될 수 있습니다)
		 * @param n 배열의 크기
		 * @param k 찾고자 하는 원소의 순위 (0 <= k < n)
		 * @return k번째로 작은 원소
		 * @throws std::invalid_argument k가 유효한 범위를 벗어난 경우
		 */
		T select(T arr[], int n, int k)
		{
			if (k < 0 || k >= n)
			{
				throw std::invalid_argument("k must be within the valid range of the array.");
			}

			// 이하 ____
			// 최악의 경우를 피하고 평균 O(n) 성능을 보장하기 위해 배열을 섞습니다.
			unsigned seed = 
				std::chrono::system_clock::now()
				.time_since_epoch()
				.count();
			std::shuffle(
				arr, 
				arr + n, 
				std::default_random_engine(seed));

			int low = 0;
			int high = n - 1;

			// 범위를 좁혀가며 k번째 원소를 찾습니다.
			while (high > low)
			{
				int j = partition(arr, low, high);
				if (j < k)
				{
					low = j + 1;
				}
				else if(j > k)
				{
					high = j - 1;
				}
				else
				{
					return arr[k];
				}
			}

			// 루프가 끝나면 low == high == k 이므로, arr[k]가 정답입니다.
			return arr[k];
		}

	private:
		/**
		 * @brief 두 원소의 위치를 교환하는 헬퍼 함수
		 */
		void swap(T arr[], int i, int j)
		{
			T temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}

		/**
		 * @brief arr[low..high]를 파티션하고 피벗의 최종 인덱스를 반환합니다.
		 * (QuickSort의 파티션 구현과 동일)
		 */
		int partition(T arr[], int low, int high)
		{
			int i = low;
			int j = high + 1;
			T pivot = arr[low];

			while (true)
			{
				while (arr[++i] < pivot)
				{
					if (i == high) break;
				}
				while (pivot < arr[--j])
				{
					if (j == low) break;
				}

				if (i >= j)
				{
					break;
				}
				swap(arr, i, j);
			}
			swap(arr, low, j);
			return j;
		}
	};

}