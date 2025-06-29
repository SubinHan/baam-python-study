from GBArray import GBArray

class GBVariableArrayStack:
    def __init__(self, initial_capacity=4):
        if initial_capacity <= 0:
            raise ValueError("Initial capacity must be greater than 0")
        self._data = GBArray(initial_capacity)
        self._capacity = initial_capacity
        self._top = 0

    def _resize(self):
        # resize를 하는 방법은 결국:
        # 1) 더 큰 array를 할당
        # 2) 큰 array에, 기존의 array 값들을 복사
        new_capacity = self._capacity * 2
        new_data = GBArray(new_capacity)
        
        # 기존의 array 값들을 옮겨줘야 함.
        for i in range(self._top):
            new_data[i] = self._data[i]

        self._data = new_data
        self._capacity = new_capacity


    def push(self, value):
        if self._top >= self._capacity:
            self._resize()
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
        return f"VariableLengthStack({[self._data[i] for i in range(self._top)]})"
    
if __name__ == "__main__":
    stack = GBVariableArrayStack(2)
    stack.push(1)
    stack.push(2)
    stack.push(3)  # 자동 resize 발생
    stack.push(4)
    print(stack)  # VariableLengthStack([1, 2, 3, 4])
    print(stack.pop())  # 4
    print(stack.peek())  # 3

    for i in range(5000):
        stack.push(i)