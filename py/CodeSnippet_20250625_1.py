from GBSort import GBSort

class MyExampleSort(GBSort):
    def sort(self, data):
        pass

sorter = MyExampleSort()
data = [5, 2, 4, 6, 1, 3]
print("Before:", data)
sorter.sort(data)

# ASSERTION FAIL:
# MyExampleSort는 sort()에서 정렬하지 않음.
assert sorter.is_sorted(data), 'Sorting Failed'

print("After: ", data)