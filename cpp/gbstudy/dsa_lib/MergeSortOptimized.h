#pragma once

#include "Sort.h"     // Sort 기본 클래스
#include <algorithm>  // std::copy, std::min 등 사용

namespace gb
{
    /**
     * @brief 병합 정렬(Merge Sort)의 최적화된 구현 클래스.
     * - 작은 배열에 대해서는 삽입 정렬(Cutoff)을 사용하여 성능을 향상시킵니다.
     * - 재귀 레벨마다 배열 역할을 교환하여 불필요한 복사 비용을 제거합니다.
     * - 이미 정렬된 부분 배열은 병합을 생략하여 효율을 높입니다.
     * @tparam T 정렬할 데이터의 타입
     */
    template <typename T>
    class MergeSortOptimized : public Sort<T>
    {
    private:
        // 삽입 정렬로 전환할 배열 크기의 임계값
        static const int INSERTION_SORT_CUTOFF = 7;

        /**
         * @brief arr[lo..hi] 범위를 삽입 정렬로 정렬합니다.
         */
        void insertion_sort(T* a, int lo, int hi)
        {
            for (int i = lo + 1; i <= hi; ++i)
            {
                T key = a[i];
                int j = i - 1;
                while (j >= lo && a[j] > key)
                {
                    a[j + 1] = a[j];
                    j--;
                }
                a[j + 1] = key;
            }
        }

        /**
         * @brief src[lo..mid]와 src[mid+1..hi]를 병합하여 dst[lo..hi]에 저장합니다.
         * 이 함수에서는 추가적인 배열 복사가 발생하지 않습니다.
         */
        void merge(T* src, T* dst, int lo, int mid, int hi)
        {
            int i = lo;
            int j = mid + 1;

            for (int k = lo; k <= hi; ++k)
            {
                if (i > mid)               // 왼쪽 절반을 모두 소진한 경우
                {
                    dst[k] = src[j++];
                }
                else if (j > hi)           // 오른쪽 절반을 모두 소진한 경우
                {
                    dst[k] = src[i++];
                }
                else if (src[j] < src[i])  // 오른쪽 원소가 왼쪽 원소보다 작은 경우
                {
                    dst[k] = src[j++];
                }
                else                       // 왼쪽 원소가 오른쪽 원소보다 작거나 같은 경우
                {
                    dst[k] = src[i++];
                }
            }
        }

        /**
         * @brief src 배열의 [lo..hi] 범위를 정렬하여 dst 배열의 [lo..hi]에 저장합니다.
         * 재귀 호출 시마다 src와 dst의 역할을 바꿉니다.
         */
        void sort_internal(T* src, T* dst, int lo, int hi)
        {
            // 개선점 1: Cutoff 적용
            // 배열의 크기가 임계값보다 작으면 더 빠른 삽입 정렬을 사용합니다.
            if (hi <= lo + INSERTION_SORT_CUTOFF - 1)
            {
                insertion_sort(dst, lo, hi);
                return;
            }

            int mid = lo + (hi - lo) / 2;

            // 재귀 호출: src와 dst의 역할을 서로 바꿔서 전달합니다.
            // 즉, 하위 레벨에서는 dst를 src로 삼아 정렬 결과를 src에 저장합니다.
            sort_internal(dst, src, lo, mid);
            sort_internal(dst, src, mid + 1, hi);

            // 개선점 2: 이미 정렬된 경우 병합 생략
            // 왼쪽 절반의 마지막 원소가 오른쪽 절반의 첫 원소보다 작거나 같으면
            // 이미 전체가 정렬된 상태이므로 병합(merge) 과정을 건너뛸 수 있습니다.
            // 이 경우, src의 내용을 dst로 복사하기만 하면 됩니다.
            if (src[mid] <= src[mid + 1])
            {
                std::copy(src + lo, src + hi + 1, dst + lo);
                return;
            }

            // 병합 단계: src에서 데이터를 읽어와 정렬 후 dst에 씁니다.
            merge(src, dst, lo, mid, hi);
        }

    public:
        /**
         * @brief 배열을 최적화된 병합 정렬을 사용하여 오름차순으로 정렬합니다.
         * 최초에 한 번만 데이터를 보조 배열로 복사합니다.
         * @param a 정렬할 배열
         * @param n 배열의 크기
         */
        void sort(T* a, int n) override
        {
            if (n <= 1) return;

            // 보조 배열을 만들고, 원본 배열의 내용을 한 번만 복사합니다.
            T* aux = new T[n];
            std::copy(a, a + n, aux);

            // aux를 원본(src)으로 하여 a를 목적지(dst)로 정렬을 시작합니다.
            sort_internal(aux, a, 0, n - 1);

            // 동적 할당된 메모리를 해제합니다.
            delete[] aux;
        }
    };

} // namespace gb