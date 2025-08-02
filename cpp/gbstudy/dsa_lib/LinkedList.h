#pragma once

#include "Node.h"
#include <iostream>
#include <vector>

namespace gb
{
	template <typename T>
    class LinkedList {
    private:
        Node<T>* head;
        int count;

        // 인덱스에 해당하는 노드를 반환하는 private 헬퍼 함수
        // Python 코드처럼 음수 인덱스를 지원합니다.
        Node<T>* get_node(int index) const {
            if (index < 0) {
                index += count;
            }
            if (index < 0 || index >= count) {
                throw std::out_of_range("Index out of range");
            }

            Node<T>* current = head;
            for (int i = 0; i < index; ++i) {
                current = current->next;
            }
            return current;
        }

    public:
        // 생성자
        LinkedList() : head(nullptr), count(0) {}

        // 소멸자: 모든 노드의 메모리를 해제합니다.
        ~LinkedList() {
            Node<T>* current = head;
            while (current != nullptr) {
                Node<T>* next_node = current->next;
                delete current;
                current = next_node;
            }
        }

        // 복사 생성자 (깊은 복사)
        LinkedList(const LinkedList& other) : head(nullptr), count(0) {
            Node<T>* current_other = other.head;
            while (current_other != nullptr) {
                append(current_other->data);
                current_other = current_other->next;
            }
        }

        // 복사 대입 연산자 (깊은 복사)
        LinkedList& operator=(const LinkedList& other) {
            if (this == &other) { // 자기 자신에 대한 대입 방지
                return *this;
            }

            // 기존 리스트 삭제
            Node<T>* current = head;
            while (current != nullptr) {
                Node<T>* next_node = current->next;
                delete current;
                current = next_node;
            }
            head = nullptr;
            count = 0;

            // other 리스트를 깊은 복사
            Node<T>* current_other = other.head;
            while (current_other != nullptr) {
                append(current_other->data);
                current_other = current_other->next;
            }
            return *this;
        }

        // 이동 생성자
        LinkedList(LinkedList&& other) noexcept : head(other.head), count(other.count) {
            // 원본 객체의 소유권을 뺏어오고, 원본은 비워준다.
            other.head = nullptr;
            other.count = 0;
        }

        // 이동 대입 연산자
        LinkedList& operator=(LinkedList&& other) noexcept {
            if (this == &other) {
                return *this;
            }

            // 기존 리스트 메모리 해제
            Node<T>* current = head;
            while (current != nullptr) {
                Node<T>* next_node = current->next;
                delete current;
                current = next_node;
            }

            // other의 소유권을 가져온다.
            head = other.head;
            count = other.count;

            // 원본은 비워준다.
            other.head = nullptr;
            other.count = 0;

            return *this;
        }

        Node<T>* get_head() const {
            return head;
        }

        void set_head(Node<T>* new_head) {
            // 기존 head는 관리하지 않으므로, 호출하는 쪽에서 메모리 관리에 유의해야 합니다.
            head = new_head;
        }

        // 리스트 끝에 새 노드를 추가합니다.
        void append(T data) {
            Node<T>* new_node = new Node<T>(data);
            if (head == nullptr) {
                head = new_node;
            } else {
                Node<T>* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = new_node;
            }
            count++;
        }

        // 특정 인덱스의 노드를 삭제합니다.
        void remove_at(int index) {
            if (index < 0) {
                index += count;
            }
            if (index < 0 || index >= count) {
                throw std::out_of_range("Index out of range");
            }

            Node<T>* to_delete = nullptr;
            if (index == 0) {
                to_delete = head;
                head = head->next;
            } else {
                Node<T>* prev = get_node(index - 1);
                to_delete = prev->next;
                prev->next = to_delete->next;
            }
            delete to_delete;
            count--;
        }

        // 리스트의 크기를 반환합니다.
        int size() const {
            return count;
        }

        // 인덱스를 사용하여 데이터에 접근합니다 (읽기/쓰기).
        T& operator[](int index) {
            return get_node(index)->data;
        }
        
        // const 버전의 operator[] (읽기 전용).
        const T& operator[](int index) const {
            return get_node(index)->data;
        }

        // std::vector로부터 리스트를 생성하는 헬퍼 함수
        static LinkedList<T> from_vector(const std::vector<T>& values) {
            LinkedList<T> list;
            for (const T& val : values) {
                list.append(val);
            }
            return list;
        }

        // 리스트를 std::vector로 변환하는 헬퍼 함수
        std::vector<T> to_vector() const {
            std::vector<T> vec;
            Node<T>* current = head;
            while (current != nullptr) {
                vec.push_back(current->data);
                current = current->next;
            }
            return vec;
        }

        // ostream 출력을 위한 friend 함수 선언
        template <typename U>
        friend std::ostream& operator<<(std::ostream& os, const LinkedList<U>& list);
    };

}