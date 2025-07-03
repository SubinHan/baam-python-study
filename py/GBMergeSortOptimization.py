from GBSort import GBSort
from GBArray import GBArray

class GBMergeSort(GBSort):
    """
    병합 정렬(Merge Sort)의 최적화된 구현.
    - 재귀 레벨마다 배열 역할을 교환하여 복사 비용 제거
    - 작은 배열에 대해서는 삽입 정렬(Cutoff)을 사용하여 성능 향상
    """
    
    # 삽입 정렬로 전환할 배열 크기의 임계값
    INSERTION_SORT_CUTOFF = 7

    def sort(self, arr: GBArray) -> GBArray:
        """
        배열을 병합 정렬을 사용하여 오름차순으로 정렬합니다.
        최초에 한 번만 데이터를 보조 배열로 복사합니다.

        Args:
            arr (GBArray): 정렬할 GBArray 객체.

        Returns:
            GBArray: 정렬된 GBArray 객체.
        """
        n = len(arr)
        # 보조 배열을 만들고, 원본 배열의 내용을 한 번만 복사합니다.
        aux = GBArray(n)
        for i in range(n):
            aux[i] = arr[i]
        
        # aux를 원본(src)으로 하여 arr을 목적지(dst)로 정렬을 시작합니다.
        self._sort(src=aux, dst=arr, lo=0, hi=n - 1)
        return arr

    def _insertion_sort(self, arr: GBArray, lo: int, hi: int):
        """
        arr[lo..hi] 범위를 삽입 정렬로 정렬합니다.
        """
        for i in range(lo + 1, hi + 1):
            key = arr[i]
            j = i - 1
            while j >= lo and arr[j] > key:
                arr[j + 1] = arr[j]
                j -= 1
            arr[j + 1] = key

    def _sort(self, src: GBArray, dst: GBArray, lo: int, hi: int):
        """
        src 배열의 [lo..hi] 범위를 정렬하여 dst 배열의 [lo..hi]에 저장합니다.
        재귀 호출 시마다 src와 dst의 역할을 바꿉니다.
        """
        # --- 개선점 2: Cutoff 적용 ---
        # 배열의 크기가 임계값보다 작으면 더 빠른 삽입 정렬을 사용합니다.
        if hi <= lo + self.INSERTION_SORT_CUTOFF - 1:
            self._insertion_sort(dst, lo, hi)
            return

        mid = lo + (hi - lo) // 2
        
        # 재귀 호출: src와 dst의 역할을 서로 바꿔서 전달합니다.
        # 즉, 하위 레벨에서는 dst를 src로 삼아 정렬 결과를 src에 저장합니다.
        self._sort(src=dst, dst=src, lo=lo, hi=mid)
        self._sort(src=dst, dst=src, lo=mid + 1, hi=hi)
        
        # --- 추가 최적화: 이미 정렬된 경우 병합 생략 ---
        # 왼쪽 절반의 마지막 원소가 오른쪽 절반의 첫 원소보다 작거나 같으면
        # 이미 전체가 정렬된 상태이므로 병합(merge) 과정을 건너뛸 수 있습니다.
        # 이 경우, src의 내용을 dst로 복사하기만 하면 됩니다.
        if src[mid] <= src[mid + 1]:
            dst[lo:hi+1] = src[lo:hi+1]
            return

        # 병합 단계: src에서 데이터를 읽어와 정렬 후 dst에 씁니다.
        self._merge(src, dst, lo, mid, hi)

    def _merge(self, src: GBArray, dst: GBArray, lo: int, mid: int, hi: int):
        """
        src[lo..mid]와 src[mid+1..hi]를 병합하여 dst[lo..hi]에 저장합니다.
        --- 개선점 1: 이 함수에서는 더 이상 배열 복사가 없습니다. ---
        """
        i = lo
        j = mid + 1

        for k in range(lo, hi + 1):
            if i > mid:  # 왼쪽 절반을 모두 소진한 경우
                dst[k] = src[j]
                j += 1
            elif j > hi:  # 오른쪽 절반을 모두 소진한 경우
                dst[k] = src[i]
                i += 1
            elif src[j] < src[i]:  # 오른쪽 원소가 왼쪽 원소보다 작은 경우
                dst[k] = src[j]
                j += 1
            else:  # 왼쪽 원소가 오른쪽 원소보다 작거나 같은 경우
                dst[k] = src[i]
                i += 1

# --- 테스트 코드 ---
if __name__ == "__main__":
    # 테스트할 데이터
    data = [29, 10, 14, 37, 13, 1, 99, 5, 42, 15, 63, 8, 22, 49, 11]
    
    # GBArray 객체 생성
    gb_array = GBArray(len(data))
    for i, val in enumerate(data):
        gb_array[i] = val
        
    print("Original GBArray:", gb_array)
    
    # 정렬기 생성 및 정렬 수행
    sorter = GBMergeSort()
    sorted_array = sorter.sort(gb_array)
    
    print("Sorted GBArray:  ", sorted_array)

    # 정렬 결과 확인
    is_sorted_correctly = all(sorted_array[i] <= sorted_array[i+1] for i in range(len(sorted_array)-1))
    print("Is sorted correctly?", is_sorted_correctly)