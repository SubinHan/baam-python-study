class EvenIndexIterator:
    def __init__(self, data):
        self.data = data
        self.index = 0

    def __iter__(self):
        return self

    def __next__(self):
        if self.index > len(self.data):
            raise StopIteration
        
        current_index = self.index
        self.index += 2
        return self.data[current_index]


my_list = [3, 8, 7, 10, 15, 6, 9]

for i in EvenIndexIterator(my_list):
    print(i)