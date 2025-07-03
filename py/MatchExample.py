# Python 3.10 이상만 가능

menu = int(input('메뉴를 1, 2, 3 중 하나를 골라 입력해주세요> '))
 
match menu:
    case 1:
        print('커피')
    case 2:
        print('에이드')
    case 3:
        print('우유')
    case _:
        print('1 ~ 3까지만 입력 가능!')

print('=====================')