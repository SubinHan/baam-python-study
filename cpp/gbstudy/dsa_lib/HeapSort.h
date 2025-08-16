#pragma once
#include "Sort.h" // 기본 클래스 포함

namespace gb
{
	template <typename T>
	class HeapSort : public Sort<T>
	{
	public:
	    // 힙 정렬을 수행하는 메인 함수
	    void sort(T arr[], int n) override {
	        // 1. 힙 구성(Heap Construction) 단계
	        // 배열의 중간(마지막 부모 노드)부터 시작하여 루트까지 sink를 호출하여
	        // 배열 전체를 최대 힙(max-heap) 상태로 만듭니다.
	        for (int k = n / 2 - 1; k >= 0; k--) {
	            sink(arr, k, n);
	        }

	        // 2. 정렬 제거(Sortdown) 단계
	        // 힙의 크기를 1씩 줄여나가면서 정렬을 완성합니다.
	        for (int i = n - 1; i > 0; i--) {
	            // 현재 힙의 최대값(arr[0])을 힙의 마지막 원소와 교환합니다.
	            this->swap(arr, 0, i);
	            
	            // 힙의 크기를 줄이고(i), 루트(0)에서 sink를 호출하여
	            // 힙 속성을 복원합니다.
	            sink(arr, 0, i);
	        }
	    }

	private:
	    // 특정 노드(k)를 아래로 내려보내 힙 속성을 만족시키는 함수
	    // n은 현재 힙의 크기를 나타냅니다.
	    void sink(T arr[], int k, int n) {
	        // 자식 노드가 존재하는 동안 반복 (왼쪽 자식 기준)
	        while (2 * k + 1 < n) {
	            int child = 2 * k + 1; // 왼쪽 자식 인덱스

	            // 오른쪽 자식이 존재하고, 왼쪽 자식보다 크다면 오른쪽 자식을 선택
	            if (child + 1 < n && arr[child] < arr[child + 1]) {
	                child++;
	            }

	            // 부모(k)가 선택된 자식보다 크거나 같으면 힙 속성이 만족된 상태이므로 종료
	            if (!(arr[k] < arr[child])) {
	                break;
	            }

	            // 부모와 자식의 위치를 교환하고, 계속 아래로 내려갑니다.
	            this->swap(arr, k, child);
	            k = child;
	        }
	    }
	};
}