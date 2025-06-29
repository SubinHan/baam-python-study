from GBSort import GBSort

class GBShellSort(GBSort):
    def sort(self, arr):
        n = len(arr)

        # Knuth 증가 시퀀스 생성: 1, 4, 13, 40, 121, ...
        h = 1
        while h < n // 3:
            h = 3 * h + 1

        # h가 1이 될 때까지 시퀀스를 역순으로 사용
        while h >= 1:
            # h-정렬
            for i in range(h, n):
                j = i
                while j >= h and arr[j] < arr[j - h]:
                    self.swap(arr, j, j - h)
                    j -= h
            h //= 3
