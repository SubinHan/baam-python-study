from GBSort import GBSort
from GBArray import GBArray

class GBMergeSort(GBSort):
    """
    병합 정렬(Merge Sort) 구현 클래스.
    """

    def __init__(self):
        """
        병합에 필요한 보조 배열(auxiliary array)을 초기화합니다.
        """
        self.aux = []

    def sort(self, arr):
        """
        배열을 병합 정렬을 사용하여 오름차순으로 정렬합니다.

        Args:
            arr (list): 정렬할 리스트.

        Returns:
            list: 정렬된 리스트.
        """
        n = len(arr)
        # 보조 배열 공간을 한 번만 할당합니다.
        self.aux = GBArray(n)
        self._sort(arr, 0, n - 1)
        return arr

    def _sort(self, arr, lo, hi):
        """
        arr[lo..hi]를 정렬하는 재귀 함수입니다.
        """
        # 기저 사례: 배열의 크기가 1 이하이면 이미 정렬된 상태입니다.
        if hi <= lo:
            return

        mid = lo + (hi - lo) // 2
        
        # 왼쪽 절반을 재귀적으로 정렬합니다.
        self._sort(arr, lo, mid)
        # 오른쪽 절반을 재귀적으로 정렬합니다.
        self._sort(arr, mid + 1, hi)
        # 두 절반을 병합합니다.
        self._merge(arr, lo, mid, hi)

    def _merge(self, arr, lo, mid, hi):
        """
        arr[lo..mid]와 arr[mid+1..hi]를 병합합니다.
        """
        i = lo
        j = mid + 1

        # arr[lo..hi]를 aux[lo..hi]로 복사합니다.
        # Python의 슬라이싱을 이용하면 더 간결하게 복사할 수 있습니다.
        # for k in range(lo, hi + 1):
        #     self.aux[k] = arr[k]
        self.aux[lo:hi+1] = arr[lo:hi+1]

        # 다시 arr[lo..hi]로 병합합니다.
        for k in range(lo, hi + 1):
            if i > mid:  # 왼쪽 절반을 모두 소진한 경우
                arr[k] = self.aux[j]
                j += 1
            elif j > hi:  # 오른쪽 절반을 모두 소진한 경우
                arr[k] = self.aux[i]
                i += 1
            elif self.aux[j] < self.aux[i]: # 오른쪽 원소가 왼쪽 원소보다 작은 경우
                arr[k] = self.aux[j]
                j += 1
            else:  # 왼쪽 원소가 오른쪽 원소보다 작거나 같은 경우
                arr[k] = self.aux[i]
                i += 1
