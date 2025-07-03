from GBSort import GBSort

class GBInsertionSort(GBSort):
    def sort(self, arr):
        n = len(arr)
        for i in range(1, n):
            j = i
            # 현재 위치의 원소가 왼쪽 원소보다 작으면 swap
            while j > 0 and arr[j-1] > arr[j]:
                self.swap(arr, j, j-1)
                j -= 1
        return arr
