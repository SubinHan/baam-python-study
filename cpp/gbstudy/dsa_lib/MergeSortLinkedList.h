#pragma once

#include "Node.h"

namespace gb {
	template <typename T>
	class MergeSortLinkedList {
	public:
		Node<T>* sort(Node<T>* head)
		{
			if (head == nullptr || head->next == nullptr)
			{
				return head;
			}

			Node<T>* left_head = nullptr;
			Node<T>* right_head = nullptr;
			split_list(head, &left_head, &right_head);

			left_head = sort(left_head);
			right_head = sort(right_head);

			return merge(left_head, right_head);
		}

	private:
		/**
		 *	split_list는 source를 front_ref, back_ref로 나누어 절반씩 분할하여 반환합니다.
		 *
		 *	@param source 분할할 연결 리스트입니다.
		 *	@param front_ref 분할 후, 앞의 절반에 대한 연결 리스트의 헤드입니다.
		 *	@param back_ref 분할 후, 뒤의 절반에 대한 연결 리스트의 헤드입니다.
		 */
		void split_list(Node<T>* source, Node<T>** front_ref, Node<T>** back_ref)
		{
			if (source == nullptr || source->next == nullptr)
			{
				*front_ref = source;
				*back_ref = nullptr;
				return;
			}

			Node<T>* slow = source;
			Node<T>* fast = source->next;

			while (fast != nullptr)
			{
				// ____
				fast = fast->next;
				if (fast != nullptr)
				{
					slow = slow->next;
					fast = fast->next;
				}
			}

			*front_ref = source;
			*back_ref = slow->next;
			slow->next = nullptr;
		}
		
		/**
		 *	merge는 left와 right를 병합하여 하나의 연결 리스트로 만든 뒤 그 헤드를 반환합니다.
		 */
		Node<T>* merge(Node<T>* left, Node<T>* right)
		{
            // 더미 노드를 사용하면 시작 부분의 예외 처리가 간결해집니다.
            Node<T> dummy_head(T{});
            Node<T>* tail = &dummy_head;

            while (left != nullptr && right != nullptr)
            {
                if (left->data <= right->data)
                {
					// ____
                    tail->next = left;
                    left = left->next;
                }
                else
                {
					// ____
                    tail->next = right;
                    right = right->next;
                }
                tail = tail->next;
            }

            // 둘 중 하나에 남은 노드들을 이어 붙입니다.
            tail->next = (left != nullptr) ? left : right;

            // 더미 노드 다음이 실제 병합된 리스트의 시작입니다.
            return dummy_head.next;
		}
	};
}