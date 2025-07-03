from GBSort import GBSort

class MyExampleSort(GBSort):
    pass

# ERROR:
# MyExampleSort는 sort()를 구현하지 않음.
sorter = MyExampleSort()

data = [5, 2, 4, 6, 1, 3]
print("Before:", data)
sorter.sort(data)
assert sorter.is_sorted(data), 'Sorting Failed'
print("After: ", data)