# raise
a = int(input("1~5 까지 숫자 입력 : "))

if a < 1 or a > 5:
    raise

print(f"입력한 a : {a} 입니다.")











############################
# raise + Exception Object


a = int(input("1~5 까지 숫자 입력 : "))

# 범위를 벗어나면 error 발생!
if a < 1 or a > 5:
    raise ValueError

# 범위 안에 있으면 정상 출력
print(f"입력한 a : {a} 입니다.")


#########################
# try - except

try:
    a = int(input("1~5 까지 숫자 입력 : "))

    # 범위를 벗어나면 error 발생!
    if a < 1 or a > 5:
        raise

    # 범위 안에 있으면 정상 출력
    print(f"입력한 a : {a} 입니다.")
except:
    print("1~5 사이 입력하라고 했잖아요.")


###########################
# try - except - else - finally

i = 0
while i < 5:
    print(i)
    i += 1

# while True:
#     try:  # 코드 작성
#         x = int(input("A를 입력 하세요: "))
#         y = int(input("A를 몇으로 나눌 지 입력해주세요: "))
#         print(x // y)
#     except ValueError:
#         print("숫자만을 입력할 수 있습니다. 다시 입력해주세요.")
#     except (ZeroDivisionError, OverflowError):
#         print("0으로 나누었거나, 값이 너무 큽니다. 다시 입력해주세요.")
#     except Exception as e:
#         print("알 수 없는 에러 발생", e)
#     else:
#         print("연산 끝")
#         break
#     finally:
#         print("에러 처리 끝")