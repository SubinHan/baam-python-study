import random

from GBStopwatch import GBStopwatch

def generate_random_integers(n, lower=-10, upper=10):
    return [random.randint(lower, upper) for _ in range(n)]

def generate_unique_random_integers(n: int, lower: int, upper: int) -> list:
    if upper - lower + 1 < n:
        raise ValueError("범위가 너무 작아서 고유한 정수를 생성할 수 없습니다.")
    
    arr = list(range(lower, upper + 1))
    length = len(arr)
    
    for i in range(n):
        j = random.randint(i, length - 1)
        arr[i], arr[j] = arr[j], arr[i]
    
    return arr[:n]

def count_two_sum_zero(nums):
    """
    Brute-force count of pairs summing to zero (O(n^2)).
    """
    count = 0
    n = len(nums)
    for i in range(n - 1):
        for j in range(i + 1, n):
            if nums[i] + nums[j] == 0:
                count += 1
    return count

def rank(key: int, a: list) -> int:
    lo, hi = 0, len(a) - 1
    while lo <= hi:
        mid = lo + (hi - lo) // 2
        if key < a[mid]:
            hi = mid - 1
        elif key > a[mid]:
            lo = mid + 1
        else:
            return mid
    return -1

def count_two_sum_zero_bs(nums):
    nums_sorted = sorted(nums)
    count = 0
    n = len(nums_sorted)
    for i in range(n - 1):
        if rank(-nums_sorted[i], nums_sorted) > i:
            count += 1
    return count

def count_two_sum_zero_bool(nums: list, lower: int, upper: int) -> int:
    # offset: value -> index 매핑
    offset = -lower
    size = upper - lower + 1

    # 1) 존재 여부를 저장할 boolean 리스트 초기화
    present = [False] * size
    for v in nums:
        present[v + offset] = True

    # 2) v > 0인 경우에만 -v 존재 여부 체크 (중복 카운트 방지)
    count = 0
    for v in nums:
        if v > 0 and present[-v + offset]:
            count += 1

    return count

if __name__ == "__main__":
    random.seed(42)
    n = 10000
    lower = -n
    upper = n
    nums = generate_unique_random_integers(n, lower, upper)

    # Measure brute-force version
    timer1 = GBStopwatch()
    result1 = count_two_sum_zero(nums)
    time1 = timer1.elapsed_time()

    # Measure binary-search version
    timer2 = GBStopwatch()
    result2 = count_two_sum_zero_bs(nums)
    time2 = timer2.elapsed_time()
    
    # Space-time trade off
    timer3 = GBStopwatch()
    result3 = count_two_sum_zero_bool(nums, lower, upper)
    time3 = timer3.elapsed_time()

    print(f"Brute-force 2-sum: {time1:.6f}s, pairs found: {result1}")
    print(f"Binary-search 2-sum: {time2:.6f}s, pairs found: {result2}")
    print(f"Space-time trade off 2-sum: {time3:.6f}s, pairs found: {result3}")
