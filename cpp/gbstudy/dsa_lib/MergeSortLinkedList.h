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

		Node<T>* merge(Node<T>* left, Node<T>* right)
		{
			if (left == nullptr)
			{
				return right;
			}
			if (right == nullptr)
			{
				return left;
			}

			Node<T>* result = nullptr;
			if (left->data <= right->data)
			{
				result = left;
				result->next = merge(left->next, right);
			}
			else
			{
				result = right;
				result->next = merge(left, right->next);
			}
			return result;
		}
	};
}