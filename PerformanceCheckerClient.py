from PerformanceChecker import PerformanceChecker

pc = PerformanceChecker()
for i in range(10000):
    print("dosomething")
print(pc.elapsed_time_ms(), "milliseconds")