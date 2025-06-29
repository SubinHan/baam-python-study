import time

class PerformanceChecker:
    def __init__(self):
        self.start_time = time.time_ns()
    
    def elapsed_time_ns(self):
        return time.time_ns() - self.start_time
    
    def elapsed_time_ms(self):
        return self.elapsed_time_ns() / 1000000
    
    def elapsed_time_s(self):
        return self.elapsed_time_ns() / 1000000000