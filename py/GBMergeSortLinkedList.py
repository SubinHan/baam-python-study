from GBSort import GBSort
from GBNode import GBNode

class GBMergeSortLinkedList(GBSort):
    """
    연결 리스트를 위한 병합 정렬 구현 클래스.
    재귀적인 분할-정복 방식을 사용합니다.
    """

    def sort(self, head):
        """
        주어진 연결 리스트의 head를 받아 정렬된 리스트의 새로운 head를 반환합니다.
        
        Args:
            head (GBNode): 정렬할 연결 리스트의 첫 번째 노드.
            
        Returns:
            GBNode: 정렬된 연결 리스트의 새로운 첫 번째 노드.
        """
        # 기저 사례(Base case): 리스트가 비어있거나 노드가 하나뿐이면 이미 정렬된 상태입니다.
        if not head or not head.next:
            return head

        # 1. 분할(Divide): 리스트를 두 개의 하위 리스트로 나눕니다.
        left_head, right_head = self._split_list(head)

        # 2. 정복(Conquer): 각 하위 리스트를 재귀적으로 정렬합니다.
        sorted_left = self.sort(left_head)
        sorted_right = self.sort(right_head)

        # 3. 결합(Combine): 정렬된 두 하위 리스트를 병합합니다.
        return self._merge(sorted_left, sorted_right)

    def _split_list(self, head):
        """
        '느린/빠른 포인터'를 이용해 리스트의 중간을 찾아 두 개로 분할합니다.
        """
        # slow 포인터는 한 번에 한 칸, fast 포인터는 한 번에 두 칸 이동합니다.
        # fast가 리스트 끝에 도달하면 slow는 리스트의 중간에 위치하게 됩니다.
        slow = head
        fast = head.next
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
        
        # slow.next가 두 번째 하위 리스트의 시작점이 됩니다.
        mid = slow.next
        # 첫 번째 하위 리스트의 끝을 표시합니다 (연결을 끊음).
        slow.next = None
        
        return head, mid

    def _merge(self, left, right):
        """
        정렬된 두 개의 하위 리스트(left, right)를 하나의 정렬된 리스트로 병합합니다.
        """
        # 더미 노드를 사용하면 병합 로직을 간소화할 수 있습니다.
        dummy_head = GBNode(None)
        tail = dummy_head

        while left and right:
            if left.item <= right.item:
                tail.next = left
                left = left.next
            else:
                tail.next = right
                right = right.next
            tail = tail.next

        # 남은 노드들을 이어 붙입니다. left나 right 둘 중 하나는 None입니다.
        tail.next = left or right

        # 더미 노드 다음이 실제 병합된 리스트의 head가 됩니다.
        return dummy_head.next

# --- 테스트 코드 ---
def print_list(head, message=""):
    """연결 리스트를 보기 좋게 출력하는 헬퍼 함수"""
    if message:
        print(message, end="")
    current = head
    while current:
        end = " -> " if current.next else "\n"
        print(current.item, end=end)
        current = current.next
    if not head:
        print("List is empty.")