from GBSort import GBSort

class GBInsertionSortForPython(GBSort):
    def sort(self, arr):
        n = len(arr)
        for i in range(1, n):
            key = arr[i]
            j = i - 1
            # arr[j] > key 인 동안 j를 뒤로 당기며 시프트
            while j >= 0 and arr[j] > key:
                arr[j + 1] = arr[j]
                j -= 1
            arr[j + 1] = key
        return arr
