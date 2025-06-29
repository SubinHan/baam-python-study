from GBNode import GBNode

class GBQueue:
    def __init__(self):
        self.head = None
        self.tail = None
        self.size = 0

    def is_empty(self):
        """Return True if the queue is empty."""
        return self.size == 0

    def __len__(self):
        """Return the number of items in the queue."""
        return self.size

    def enqueue(self, item):
        """Add an item to the end of the queue."""
        new_node = GBNode(item)
        if self.is_empty():
            self.head = new_node
            self.tail = new_node
        else:
            self.tail.next = new_node
            self.tail = new_node
        self.size += 1

    def dequeue(self):
        """Remove and return the item from the front of the queue."""
        if self.is_empty():
            raise IndexError("dequeue from empty queue")
        item = self.head.item
        self.head = self.head.next
        if self.head is None:
            self.tail = None
        self.size -= 1
        return item

    def peek(self):
        """Return the item at the front of the queue without removing it."""
        if self.is_empty():
            raise IndexError("peek from empty queue")
        return self.head.item

    def __repr__(self):
        """Return a string representation of the queue contents."""
        items = []
        current = self.head
        while current:
            items.append(repr(current.item))
            current = current.next
        return f"GBQueue([{', '.join(items)}])"


if __name__ == "__main__":
    # 간단한 사용 사례 예제
    q = GBQueue()
    print("Is empty:", q.is_empty())
    q.enqueue(1)
    q.enqueue(2)
    q.enqueue(3)
    print("Queue after enqueues:", q)
    print("Peek at head:", q.peek())
    print("Dequeued item:", q.dequeue())
    print("Queue after dequeue:", q)
    print("Queue length:", len(q))