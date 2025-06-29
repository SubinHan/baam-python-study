import random
import time

from GBStopwatch import GBStopwatch

def generate_random_integers(n, lower=-10, upper=10):
    """
    Generates a list of n random integers between lower and upper (inclusive).
    """
    return [random.randint(lower, upper) for _ in range(n)]

def count_three_sum_zero(nums):
    """
    Counts the number of unique triplets (i < j < k) in nums that sum to zero using a brute-force approach.
    """
    count = 0
    n = len(nums)
    for i in range(n-2):
        for j in range(i+1, n-1):
            for k in range(j+1, n):
                if nums[i] + nums[j] + nums[k] == 0:
                    count += 1
    return count

if __name__ == "__main__":
    random.seed(time.perf_counter())  # Seed for reproducibility
    n = 500  # Number of random integers to generate
    nums = generate_random_integers(n, -1000, 1000)
    # print("Generated numbers:", nums)
    timer = GBStopwatch()
    result = count_three_sum_zero(nums)
    print(f"Elapsed time: {timer.elapsed_time()}s")
    print(f"Number of triplets summing to zero: {result}")
