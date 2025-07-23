#pragma once

#include <stdexcept> // std::out_of_range 사용
#include <algorithm> // std::copy 사용

namespace gb
{
	/**
	 * @brief std::vector와 유사하게 동작하는 동적 크기 조절 배열 클래스.
	 * @tparam T 배열에 저장될 요소의 타입
	 */
	template <typename T>
	class ResizingArray {
	private:
		T* data;      // 데이터를 저장할 포인터
		int array_size;     // 현재 저장된 요소의 개수
		int array_capacity; // 할당된 메모리의 총 용량

		/**
		 * @brief 내부 배열의 크기를 조절하는 приват 함수.
		 * @param new_capacity 새로 할당할 용량
		 */
		void resize(int new_capacity) {
			// 0보다 작은 용량으로 조절하려는 경우 방지
			if (new_capacity < 1) new_capacity = 1;

			T* new_data = new T[new_capacity];
			
			// 기존 데이터를 새로운 배열로 복사합니다.
			// m_size와 new_capacity 중 더 작은 값만큼만 복사해야 안전합니다.
			int elements_to_copy = (array_size < new_capacity) ? array_size : new_capacity;
			for (int i = 0; i < elements_to_copy; ++i) {
				new_data[i] = data[i];
			}

			delete[] data; // 기존 메모리 해제
			data = new_data;
			array_capacity = new_capacity;

			// 만약 리사이즈 후 용량보다 요소 개수가 많았다면, 요소 개수를 용량에 맞춥니다.
			if (array_size > array_capacity) {
				array_size = array_capacity;
			}
		}

	public:
		// --- 생성자 및 소멸자 ---

		/**
		 * @brief 기본 생성자. 초기 용량 1로 시작합니다.
		 */
		ResizingArray() : data(new T[1]), array_size(0), array_capacity(1) {}

		/**
		 * @brief 소멸자. 할당된 메모리를 해제합니다.
		 */
		~ResizingArray() {
			delete[] data;
		}

		// --- 복사 및 할당 ---

		/**
		 * @brief 복사 생성자. 깊은 복사를 수행합니다.
		 */
		ResizingArray(const ResizingArray& other)
			: data(new T[other.array_capacity]), array_size(other.array_size), array_capacity(other.array_capacity) {
			for (int i = 0; i < array_size; ++i) {
				data[i] = other.data[i];
			}
		}

		/**
		 * @brief 복사 할당 연산자.
		 */
		ResizingArray& operator=(const ResizingArray& other) {
			if (this == &other) { // 자기 자신에 대한 할당 방지
				return *this;
			}

			delete[] data; // 기존 데이터 해제

			array_size = other.array_size;
			array_capacity = other.array_capacity;
			data = new T[array_capacity];

			for (int i = 0; i < array_size; ++i) {
				data[i] = other.data[i];
			}
			return *this;
		}

		// --- 용량 관련 함수 ---

		int size() const { return array_size; }
		int capacity() const { return array_capacity; }
		bool is_empty() const { return array_size == 0; }

		// --- 요소 조작 함수 ---

		/**
		 * @brief 배열의 끝에 요소를 추가합니다.
		 */
		void push_back(const T& item) {
			if (array_size == array_capacity) {
				resize(2 * array_capacity);
			}
			data[array_size++] = item;
		}

		/**
		 * @brief 배열의 마지막 요소를 제거합니다.
		 */
		void pop_back() {
			if (array_size == 0) {
				throw std::out_of_range("Cannot pop from an empty array.");
			}
			array_size--;

			// Java 코드와 같이, 배열이 너무 비면(1/4) 크기를 줄입니다.
			if (array_size > 0 && array_size == array_capacity / 4) {
				resize(array_capacity / 2);
			}
		}
		
		// --- 요소 접근 함수 ---

		T& operator[](int index) {
			if (index < 0 || index >= array_size) {
				throw std::out_of_range("Index out of range.");
			}
			return data[index];
		}

		const T& operator[](int index) const {
			if (index < 0 || index >= array_size) {
				throw std::out_of_range("Index out of range.");
			}
			return data[index];
		}

		// --- 이터레이터 지원 ---
        // C++의 범위 기반 for문을 사용할 수 있게 합니다.
		T* begin() { return &data[0]; }
		const T* begin() const { return &data[0]; }
		T* end() { return &data[array_size]; }
		const T* end() const { return &data[array_size]; }
	};
}