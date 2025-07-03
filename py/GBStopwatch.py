import time

class GBStopwatch:
    def __init__(self):
        # 생성 시점의 고해상도 타이머 값을 저장
        self._start = time.perf_counter()

    def elapsed_time(self) -> float:
        """
        생성 시점으로부터 경과한 시간을 초 단위(float)로 반환.
        """
        return time.perf_counter() - self._start

    def reset(self):
        """
        스톱워치를 다시 시작(생성 시점 재설정).
        """
        self._start = time.perf_counter()