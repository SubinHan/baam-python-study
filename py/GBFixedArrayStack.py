from GBArray import GBArray

class GBFixedArrayStack:
    def __init__(self, capacity):
        self._data = GBArray(capacity)
        self._capacity = capacity
        self._top = 0  # 다음에 push될 위치

    def push(self, value):
        if self._top >= self._capacity:
            raise OverflowError("Stack is full")
        self._data[self._top] = value
        self._top += 1

    def pop(self):
        if self._top == 0:
            raise IndexError("Pop from empty stack")
        self._top -= 1
        return self._data[self._top]

    def peek(self):
        if self._top == 0:
            raise IndexError("Peek from empty stack")
        return self._data[self._top - 1]

    def is_empty(self):
        return self._top == 0

    def __len__(self):
        return self._top

    def __repr__(self):
        return f"FixedLengthStack({[self._data[i] for i in range(self._top)]})"
    
if __name__ == "__main__":
    stack2 = GBFixedArrayStack(5)

    stack = GBFixedArrayStack(3)
    stack.push(10)

    # stack._top == 1

    stack.push(20)

    # stack._top == 2
    print(stack.peek())  # 20
    stack.push(30)
    print(stack.pop())  # 30
    print(stack.pop())  # 20
    print(stack.is_empty())  # False
    print(stack.pop())  # 10
    print(stack.pop())  # IndexError: Pop from empty stack