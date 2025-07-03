class GBNode:
    def __init__(self, item, next_node=None):
        self.item = item
        self.next = next_node

    def __repr__(self):
        return f"GBNode({self.item})"
    

if __name__ == "__main__":
    # 노드 생성
    node1 = GBNode('A')
    node2 = GBNode('B')
    node3 = GBNode('C')
    # 노드 연결
    node1.next = node2
    node2.next = node3

    # 리스트 순회 출력
    print("Simple linked list using GBNode:")
    current = node1
    while current:
        end = " -> " if current.next else "\n"
        print(current.item, end=end)
        current = current.next