import random
from GBArray import GBArray
from GBSort import GBSort
from GBArray import GBArray

class GBQuickSort(GBSort):
    """
    퀵 정렬(Quick Sort) 구현 클래스.
    """

    def sort(self, arr: GBArray) -> GBArray:
        """
        배열을 퀵 정렬을 사용하여 오름차순으로 정렬합니다.

        Args:
            arr (GBArray): 정렬할 GBArray 객체.

        Returns:
            GBArray: 정렬된 GBArray 객체.
        """
        # 입력 의존성을 없애기 위해 배열을 무작위로 섞습니다.
        random.shuffle(arr)

        # 재귀 정렬을 시작합니다.
        self._sort(arr, 0, len(arr) - 1)
        return arr

    def _sort(self, arr: GBArray, lo: int, hi: int):
        """
        arr[lo..hi] 범위를 재귀적으로 정렬합니다.
        """
        # 베이스 케이스: 하위 배열에 원소가 1개 이하이면 더 이상 분할하지 않습니다.
        if hi <= lo:
            return

        # 분할(partition)을 수행하고 피벗의 최종 위치 j를 반환받습니다.
        j = self._partition(arr, lo, hi)
        
        # 피벗을 기준으로 나눠진 두 개의 하위 배열에 대해 재귀 호출을 수행합니다.
        self._sort(arr, lo, j - 1)  # 왼쪽 부분 정렬
        self._sort(arr, j + 1, hi)  # 오른쪽 부분 정렬

    def _partition(self, arr: GBArray, lo: int, hi: int) -> int:
        """
        arr[lo..hi]를 분할하고, 피벗의 최종 위치를 반환합니다.
        """
        i, j = lo, hi + 1
        pivot = arr[lo]  # 첫 번째 원소를 피벗으로 선택

        while True:
            # 왼쪽에서 오른쪽으로 스캔: 피벗보다 크거나 같은 원소를 찾습니다.
            i += 1
            while i <= hi and arr[i] < pivot:
                i += 1
            
            # 오른쪽에서 왼쪽으로 스캔: 피벗보다 작거나 같은 원소를 찾습니다.
            j -= 1
            while j >= lo and arr[j] > pivot:
                j -= 1

            # 포인터가 교차되면 루프를 탈출합니다.
            if i >= j:
                break
            
            # 찾은 두 원소의 위치를 교환합니다.
            self.swap(arr, i, j)

        # 피벗(arr[lo])을 최종 위치(j)로 이동시킵니다.
        self.swap(arr, lo, j)
        
        # 피벗의 최종 위치를 반환합니다.
        return j

# --- 테스트 코드 ---
if __name__ == "__main__":
    # 테스트할 데이터
    data = [29, 10, 14, 37, 13, 1, 99, 5]
    
    # GBArray 객체 생성
    gb_array = GBArray(len(data))
    for i, val in enumerate(data):
        gb_array[i] = val
        
    print("Original GBArray:", gb_array)
    
    # 정렬기 생성 및 정렬 수행
    sorter = GBQuickSort()
    sorted_array = sorter.sort(gb_array)
    
    print("Sorted GBArray:  ", sorted_array)

    # 정렬 결과 확인
    is_sorted_correctly = all(sorted_array[i] <= sorted_array[i+1] for i in range(len(sorted_array)-1))
    print("Is sorted correctly?", is_sorted_correctly)