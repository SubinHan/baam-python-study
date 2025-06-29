from GBMergeSort import GBMergeSort
from GBArray import GBArray

class GBMergeSortBU(GBMergeSort):
    """
    Bottom-Up (상향식) 병합 정렬 구현 클래스.
    재귀를 사용하지 않고 반복문으로 정렬을 수행합니다.
    """

    def sort(self, arr):
        """
        배열을 Bottom-Up 병합 정렬을 사용하여 오름차순으로 정렬합니다.
        Java 코드의 public static void sort(Comparable[] a) 로직에 해당합니다.

        Args:
            arr (list): 정렬할 리스트.

        Returns:
            list: 정렬된 리스트.
        """
        n = len(arr)
        # 보조 배열 공간을 한 번만 할당합니다.
        self.aux = GBArray(n)

        # sz는 병합할 하위 배열의 크기를 의미합니다. 1, 2, 4, 8, ... 순으로 증가합니다.
        sz = 1
        while sz < n:
            # lo는 병합할 두 하위 배열 중 첫 번째 배열의 시작 인덱스입니다.
            lo = 0
            while lo < n - sz:
                # mid: 첫 번째 하위 배열의 끝 인덱스
                mid = lo + sz - 1
                # hi: 두 번째 하위 배열의 끝 인덱스
                # 마지막 하위 배열이 배열의 전체 크기를 넘어가지 않도록 min()을 사용합니다.
                hi = min(lo + sz + sz - 1, n - 1)
                
                self._merge(arr, lo, mid, hi)
                
                # 다음 병합할 위치로 건너뜁니다 (두 개 하위 배열의 크기만큼 이동).
                lo += sz + sz
            
            # 하위 배열의 크기를 두 배로 늘립니다.
            sz += sz

        return arr