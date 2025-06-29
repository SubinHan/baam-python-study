# def add(x, y):
#   return x + y

# def square(x):
#   return x * x

# def anonymous(x):
#   return x * 2

# lambda:
# 익명 함수(anonymous function)
# 객체 그 자체가 함수 역할.

# lambda [parameter]: [return]

print((lambda x, y: x + y)(2, 3))

square = lambda x: x * x
my_list = [1, 2, 3, 4, 5]
mapped_list = list(map(square, my_list))
print(mapped_list)
mapped_list = list(map(lambda x: x * 2, my_list))
print(mapped_list)

just_map = map(lambda x: x * 2, my_list)
print(just_map)
for elem in just_map:
    print(elem)
