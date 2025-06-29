from GBNode import GBNode

class GBLinkedListStack:
    def __init__(self):
        self._head = None  # 루트 노드
        self._size = 0

    def push(self, value):
        new_node = GBNode(value, self._head)
        self._head = new_node
        self._size += 1

    def pop(self):
        if self._head is None:
            raise IndexError("Pop from empty stack")
        item = self._head.item
        self._head = self._head.next
        self._size -= 1
        return item

    def peek(self):
        if self._head is None:
            raise IndexError("Peek from empty stack")
        return self._head.item

    def is_empty(self):
        return self._head is None

    def __len__(self):
        return self._size

    def __repr__(self):
        items = []
        current = self._head
        while current is not None:
            items.append(current.item)
            current = current.next
        return f"LinkedStack({items})"
    
if __name__ == "__main__":
    stack = GBLinkedListStack()
    stack.push(10)
    stack.push(20)
    stack.push(30)
    print(stack)        # LinkedStack([30, 20, 10])
    print(stack.pop())  # 30
    print(stack.peek()) # 20
    print(len(stack))   # 2