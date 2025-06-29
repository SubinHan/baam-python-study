import random
from GBArray import GBArray

class GBQuickSelect:
    """
    Quick Select 알고리즘 구현 클래스.
    배열에서 k번째로 작은 원소를 O(n)의 평균 시간 복잡도로 찾습니다.
    Quick Sort와 달리 한 쪽 파티션에 대해서만 재귀적으로 처리하여 속도를 높입니다.
    """

    def _swap(self, arr: GBArray, i: int, j: int):
        """
        배열의 두 원소를 교환하는 내부 헬퍼 메서드.
        """
        arr[i], arr[j] = arr[j], arr[i]

    def _partition(self, arr: GBArray, lo: int, hi: int) -> int:
        """
        arr[lo..hi]를 분할하고, 피벗의 최종 위치를 반환합니다.
        GBQuickSort의 파티션 구현을 그대로 사용합니다.
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
            self._swap(arr, i, j)

        # 피벗(arr[lo])을 최종 위치(j)로 이동시킵니다.
        self._swap(arr, lo, j)
        
        # 피벗의 최종 위치를 반환합니다.
        return j

    def select(self, arr: GBArray, k: int):
        """
        arr에서 k번째로 작은 원소를 찾아 반환합니다. (k는 0-based 인덱스)

        Args:
            arr (GBArray): 원소를 찾을 대상 배열. 배열의 내용은 변경될 수 있습니다.
            k (int): 찾고자 하는 원소의 순위 (0 <= k < len(arr)).

        Returns:
            Any: k번째로 작은 원소.
        
        Raises:
            ValueError: k가 유효한 범위를 벗어난 경우.
        """
        if not (0 <= k < len(arr)):
            raise ValueError(f"k must be between 0 and {len(arr) - 1}, but got {k}")

        # 최악의 경우를 피하고 평균 O(n) 성능을 보장하기 위해 배열을 섞습니다.
        temp_list = [arr[i] for i in range(len(arr))]
        random.shuffle(temp_list)
        for i, val in enumerate(temp_list):
            arr[i] = val

        lo, hi = 0, len(arr) - 1
        while hi > lo:
            # 배열을 분할하고 피벗의 위치 j를 얻습니다.
            j = self._partition(arr, lo, hi)
            
            if j < k:
                # 피벗이 k보다 왼쪽에 있으면, 오른쪽 부분배열에서 계속 찾습니다.
                lo = j + 1
            elif j > k:
                # 피벗이 k보다 오른쪽에 있으면, 왼쪽 부분배열에서 계속 찾습니다.
                hi = j - 1
            else:
                # 피벗의 위치가 k와 같으면, 원소를 찾았으므로 반환합니다.
                return arr[k]
        
        # 루프가 끝나면 lo == hi == k 이므로, arr[k]가 정답입니다.
        return arr[k]


# --- 테스트 코드 ---
if __name__ == "__main__":
    data = [29, 10, 14, 37, 13, 1, 99, 5, 42, 15, 63, 8, 22, 49, 11]
    
    gb_array = GBArray(len(data))
    for i, val in enumerate(data):
        gb_array[i] = val
        
    print(f"Original GBArray: {gb_array}")

    selector = GBQuickSelect()

    # Python의 내장 정렬을 이용해 결과를 검증합니다.
    sorted_data = sorted(data)
    print(f"Sorted reference: {sorted_data}\n")
    
    try:
        # k=0: 최솟값 찾기
        k_val_0 = selector.select(gb_array, 0)
        print(f"The 0-th smallest element is {k_val_0} (should be {sorted_data[0]})")
        assert k_val_0 == sorted_data[0]

        # k=len-1: 최댓값 찾기
        k_val_last = selector.select(gb_array, len(data) - 1)
        print(f"The {len(data)-1}-th smallest element is {k_val_last} (should be {sorted_data[-1]})")
        assert k_val_last == sorted_data[-1]

        # k=median: 중앙값 찾기
        median_k = len(data) // 2
        median_val = selector.select(gb_array, median_k)
        print(f"The {median_k}-th smallest element (median) is {median_val} (should be {sorted_data[median_k]})")
        assert median_val == sorted_data[median_k]

        print("\nAll tests passed!")

    except (ValueError, AssertionError) as e:
        print(f"\nTest failed: {e}")