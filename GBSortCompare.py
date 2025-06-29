from GBSort import GBSort
from GBStopwatch import GBStopwatch
from GBArray import GBArray
import random

class GBSortCompare:
    def time(sorter, data):
        stopwatch = GBStopwatch()
        sorter.sort(data)
        return stopwatch.elapsed_time()

    """
    길이 N인 T개의 무작위 배열을 정렬 후 소모된 시간을 반환
    """
    def time_random_input(sorter, n, trial):
        total = 0.0
        data = GBArray(n)
        for t in range(trial):
            # 1회 실험 수행(배열을 생성하고 정렬)
            for i in range(n):
                data[i] = random.uniform(-100.0, 100.0)
            total += GBSortCompare.time(sorter, data)
        
        return total

    def compare(sorter0, sorter1, n, trial):
        t0 = GBSortCompare.time_random_input(sorter0, n, trial)
        t1 = GBSortCompare.time_random_input(sorter1, n, trial)
        print(f"For {n} random Doubles \n {sorter0.__class__.__name__} is", end='')
        print(f" {t1/t0:.2f} times faster than {sorter1.__class__.__name__}\n")