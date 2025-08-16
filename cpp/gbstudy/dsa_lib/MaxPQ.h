#pragma once

#include <stdexcept> // std::out_of_range, std::overflow_error
#include <utility>   // std::swap

namespace gb
{
	template <typename Key>
	class MaxPQ {
	public:
		// 생성자: 최대 용량을 받아 우선순위 큐를 생성합니다.
		explicit MaxPQ(int max_capacity) : capacity(max_capacity), num_elements(0) {
			// 힙 구현의 편의를 위해 1-based indexing을 사용하므로,
			// 배열 크기를 capacity + 1로 할당합니다.
			priority_queue = new Key[max_capacity + 1];
		}

		// 소멸자: 동적으로 할당된 메모리를 해제합니다.
		~MaxPQ() {
			delete[] priority_queue;
		}

		// 우선순위 큐에 새로운 원소를 추가합니다.
		void insert(const Key& value) {
			if (num_elements >= capacity) {
				throw std::overflow_error("Priority queue is full");
			}
			// 1. 가장 마지막 위치에 원소를 추가합니다.
			priority_queue[++num_elements] = value;
			// 2. 힙 속성을 복원하기 위해 부모 노드와 비교하며 위로 올라갑니다.
			swim(num_elements);
		}

		// 가장 큰 원소(루트)를 제거하고 반환합니다.
		Key del_max() {
			if (is_empty()) {
				throw std::out_of_range("Priority queue is empty");
			}
			// 1. 루트 노드(최댓값)를 저장합니다.
			Key max_value = priority_queue[1];
			// 2. 가장 마지막 노드를 루트로 이동시킵니다.
			swap_elements(1, num_elements--);
			// 3. 힙 속성을 복원하기 위해 자식 노드와 비교하며 아래로 내려갑니다.
			sink(1);
			return max_value;
		}

		// 우선순위 큐가 비어있는지 확인합니다.
		bool is_empty() const {
			return num_elements == 0;
		}

		// 우선순위 큐에 포함된 원소의 개수를 반환합니다.
		int size() const {
			return num_elements;
		}

	private:
		// 두 원소의 우선순위를 비교합니다. (i < j)
		bool less(int i, int j) const {
			return priority_queue[i] < priority_queue[j];
		}

		// 두 원소의 위치를 교환합니다.
		void swap_elements(int i, int j) {
			std::swap(priority_queue[i], priority_queue[j]);
		}

		// swim: 자식 노드가 부모 노드보다 클 경우, 위로 올라가며 힙을 재구성합니다.
		void swim(int k) {
			while (k > 1 && less(k / 2, k)) {
				swap_elements(k / 2, k);
				k = k / 2;
			}
		}

		// sink: 부모 노드가 자식 노드보다 작을 경우, 아래로 내려가며 힙을 재구성합니다.
		void sink(int k) {
			while (2 * k <= num_elements) {
				int child = 2 * k;
				// 두 자식 중 더 큰 자식을 선택합니다.
				if (child < num_elements && less(child, child + 1)) {
					child++;
				}
				// 부모가 자식보다 크거나 같으면 힙 속성이 만족된 상태입니다.
				if (!less(k, child)) {
					break;
				}
				// 부모와 자식의 위치를 바꾸고 계속 아래로 내려갑니다.
				swap_elements(k, child);
				k = child;
			}
		}

		Key* priority_queue; // 힙을 저장할 배열 포인터
		int capacity;        // 최대 용량
		int num_elements;    // 현재 원소 개수

	};

}