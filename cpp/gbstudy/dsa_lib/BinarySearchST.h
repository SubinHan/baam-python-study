#pragma once

namespace gb {

	/**
	 * @brief 정렬된 배열과 이진 탐색을 사용하는 심볼 테이블 구현
	 * @tparam Key 키의 타입. 비교 가능해야 합니다 (<, >, == 연산자 필요).
	 * @tparam Value 값의 타입
	 */
	template <typename Key, typename Value>
	class BinarySearchST {
	private:
		Key* keys;      // 키를 저장하는 배열
		Value* values;  // 값을 저장하는 배열
		int count;      // 현재 저장된 키-값 쌍의 수
		int capacity;   // 배열의 현재 용량

		/**
		 * @brief 배열의 크기를 조절합니다.
		 * @param new_capacity 새로운 용량
		 */
		void resize(int new_capacity) {
			Key* temp_keys = new Key[new_capacity];
			Value* temp_values = new Value[new_capacity];

			for (int i = 0; i < count; ++i) {
				temp_keys[i] = keys[i];
				temp_values[i] = values[i];
			}

			delete[] keys;
			delete[] values;

			keys = temp_keys;
			values = temp_values;
			capacity = new_capacity;
		}

	public:
		/**
		 * @brief 주어진 용량으로 심볼 테이블을 생성합니다.
		 * @param initial_capacity 초기 배열 용량
		 */
		explicit BinarySearchST(int initial_capacity) {
			capacity = initial_capacity;
			keys = new Key[capacity];
			values = new Value[capacity];
			count = 0;
		}

		// 소멸자
		~BinarySearchST() {
			delete[] keys;
			delete[] values;
		}

		// 복사 및 대입을 금지하여 메모리 문제를 방지합니다.
		BinarySearchST(const BinarySearchST&) = delete;
		BinarySearchST& operator=(const BinarySearchST&) = delete;

		/**
		 * @brief 테이블에 저장된 키-값 쌍의 수를 반환합니다.
		 */
		int size() const {
			return count;
		}

		/**
		 * @brief 테이블이 비어있는지 확인합니다.
		 */
		bool is_empty() const {
			return count == 0;
		}

		/**
		 * @brief 주어진 키보다 작은 키의 수를 반환합니다 (이진 탐색).
		 * @param key 순위를 찾을 키
		 * @return 주어진 키의 순위
		 */
		int rank(const Key& key) const {
			int lo = 0, hi = count - 1;
			while (lo <= hi) {
				int mid = lo + (hi - lo) / 2;
				if (key < keys[mid]) {
					hi = mid - 1;
				}
				else if (key > keys[mid]) {
					lo = mid + 1;
				}
				else {
					return mid; // 키를 찾음
				}
			}
			return lo; // 키를 못 찾은 경우, 키가 삽입될 위치(lo)가 순위가 됨
		}

		/**
		 * @brief 주어진 키와 연관된 값을 반환합니다.
		 * @param key 검색할 키
		 * @return 값에 대한 포인터. 키가 없으면 nullptr.
		 */
		Value* get(const Key& key) {
			if (is_empty()) {
				return nullptr;
			}
			int i = rank(key);
			if (i < count && keys[i] == key) {
				return &values[i]; // 탐색 히트
			}
			return nullptr; // 탐색 미스
		}

		/**
		 * @brief 키-값 쌍을 테이블에 추가합니다.
		 * @param key 키
		 * @param value 값
		 */
		void put(const Key& key, const Value& value) {
			int i = rank(key);

			// 탐색 히트: 키가 이미 존재하면 값을 업데이트
			if (i < count&& keys[i] == key) {
				values[i] = value;
				return;
			}

			// 탐색 미스: 새로운 키-값 쌍을 삽입
			if (count == capacity) {
				resize(2 * capacity);
			}

			// rank 이후의 모든 요소를 한 칸씩 뒤로 이동
			for (int j = count; j > i; --j) {
				keys[j] = keys[j - 1];
				values[j] = values[j - 1];
			}

			keys[i] = key;
			values[i] = value;
			count++;
		}

		/**
		 * @brief 가장 작은 키를 반환합니다.
		 */
		const Key& min() const {
			if (is_empty()) {
				throw std::out_of_range("Symbol table is empty");
			}
			return keys[0];
		}

		/**
		 * @brief 가장 큰 키를 반환합니다.
		 */
		const Key& max() const {
			if (is_empty()) {
				throw std::out_of_range("Symbol table is empty");
			}
			return keys[count - 1];
		}
		
		/**
		 * @brief 순위가 k인 키를 반환합니다 (k번째로 작은 키).
		 */
		const Key& select(int k) const {
			if (k < 0 || k >= count) {
				throw std::out_of_range("Index is out of bounds");
			}
			return keys[k];
		}

		/**
		 * @brief 주어진 키가 테이블에 있는지 확인합니다.
		 */
		bool contains(const Key& key) const {
			return get(key) != nullptr;
		}

		/**
		 * @brief key 이상인 키 중에서 가장 작은 키(ceiling)를 반환합니다.
		 * @return 키에 대한 상수 포인터. 없으면 nullptr.
		 */
		const Key* ceiling(const Key& key) const {
			int i = rank(key);
			if (i == count) {
				return nullptr; // 모든 키가 key보다 작음
			}
			return &keys[i];
		}

		/**
		 * @brief key 이하인 키 중에서 가장 큰 키(floor)를 반환합니다.
		 * @return 키에 대한 상수 포인터. 없으면 nullptr.
		 */
		const Key* floor(const Key& key) const {
			int i = rank(key);
			if (i < count && keys[i] == key) {
				return &keys[i]; // 정확히 일치
			}
			if (i == 0) {
				return nullptr; // 모든 키가 key보다 큼
			}
			return &keys[i - 1];
		}

		/**
		 * @brief 주어진 키와 그와 연관된 값을 삭제합니다.
		 */
		void delete_key(const Key& key) {
			if (is_empty() || !contains(key)) {
				return;
			}

			int i = rank(key);
			// i 뒤의 모든 요소를 한 칸씩 앞으로 이동
			for (int j = i; j < count - 1; ++j) {
				keys[j] = keys[j + 1];
				values[j] = values[j + 1];
			}
			count--;

			// 배열이 너무 비어있으면 크기를 줄임
			if (count > 0 && count == capacity / 4) {
				resize(capacity / 2);
			}
		}
	};

} // namespace gb