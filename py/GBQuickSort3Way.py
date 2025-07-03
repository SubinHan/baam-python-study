import random
from GBSort import GBSort
from GBArray import GBArray

class GBQuick3waySort(GBSort):
    """
    3-way 퀵 정렬(Dijkstra's 3-way partitioning) 구현 클래스.
    이 정렬은 중복된 키가 많은 배열에서 특히 뛰어난 성능을 보입니다.
    배열을 세 부분으로 나눕니다:
    1. 피벗(pivot)보다 작은 부분
    2. 피벗과 같은 부분
    3. 피벗보다 큰 부분
    이후, '작은 부분'과 '큰 부분'에 대해서만 재귀적으로 정렬을 수행합니다.
    """

    def sort(self, arr: GBArray) -> GBArray:
        """
        배열을 3-way 퀵 정렬을 사용하여 오름차순으로 정렬합니다.

        Args:
            arr (GBArray): 정렬할 GBArray 객체.

        Returns:
            GBArray: 정렬된 GBArray 객체.
        """
        # 최악의 경우(예: 이미 정렬된 배열)를 피하기 위해 배열을 무작위로 섞습니다.
        random.shuffle(arr)

        # 재귀 정렬을 시작합니다.
        self._sort(arr, 0, len(arr) - 1)
        return arr

    def _sort(self, arr: GBArray, lo: int, hi: int):
        """
        arr[lo..hi] 범위를 3-way 분할을 사용하여 재귀적으로 정렬합니다.
        """
        # 베이스 케이스: 하위 배열에 원소가 1개 이하이면 정렬할 필요가 없습니다.
        if hi <= lo:
            return

        # 포인터 초기화
        # lt: 피벗보다 작은 부분의 오른쪽 경계 + 1
        # gt: 피벗보다 큰 부분의 왼쪽 경계 - 1
        # i: 현재 검사 중인 원소의 인덱스
        lt, i, gt = lo, lo + 1, hi
        
        # 첫 번째 원소를 피벗으로 선택합니다.
        pivot = arr[lo]

        while i <= gt:
            if arr[i] < pivot:
                # 현재 원소(arr[i])가 피벗보다 작으면,
                # arr[lt]와 교환하고 lt와 i를 1씩 증가시킵니다.
                self.swap(arr, lt, i)
                lt += 1
                i += 1
            elif arr[i] > pivot:
                # 현재 원소(arr[i])가 피벗보다 크면,
                # arr[gt]와 교환하고 gt를 1 감소시킵니다.
                # i는 증가시키지 않습니다 (교환된 arr[i]를 다시 검사해야 하므로).
                self.swap(arr, i, gt)
                gt -= 1
            else:  # arr[i] == pivot
                # 현재 원소가 피벗과 같으면,
                # i만 1 증가시켜 다음 원소를 검사합니다.
                i += 1
        
        # 이제 a[lo..lt-1] < pivot = a[lt..gt] < a[gt+1..hi] 상태가 됩니다.
        # 피벗과 같은 부분(lt..gt)은 정렬할 필요가 없습니다.
        self._sort(arr, lo, lt - 1)  # 피벗보다 작은 부분 재귀 정렬
        self._sort(arr, gt + 1, hi)  # 피벗보다 큰 부분 재귀 정렬