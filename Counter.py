class Counter:
    def __init__(self, id, max):
        self.id = id
        self.max = max
        self.count = 0

    def increment(self):
        self.count += 1
    
    def value(self):
        return self.count
    
    def to_string(self):
        return self.id
    
c = Counter("id", 100)
c.increment()

c1 = c
c1.increment()

print(c.value())