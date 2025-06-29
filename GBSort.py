from abc import *

class GBSort(metaclass=ABCMeta):
    def swap(self, arr, i, j):
        """
        두 인덱스 i, j 위치의 원소를 교환.
        """
        # 1) 전통적인 스타일 (임시 변수 이용)
        # temp = arr[i]
        # arr[i] = arr[j]
        # arr[j] = temp

        # 2) Pythonic 튜플 언패킹 방식
        arr[i], arr[j] = arr[j], arr[i]

    def is_sorted(self, arr):
        """
        리스트가 non-decreasing order(비감소 순)로 정렬되었는지 검사.
        """
        return all(arr[k] <= arr[k+1] for k in range(len(arr)-1))

    @abstractmethod
    def sort(self, arr):
        """
        Sort의 구현
        """
        pass