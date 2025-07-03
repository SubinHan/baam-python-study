from GBNode import GBNode

class GBLinkedList:
    def __init__(self):
        self._head = None
        self._size = 0

    def append(self, value):
        """리스트 끝에 새 노드를 추가."""
        new_node = GBNode(value)
        if not self._head:
            self._head = new_node
        else:
            curr = self._head
            while curr.next:
                curr = curr.next
            curr.next = new_node
        self._size += 1

    def _get_node(self, index: int) -> GBNode:
        """인덱스에 해당하는 노드를 반환. 인덱스 범위 검사 포함."""
        if index < 0:
            index += self._size
        if index < 0 or index >= self._size:
            raise IndexError("Index out of range")
        curr = self._head
        for _ in range(index):
            curr = curr.next
        return curr

    def __len__(self) -> int:
        return self._size

    def __getitem__(self, index: int):
        """a[index] 형태로 값 조회."""
        node = self._get_node(index)
        return node.item

    def __setitem__(self, index: int, value):
        """a[index] = value 형태로 값 수정."""
        node = self._get_node(index)
        node.item = value

    def __delitem__(self, index: int):
        """del a[index] 형태로 노드 삭제."""
        if index < 0:
            index += self._size
        if index < 0 or index >= self._size:
            raise IndexError("Index out of range")
        # head 삭제
        if index == 0:
            self._head = self._head.next
        else:
            prev = self._get_node(index - 1)
            prev.next = prev.next.next
        self._size -= 1

    def __repr__(self) -> str:
        items = []
        curr = self._head
        while curr:
            items.append(curr.item)
            curr = curr.next
        return f"GBLinkedList({items})"


if __name__ == "__main__":
    lst = GBLinkedList()
    for v in [10, 20, 30]:
        lst.append(v)
    print(lst)            # GBLinkedList([10, 20, 30])
    print(len(lst))       # 3

    print(lst[1])         # 20
    lst[1] = 99
    print(lst)            # GBLinkedList([10, 99, 30])

    del lst[0]
    print(lst)            # GBLinkedList([99, 30])

    lst.append(77)
    print(lst)            # GBLinkedList([99, 30, 77])

    # 음수 인덱스도 지원
    print(lst[-1])        # 77