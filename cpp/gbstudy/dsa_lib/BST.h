#pragma once

#include <stdexcept>
#include <vector>

namespace gb {

template <typename Key, typename Value>
class Bst {
private:
    // 내부 노드 구조체
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        int node_count; // 이 노드를 루트로 하는 서브트리의 노드 수

        Node(const Key& key, const Value& value, int count)
            : key(key), value(value), left(nullptr), right(nullptr), node_count(count) {}
    };

    Node* root_node; // 트리의 루트 노드

    // 재귀적으로 노드들의 메모리를 해제하는 헬퍼 함수
    void clear(Node* node) {
        if (!node) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

    // 특정 노드를 루트로 하는 서브트리의 크기를 반환하는 헬퍼 함수
    int size(Node* node) const {
        return node ? node->node_count : 0;
    }

    // get()의 재귀 헬퍼 함수
    const Value* get(Node* node, const Key& key) const {
        if (!node) {
            return nullptr;
        }

        if (key < node->key) {
            return get(node->left, key);
        } else if (key > node->key) {
            return get(node->right, key);
        } else {
            return &node->value;
        }
    }

    // put()의 재귀 헬퍼 함수
    Node* put(Node* node, const Key& key, const Value& value) {
        if (!node) {
            return new Node(key, value, 1);
        }

        if (key < node->key) {
            node->left = put(node->left, key, value);
        } else if (key > node->key) {
            node->right = put(node->right, key, value);
        } else {
            node->value = value;
        }

        node->node_count = 1 + size(node->left) + size(node->right);
        return node;
    }

    // min()의 재귀 헬퍼 함수
    Node* min(Node* node) const {
        if (!node || !node->left) {
            return node;
        }
        return min(node->left);
    }

    // max()의 재귀 헬퍼 함수
    Node* max(Node* node) const {
        if (!node || !node->right) return node;
        return max(node->right);
    }

    // floor()의 재귀 헬퍼 함수
    Node* floor(Node* node, const Key& key) const {
        if (!node) {
            return nullptr;
        }
        if (key == node->key) {
            return node;
        }
        if (key < node->key) {
            return floor(node->left, key);
        }
        Node* t = floor(node->right, key);
        return t ? t : node;
    }
    
    // ceiling()의 재귀 헬퍼 함수
    Node* ceiling(Node* node, const Key& key) const {
        if (!node) {
            return nullptr;
        }
        if (key == node->key) {
            return node;
        }
        if (key > node->key) {
            return ceiling(node->right, key);
        }
        Node* t = ceiling(node->left, key);
        return t ? t : node;
    }

    // rank()의 재귀 헬퍼 함수
    int rank(Node* node, const Key& key) const {
        if (!node) {
            return 0;
        }
        if (key < node->key) {
            return rank(node->left, key);
        } else if (key > node->key) {
            return 1 + size(node->left) + rank(node->right, key);
        } else {
            return size(node->left);
        }
    }

    // select()의 재귀 헬퍼 함수
    Node* select(Node* node, int k) const {
        if (!node) {
            return nullptr;
        }
        int t = size(node->left);
        if (t > k) {
            return select(node->left, k);
        } else if (t < k) {
            return select(node->right, k - t - 1);
        } else {
            return node;
        }
    }

    // delete_min()의 재귀 헬퍼 함수
    Node* delete_min(Node* node) {
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        node->left = delete_min(node->left);
        node->node_count = 1 + size(node->left) + size(node->right);
        return node;
    }

    // delete_max()의 재귀 헬퍼 함수
    Node* delete_max(Node* node) {
        if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        node->right = delete_max(node->right);
        node->node_count = 1 + size(node->left) + size(node->right);
        return node;
    }

    // delete_key()의 재귀 헬퍼 함수
    Node* delete_key(Node* node, const Key& key) {
        if (!node) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = delete_key(node->left, key);
        } else if (key > node->key) {
            node->right = delete_key(node->right, key);
        } else {
            if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            
	        Node* successor = min(node->right);
	        node->key = successor->key;
	        node->value = successor->value;
	        node->right = delete_min(node->right);
        }

        node->node_count = 1 + size(node->left) + size(node->right);
        return node;
    }

    // keys()의 재귀 헬퍼 함수
    void keys(Node* node, std::vector<Key>& queue, const Key& lo, const Key& hi) const {
        if (!node) {
            return;
        }
        bool lo_less = lo < node->key;
        bool hi_greater = hi > node->key;

        if (lo_less) {
            keys(node->left, queue, lo, hi);
        }
        if ((lo <= node->key) && (hi >= node->key)) {
            queue.push_back(node->key);
        }
        if (hi_greater) {
            keys(node->right, queue, lo, hi);
        }
    }

public:
    Bst() : root_node(nullptr) {}

    ~Bst() {
        clear(root_node);
    }

    // 트리의 전체 크기를 반환합니다.
    int size() const {
        return size(root_node);
    }

    // 비어있는지 확인합니다.
    bool is_empty() const {
        return root_node == nullptr;
    }

    // 주어진 키에 해당하는 값을 반환합니다. (const 버전)
    // 키가 존재하지 않으면 예외를 던집니다.
    const Value& get(const Key& key) const {
        const Value* val_ptr = get(root_node, key);
        if (!val_ptr) {
            throw std::runtime_error("Key not found");
        }
        return *val_ptr;
    }

    // 키-값 쌍을 트리에 추가하거나, 이미 키가 존재하면 값을 업데이트합니다.
    void put(const Key& key, const Value& value) {
        root_node = put(root_node, key, value);
    }

    // 가장 작은 키를 반환합니다.
    Key min() const {
        if (is_empty()) {
            throw std::runtime_error("Tree is empty");
        }
        return min(root_node)->key;
    }
    
    // 가장 큰 키를 반환합니다.
    Key max() const {
        if (is_empty()) throw std::runtime_error("Tree is empty");
        return max(root_node)->key;
    }
    
    // key보다 작거나 같은 가장 큰 키를 반환합니다.
    Key floor(const Key& key) const {
        Node* result_node = floor(root_node, key);
        if (!result_node) {
             throw std::runtime_error("No key is less than or equal to the given key");
        }
        return result_node->key;
    }
    
    // key보다 크거나 같은 가장 작은 키를 반환합니다.
    Key ceiling(const Key& key) const {
        Node* result_node = ceiling(root_node, key);
        if (!result_node) {
             throw std::runtime_error("No key is less than or equal to the given key");
        }
        return result_node->key;
    }

    // 주어진 키보다 작은 키들의 개수를 반환합니다.
    int rank(const Key& key) const {
        return rank(root_node, key);
    }

    // 순위가 k인 키를 반환합니다 (0-indexed).
    Key select(int k) const {
        Node* result_node = select(root_node, k);
        if (!result_node) {
            throw std::runtime_error("Rank is out of bounds");
        }
        return result_node->key;
    }

    // 가장 작은 키를 가진 노드를 삭제합니다.
    void delete_min() {
        if (is_empty()) {
            throw std::runtime_error("Tree is empty");
        }
        root_node = delete_min(root_node);
    }

    // 가장 큰 키를 가진 노드를 삭제합니다.
    void delete_max() {
        if (is_empty()) throw std::runtime_error("Tree is empty");
        root_node = delete_max(root_node);
    }

    // 주어진 키를 가진 노드를 삭제합니다.
    void delete_key(const Key& key) {
        root_node = delete_key(root_node, key);
    }

    // 트리의 모든 키를 큐에 담아 반환합니다.
    std::vector<Key> keys() const {
        if(is_empty()) {
            return std::vector<Key>();
        }
        return keys(min(), max());
    }

    // 주어진 범위 [lo, hi]에 속하는 모든 키를 큐에 담아 반환합니다.
    std::vector<Key> keys(const Key& lo, const Key& hi) const {
        std::vector<Key> key_vector;
        keys(root_node, key_vector, lo, hi);
        return key_vector;
    }
};

} // namespace gb