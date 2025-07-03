
# 클래스, 객체

# 절차지향 프로그래밍 => C언어
# 절차 => procedure, sub-routine
# 요리를 한다. 1) 냉장고에서 음식을 꺼낸다. 2) 음식을 다진다. 3) 음식을 냄비에 넣는다. ...
# 결국에는 절차라는 것은 "함수"로서 표현되었음.
# 재귀적으로 있을 수 있음. 가령 냉장고에서 음식을 꺼낸다. 1) 손으로 냉장고 손잡이를 잡는다 2) ...

# 문제가 발생하기 시작.
# 규모가 커지니까 가령 이런 문제가 생기더라..
# "나는 팔을 움직이는 sub-routine을 가지고(기존에 있던), 또 다른 행위를 하고 싶다.
# 근데 어디까지가 팔을 움직이는 영역이야?"
# A를 하기 위해서는 사실 B와 C가 필요한 경우들이 있다.
# "의존"이 되어있다. 혹은 "결합"이 되어있다.

# 객체지향이 등장한다.
# 객체지향이 뭐냐면, 우리가 "절차"보다, 어떤 행위를 하는 "객체"라는 개념으로 바라보는 것은 어떨까?
# 클래스와 객체라는 개념이 도입.
# 클래스란, "속성"과 "연산"의 집합.
# 속성은 Attribute, Member Variable. 연산은 Method, Member Function 등으로 말함.
# 쉽게 말하면, 속성 => 값. 연산 => 함수

# 2차원 벡터를 의미하는 Vector2D라는 class를 만들었다.
# Vector2D의 속성은 => x, y
# Vector2D의 연산은 => 선형대수적으로 활용가능한 연산들 ex) add, subtract, dot, cross
# 위 속성과 연산은 "한 곳에" 정의되어야 하지 않을까?
# 즉, class는 "속성"과 "연산"의 집합을 의미하는 설계도.

# 객체라는 개념이 등장.
# 객체라는 것은 class의 instance.
# Vector2D class는 말그대로 "2차원 축 위의 점"이 "어떻게" 정의되는가를 기술함.
# 객체는, 이들의 "실현". 예를 들어, (1, 2) 점.name, 

# 이게 근데 왜 좋아요?
# 캡슐화(encapsulation), 정보은닉(information hiding)
# 캡슐화 => "속성"과 "연산"을 하나로 묶는다. 추상화된 캡슐에 이러한 것들을 담는다.
# 정보은닉 => 객체를 사용하는 사용자를 위해 정말 필요한 정보만을 바깥으로 노출하고, 
# 불필요한 것은 숨긴다.

# 이게 무슨의미인데?
# Vector2D => cartesian coordinate (x, y)로 생각을 했었는데
# 사실은, Polar coordinate (r, theta)일 수도 있다.
# 내부 구현이 어떻게 되느냐는 사용자가 관여할 바는 아니다.
# 그냥 사용자는 객체를 사용하기만 하면 된다.
# 사용자는, 그 구현이 바뀌어도 전혀 영향을 받지 않는다.
# dot(p1, p2) = 값은 동일

# API
# Application Programming Interface => 
#   특정한 "Application"(클래스, 프로그램)을 어떻게 사용할 수 있는지 정의한 것.
# API가 왜 중요한가요? => 객체가 어떻게 행위하는지 추상적으로 정의하고, 이건 변화시키지 말자.
# API != class, object

# 사례
# Python list.
# sort의 API는 변하지 않으나.
# sort를 구현하는 class는 변한다.
# 사용자는 API에 의존하니까, 사용자들의 코드가 변하지는 않는다.

# API는 "구현"과 관계없는 추상적 인터페이스
# Class는 (일반적으로) API의 "구현"
# Object는 Class의 "사례"
# 법적으로 "붕어빵은 어떠어떠하게 생겨야 한다." => API
# 그러한 법을 따라서 각 제조업체들이 붕어빵 틀을 만든다. => Class
# 붕어빵 틀을 이용해서 붕어빵을 실제로 찍어낸다. => Object

# 생성자는 생성할 때 호출되는 함수
# __init__이라는 이름을 가진다.

class Student:
    def __init__(self, new_number, new_name, new_grade):
        self.number = new_number
        self.name = new_name
        self.grade = new_grade
        print("인자가 있는 생성자 호출")

    def set_info(self, new_number, new_name, new_grade):
        self.number = new_number
        self.name = new_name
        self.grade = new_grade

    def print_info(self):
        print("--------------------")
        print("Number: ", self.number)
        print("Name: ", self.name)
        print("Grade: ", self.grade)
        print("--------------------")

s = Student("201710585", "한수빈", 4)
s.print_info()

s2 = Student("아무개학번", "아무개", 3)
s3 = Student("아무개학번", "아무개", 3)

print(s)