import time

my_list = [0]*100000

t0 = time.time()
for i in range(len(my_list)):
    # 1) 뒤에서부터 제거하기
    del(my_list[len(my_list) - 1])
    # 2) 앞에서부터 제거하기
    # del(my_list[my_list[0]])
t1 = time.time()

print('삭제된 list의 크기는: ', len(my_list))
print(t1 - t0)

