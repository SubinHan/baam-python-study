#pragma once

namespace gb {

	template <typename Key, typename Value>
	class SequentialSearchST {
	private:
		// 연결 리스트 노드를 위한 private 중첩 클래스
		struct Node {
			Key key;
			Value value;
			Node* next;

			// 생성자
			Node(const Key& key, const Value& value, Node* next)
				: key(key), value(value), next(next) {
			}
		};

		Node* first_node; // 연결 리스트의 첫 번째 노드

	public:
		// 생성자: 빈 심볼 테이블을 생성합니다.
		SequentialSearchST() : first_node(nullptr) {}

		// 소멸자: 동적으로 할당된 모든 노드를 해제합니다.
		~SequentialSearchST() {
			Node* current = first_node;
			while (current != nullptr) {
				Node* temp = current;
				current = current->next;
				delete temp;
			}
		}

		/**
		 * @brief 주어진 키와 연관된 값을 반환합니다.
		 * @param key 검색할 키
		 * @return 키와 연관된 값에 대한 포인터. 키가 테이블에 없으면 nullptr를 반환합니다.
		 */
		Value* get(const Key& key) {
			// 탐색 히트: 키를 찾아 연관된 값을 반환합니다.
			for (Node* x = first_node; x != nullptr; x = x->next) {
				if (key == x->key) {
					return &(x->value); // 탐색 히트
				}
			}
			return nullptr; // 탐색 미스
		}

		/**
		 * @brief 키-값 쌍을 테이블에 추가합니다.
		 * 키가 이미 존재하면 값을 업데이트하고, 그렇지 않으면 새로운 노드를 추가합니다.
		 * @param key 키
		 * @param value 값
		 */
		void put(const Key& key, const Value& value) {
			// 탐색 히트: 키를 찾아 값을 업데이트합니다.
			for (Node* x = first_node; x != nullptr; x = x->next) {
				if (key == x->key) {
					x->value = value;
					return;
				}
			}
			// 탐색 미스: 새로운 노드를 리스트의 맨 앞에 추가합니다.
			first_node = new Node(key, value, first_node);
		}
	};

}
