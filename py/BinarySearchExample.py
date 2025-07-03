import random
from GBStopwatch import GBStopwatch

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

def rank_seq(key: int, a: list) -> int:
    for index, elem in enumerate(a):
        if key == elem:
            return index
    return -1

if __name__ == "__main__":
    # 1) Generate 100 random integers between 0 and 200
    random.seed(42)
    nums = [random.randint(0, 200) for _ in range(100)]
    
    # 2) Sort the list
    nums.sort()
    
    # Display the sorted list
    print("Sorted list of 100 random integers:")
    print(nums)
    
    # 3) Demonstrate rank() usage
    test_keys = [nums[0], nums[50], nums[-1], 201]  # first, middle, last, and a non-existent key
    print("\nBinary search results:")
    for key in test_keys:
        result = rank(key, nums)
        print(f"Searching for {key}: {'Found' if result != -1 else 'Not found'} (returns {result})")

    # 4) Comparison
    nums = [random.randint(0, 200000) for _ in range(100000)]
    nums.sort()
    
    test_keys = [nums[0], nums[50000], nums[-1], 200001]  # first, middle, last, and a non-existent key
    print("\nBinary search results:")
    binary_stopwatch = GBStopwatch()
    for key in test_keys:
        result = rank(key, nums)
        print(f"Searching for {key}: {'Found' if result != -1 else 'Not found'} (returns {result})")
    print('binary serach took:', binary_stopwatch.elapsed_time())
    
    sequential_stopwatch = GBStopwatch()
    for key in test_keys:
        result = rank_seq(key, nums)
        print(f"Searching for {key}: {'Found' if result != -1 else 'Not found'} (returns {result})")
    print('sequential serach took:', sequential_stopwatch.elapsed_time())
