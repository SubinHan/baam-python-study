from GBSort import GBSort

class GBSelectionSort(GBSort):

    def sort(self, arr):
        n = len(arr)

        for i in range(n - 1):
            # i번째 위치에 들어갈 최솟값의 인덱스 찾기
            min_idx = i
            for j in range(i + 1, n):
                if arr[j] < arr[min_idx]:
                    min_idx = j
            # i와 min_idx 자리를 교환
            self.swap(arr, i, min_idx)