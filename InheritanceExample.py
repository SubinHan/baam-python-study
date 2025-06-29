# 상속 문법
# class [ClassName]([상속받을 ClassName]):

# 상속을 받으면,
# 부모의 모든 함수, 모든 속성들을 가져온다.

# Overriding
# 부모의 함수를 덮어쓸 수도 있다. (같은 이름과 같은 인자 형태로 선언하면 됨)


class Person:
    def __init__(self, name: str, age: int):
        print('Person 생성자 호출')
        self.name = name
        self.age = age

    def greet(self) -> None:
        """기본 인사 메서드 (자식이 오버라이딩 가능)"""
        print(f"안녕하세요, 저는 {self.name}이고, 나이는 {self.age}세입니다.")

    def info(self) -> None:
        """공통 정보 출력 메서드 (자식이 오버라이딩하지 않음)"""
        print(f"[정보] 이름: {self.name} / 나이: {self.age}")

# 상속을 할 때는
# "IS-A 관계"일 때 상속을 한다.
# Student is a Person.
class Student(Person):
    def __init__(self, name: str, age: int, student_id: str):
        print('Student 생성자 호출')
        # 부모 생성자를 호출하여 name, age 초기화
        super().__init__(name, age)
        self.student_id = student_id

    def greet(self) -> None:
        """학생 전용 인사말로 오버라이딩"""
        print(f"안녕하세요, 저는 학생 {self.name}이고, 학번은 {self.student_id}입니다.")


class Employee(Person):
    def __init__(self, name: str, age: int, employee_id: str, department: str):
        # 부모 생성자 호출
        super().__init__(name, age)
        self.employee_id = employee_id
        self.department = department

    def greet(self) -> None:
        """직원 전용 인사말로 오버라이딩"""
        print(f"안녕하세요, 저는 직원 {self.name}이고, 사번은 {self.employee_id}입니다.")

    def work(self) -> None:
        """직원만 가지는 고유 메서드"""
        print(f"{self.name}님이 {self.department} 부서에서 업무를 수행 중입니다.")


def main():
    # 1) Person 타입의 객체를 담을 리스트 생성
    # Colon 뒤에 type을 명시 가능(optional)
    people: list[Person] = []

    # 2) Student와 Employee 인스턴스 생성
    person = Person("홍길동", 30)
    student = Student("박영희", 20, "S2025001")
    employee = Employee("이철수", 40, "E2025001", "기획팀")

    # 3) 두 인스턴스를 Person 타입 리스트에 추가
    people.append(person)
    people.append(student)
    people.append(employee)
    # Student, Employee 모두 Person을 상속받으므로 List[Person]에 담아도 문제없다. 

    # 4) for문으로 리스트 순회하며 공통 메서드 호출
    for p in people:
        # greet(): 실제 실행할 메서드는 student.greet() 혹은 employee.greet()
        p.greet()   # 다형성(polymorphism) 발생: 적절한 오버라이딩된 구현이 호출된다.
        # info(): 부모 클래스 Person의 구현을 그대로 사용
        p.info()    # 공통 메서드로, Student, Employee 모두 동일 동작을 수행한다.
        print("――――――――――――――――――")
    # 이 루프를 돌면 아래와 같은 순서로 출력됨:
    # 1) 학생 인사 -> 학생 info
    # 2) 구분선
    # 3) 직원 인사 -> 직원 info
    # 4) 구분선

    # 5) for문 이후, Employee 전용 메서드 호출
    # 리스트 요소는 Person으로 참조했으므로, 직접 person.work() 호출은 불가.
    # 따라서 명시적으로 Employee 타입으로 접근해야 한다.
    print("== 직원 전용 메서드 실행 ==")
    employee.work()

if __name__ == "__main__":
    main()


# 상속(inheritance)
# 부모의 모든 것을 가져오는 것
# 객체지향 프로그래밍을 하다보면, 비슷한 객체들끼리 모아놔야 할 필요가 있다.
# "운송수단" => 자동차, 자전거, 기차, 비행기
# 각각의 운송수단들은, 공통의 무언가를 공유할 가능성이 높다.
# 근데 이러한 "공통의 무언가"를 계속해서 반복적으로 구현을 하면, 불편함이 많다.
# 그래서, "공통의 무언가"를 묶은, 부모를 선언하고,
# 자동차, 자전거, 기차, 비행기 등등이 자식으로서 "공통의 무언가"를 상속받는다.