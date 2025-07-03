from Counter import Counter
# import Counter도 가능. 대신 이 경우
# counter_inst = Conuter.Counter("counter0", 10) 꼴이 되어야 함.

counter_inst = Counter("counter0", 10)
for i in range (50):
    counter_inst.increment()

print(counter_inst.value())
print(counter_inst.to_string())