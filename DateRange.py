class Date:
    DAYS_IN_MONTH = [31, 28, 31, 30, 31, 30,
                     31, 31, 30, 31, 30, 31]

    def __init__(self, year, month, day):
        self.year = year
        self.month = month
        self.day = day

    def __str__(self):
        return f"{self.year:04d}-{self.month:02d}-{self.day:02d}"

    def is_leap_year(self):
        y = self.year
        return (y % 4 == 0 and y % 100 != 0) or (y % 400 == 0)

    def days_in_month(self):
        if self.month == 2 and self.is_leap_year():
            return 29
        return self.DAYS_IN_MONTH[self.month - 1]

    def __lt__(self, other):
        return (self.year, self.month, self.day) < (other.year, other.month, other.day)

    def __le__(self, other):
        return (self.year, self.month, self.day) <= (other.year, other.month, other.day)

    def add_day(self):
        d = self.day + 1
        m = self.month
        y = self.year
        if d > self.days_in_month():
            d = 1
            m += 1
            if m > 12:
                m = 1
                y += 1
        return Date(y, m, d)


class DateIterator:
    def __init__(self, current, end):
        self.current = current
        self.end = end

    def __iter__(self):
        return self

    def __next__(self):
        if self.current > self.end:
            raise StopIteration
        today = self.current
        self.current = self.current.add_day()
        return today


class DateRange:
    def __init__(self, start, end):
        self.start = start
        self.end = end

    def __iter__(self):
        return DateIterator(self.start, self.end)
    
start = Date(2024, 2, 27)
end = Date(2024, 3, 2)

for d in DateRange(start, end):
    print(d)
# 2024-02-27
# 2024-02-28
# 2024-02-29
# 2024-03-01
# 2024-03-02