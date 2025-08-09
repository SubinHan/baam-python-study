

# Visual Studio Community 설치 (초소형 C++ 환경)

#### 📥 1단계: Visual Studio 설치 파일 다운로드

1. 먼저, 아래 링크에 접속해서 **Visual Studio 2022 Community** 버전을 다운로드하세요. Community 버전은 학생, 개인 개발자에게 무료로 제공되는 버전입니다.
2. 다운로드된 `vs_community.exe` 파일을 실행하면, 필요한 파일을 먼저 다운로드한 후 설치 화면이 나타납니다.
    

#### ⚙️ 2단계: C++ 개발 최소 기능 선택 (가장 중요!)

설치 화면에서 **'워크로드(Workloads)'**를 선택하는 부분이 가장 중요해요. 여기서 C++ 개발에 필요한 모든 기능을 담고 있는 **`C++를 사용한 데스크톱 개발`**을 선택할 거예요. 하지만 전부 설치하면 용량이 너무 커지니, 필요한 것만 쏙쏙 골라 담아봅시다.

1. '워크로드' 탭에서 **`C++를 사용한 데스크톱 개발`** 항목의 체크박스를 클릭하세요.
2. 화면 오른쪽에 **'설치 세부 정보(Installation details)'** 패널이 나타납니다. 여기서 아래 항목들만 **체크**하고, 나머지는 **모두 체크 해제**하세요. 이게 핵심입니다!
    **✅ 반드시 체크해야 할 항목:**
    - **MSVC v143 - VS 2022 C++ x64/x86 빌드 도구 (최신)**
        - C++ 코드를 컴퓨터가 이해하는 언어로 번역해주는 '컴파일러'입니다. 이게 없으면 C++ 프로그래밍을 할 수 없어요.
    - **Windows 11 SDK** 또는 **Windows 10 SDK** (최신 버전 하나)
        - `cout`, `cin` 같은 기본 입출력 기능을 포함한 Windows의 핵심 기능들을 사용할 수 있게 해주는 도구 모음입니다.
    - **C++ 핵심 기능**
        - Visual Studio가 C++ 코드를 잘 이해하고 도와줄 수 있게 하는 기본 기능입니다.
    - **C++용 테스트 어댑터**
        - 우리가 앞으로 사용할 '단위 테스트' 기능을 Visual Studio에서 실행하기 위해 꼭 필요한 연결고리입니다.
            
    
    **❌ 체크 해제할 항목 (예시):**
    - `IntelliCode` (AI 코드 추천 기능, 지금은 없어도 괜찮아요)
    - `C++/CLI 지원...`
    - `C++ MFC...`, `C++ ATL...` (오래된 GUI 라이브러리)
    - `C++ AddressSanitizer` 등 기타 모든 항목들...
    
    이렇게 선택하면 설치 용량이 **수십 GB에서 2~3GB 수준으로** 크게 줄어듭니다.
    
3. 모두 선택했다면, 오른쪽 아래의 **`설치`** 버튼을 누릅니다. 설치가 완료될 때까지 잠시 기다려 주세요.

---

# 7. 상속과 다형성

### 7.1. 상속 (Inheritance)

#### 기본 개념

상속은 객체 지향 프로그래밍의 핵심 기능 중 하나로, **기존 클래스(부모 클래스, Base Class)의 기능을 새로운 클래스(자식 클래스, Derived Class)가 물려받는 것**을 의미합니다.
- **IS-A 관계**: 상속은 "자식은 부모의 한 종류이다 (A Student **is a** Person)" 관계가 성립할 때 사용합니다.
- **코드 재사용**: 부모 클래스에 정의된 멤버 변수와 함수를 자식 클래스에서 다시 작성할 필요 없이 사용할 수 있어 코드의 재사용성이 높아집니다.
- **기능 확장**: 자식 클래스는 부모에게 물려받은 기능 외에 자신만의 새로운 기능을 추가할 수 있습니다.
#### C++ 구현 예제

Python의 `InheritanceExample.py`와 유사하게 `Person`을 부모 클래스로, `Student`와 `Employee`를 자식 클래스로 구현해 보겠습니다.

```c++
// Person.h
#pragma once
#include <iostream>

class Person {
public:
    // 생성자
    Person(const char* name, int age);

    // 소멸자
    ~Person();

    void greet();
    void info();

protected:
    // 자식 클래스에서는 접근 가능해야 하므로 protected로 선언
    const char* name;
    int age;
};

// Person.cpp
#include "Person.h"

Person::Person(const char* new_name, int new_age) {
    std::cout << "Person 생성자 호출" << std::endl;
    name = new_name;
    age = new_age;
}

Person::~Person() {
    std::cout << "Person 소멸자 호출" << std::endl;
}

void Person::greet() {
    std::cout << "안녕하세요, 저는 " << name << "이고, 나이는 " << age << "세입니다." << std::endl;
}

void Person::info() {
    std::cout << "[정보] 이름: " << name << " / 나이: " << age << std::endl;
}

// Student.h
#pragma once
#include "Person.h"

class Student : public Person {
public:
    Student(const char* name, int age, const char* student_id);
    ~Student();

    void greet();

private:
    const char* student_id;
};

// Student.cpp
#include "Student.h"

Student::Student(const char* name, int age, const char* student_id)
    : Person(name, age), student_id(student_id) 
{ // 부모 생성자 호출
    std::cout << "Student 생성자 호출" << std::endl;
}

Student::~Student() 
{
    std::cout << "Student 소멸자 호출" << std::endl;
}

void Student::greet() 
{
    std::cout << "안녕하세요, 저는 학생 " << name << "이고, 학번은 " << student_id << "입니다." << std::endl;
}
```

---

### 2. 가상 함수(virtual)와 오버라이딩(Overriding)

#### 다형성(Polymorphism)의 문제

**다형성**은 "여러 형태를 가질 수 있는 능력"으로, 객체 지향 프로그래밍에서는 **하나의 인터페이스(부모 클래스 포인터)를 통해 여러 종류의 실제 객체(자식 클래스 객체)를 다루는 것**을 의미합니다.

하지만 아래와 같이 코드를 작성하면 문제가 발생합니다.

```c++
// main.cpp
#include "Student.h"

int main() {
    Person* person1 = new Student("박영희", 20, "S2025001");

    // 기대: "안녕하세요, 저는 학생 박영희이고..."
    // 실제: "안녕하세요, 저는 박영희이고, 나이는 20세입니다."
    person1->greet(); // Person의 greet()가 호출됨

    delete person1;
    return 0;
}
```

`Person` 포인터로 `Student` 객체를 가리키고 `greet()` 함수를 호출했지만, `Student`의 `greet()`이 아닌 `Person`의 `greet()` 함수가 호출되었습니다. 이를 **정적 바인딩(Static Binding)** 이라고 합니다. 컴파일 시점에 포인터의 타입(`Person*`)을 보고 어떤 함수를 호출할지 결정하기 때문입니다.

#### virtual 키워드와 동적 바인딩

이 문제를 해결하고, 실제 객체의 함수가 호출되도록 하는 것이 `virtual` 키워드입니다.
- **virtual**: 부모 클래스에서 함수를 `virtual`로 선언하면, 해당 함수는 **동적 바인딩(Dynamic Binding)** 으로 처리됩니다.
- **동적 바인딩**: 컴파일 시점이 아닌, **프로그램 실행 시점(runtime)** 에 포인터가 가리키는 실제 객체의 타입을 확인하여 호출할 함수를 결정합니다.

#### 오버라이딩 예제

`Person` 클래스의 `greet` 함수와 소멸자에 `virtual` 키워드를 추가해 보겠습니다.
```c++
// Person.h
class Person {
public:
    Person(const char* name, int age);
    // 소멸자는 반드시 virtual로 선언해야 메모리 누수를 막을 수 있습니다.
    virtual ~Person();

    // greet 함수를 virtual로 선언
    virtual void greet();

    void info();

protected:
    const char* name;
    int age;
};

// Person.cpp
// ... 이전과 동일 ...
Person::~Person() { /* ... */ }
void Person::greet() { /* ... */ }

// Student.h
class Student : public Person {
public:
    // ... 이전과 동일 ...
    // C++11부터는 `override` 키워드를 붙여 오버라이딩을 명시하는 것이 좋습니다.
    void greet() override;
    // ...
};

// Student.cpp
void Student::greet() {
    // ... 이전과 동일 ...
}

// main.cpp
int main() {
    Person* people[2];
    people[0] = new Person("박영희", 20);
    people[1] = new Student("이철수", 24, "S2025001"); // Employee 클래스

    for (int i = 0; i < 2; ++i) {
        // virtual 덕분에 각 객체에 맞는 greet() 함수가 호출됩니다.
        people[i]->greet(); // 다형성(Polymorphism)
        people[i]->info();
        std::cout << "--------------------" << std::endl;
        delete people[i]; // virtual 소멸자 덕분에 자식 소멸자가 먼저 호출됩니다.
    }
    return 0;
}
```

이제 `main` 함수에서 `people[0]->greet()`을 호출하면 `Student`의 `greet()`이, `people[1]->greet()`을 호출하면 `Employee`의 `greet()`이 올바르게 호출됩니다. 이것이 바로 다형성입니다.

---

### 3. C++ 형변환(Casting)

C++에서는 C 스타일의 `(type)value` 캐스팅보다 명시적이고 안전한 4가지 캐스트 연산자를 제공합니다.

#### `static_cast`
- **컴파일 시점**에 타입 변환의 유효성을 검사하는, 비교적 안전한 캐스트입니다.
- **주요 용도**:
    - `void*`에서 다른 타입 포인터로 변환.
    - 숫자 타입 간의 변환 (e.g., `int` -> `float`).
    - **상속 관계에서 부모 -> 자식(Downcasting) 또는 자식 -> 부모(Upcasting)**. (단, Downcasting은 안전성을 보장하지 않음)

```c++
// Upcasting (안전)
Student* student = new Student("박영희", 20, "S2025001");
Person* person = static_cast<Person*>(student);

// Downcasting (위험할 수 있음)
// person이 실제로는 Student 객체를 가리키고 있음을 개발자가 확신할 때 사용
Student* student2 = static_cast<Student*>(person);
```

#### `dynamic_cast`
- **실행 시점**에 타입 변환의 유효성을 검사하며, 상속 관계에서의 안전한 Downcasting을 위해 사용됩니다.
- **`virtual` 함수가 하나 이상 포함된 다형성 클래스**에만 사용할 수 있습니다. (RTTI - Run-Time Type Information 정보 사용)
- **주요 용도**:
    - 부모 클래스 포인터가 실제로 특정 자식 클래스 객체를 가리키는지 확인할 때 사용합니다.
    - 변환에 실패하면 포인터의 경우 `nullptr`를, 참조의 경우 `std::bad_cast` 예외를 발생시킵니다.

```c++
Person* person = new Student("박영희", 20, "S2025001");

// 안전한 Downcasting
Student* student = dynamic_cast<Student*>(person);
if (student) { // 캐스팅 성공
    student->greet();
}

Employee* employee = dynamic_cast<Employee*>(person);
if (!employee) { // 캐스팅 실패
    std::cout << "이 사람은 Employee가 아닙니다." << std::endl;
}
```

#### `const_cast`
- 포인터나 참조의 **`const` 또는 `volatile` 한정자를 제거**할 때 사용합니다.
- `const`를 제거하고 값을 수정하는 행위는 매우 위험하며, 원래 객체가 `const`로 선언된 경우 **미정의 행동(Undefined Behavior)** 을 유발할 수 있습니다.

```c++
void print_name(const char* name) {
    // name은 const 포인터라 수정 불가
    // const를 제거하여 수정 가능하게 만듦 (주의해서 사용)
    char* modifiable_name = const_cast<char*>(name);
    modifiable_name[0] = '김'; // 위험한 작업
    std::cout << modifiable_name << std::endl;
}
```

#### `reinterpret_cast`
- **전혀 관련 없는 타입 간의 비트 수준 변환**을 수행하는, 가장 위험한 캐스트입니다.
- 포인터를 정수로, 정수를 포인터로 바꾸거나 전혀 다른 타입의 포인터로 변환하는 등 저수준(low-level) 작업에 사용됩니다.
- 이식성을 해치고 매우 위험하므로 반드시 필요한 경우가 아니면 사용하지 않아야 합니다.

```c++
int address_value = 0x12345;
// 정수 주소값을 실제 포인터로 변환
Person* person_ptr = reinterpret_cast<Person*>(address_value);

// 포인터를 정수로 변환
long address = reinterpret_cast<long>(person_ptr);
```

# 7. Template

- C++ 템플릿을 한마디로 정의하면, **"데이터 타입(Type)을 파라미터로 받는 기능"** 입니다.
- 이게 무슨 말일까요? 우리가 붕어빵을 만든다고 상상해봅시다.
	- **붕어빵 틀**은 모양(붕어)을 결정합니다.
	- **속 재료**는 팥, 슈크림, 고구마 등 다양하게 바꿀 수 있습니다.

여기서 **붕어빵 틀**이 바로 **템플릿**이고, **속 재료(팥, 슈크림)** 가 **데이터 타입(int, double, string...)** 입니다. 즉, 템플릿을 이용하면 **'기능의 골격(알고리즘)'은 한 번만 만들어두고, 그 안에서 사용될 데이터 타입은 필요에 따라 바꿔 끼울 수 있습니다.**

이처럼 데이터 타입에 의존하지 않고, 일반적인 형태로 코드를 작성하는 방식을 **제네릭 프로그래밍(Generic Programming)** 이라고 부르며, 템플릿은 C++에서 이를 가능하게 하는 핵심 도구입니다.

### 🤔 템플릿은 왜 필요한가요?

만약 두 숫자를 더하는 `add` 함수를 만든다고 가정해봅시다. `int`형 두 개를 더하는 함수와 `double`형 두 개를 더하는 함수는 어떻게 만들어야 할까요?

**템플릿이 없다면...**

```c++
int add_int(int a, int b) {
    return a + b;
}

double add_double(double a, double b) {
    return a + b;
}

// 사용할 때
int result1 = add_int(3, 5);       // 정수 덧셈
double result2 = add_double(3.5, 2.1); // 실수 덧셈
```

어떤가요? 함수의 이름만 다를 뿐, `a + b`를 반환하는 핵심 로직은 완전히 똑같습니다. 타입별로 똑같은 함수를 계속 만드는 것은 매우 비효율적이고, 유지보수도 어렵습니다.

**템플릿을 사용하면!**

이 문제를 템플릿으로 아주 우아하게 해결할 수 있습니다.
```c++
template <typename T>
T add(T a, T b) {
    return a + b;
}

// 사용할 때
int result1 = add(3, 5);           // 컴파일러가 T를 int로 추론해 add<int> 함수를 생성
double result2 = add(3.5, 2.1);     // 컴파일러가 T를 double로 추론해 add<double> 함수를 생성
```

`add_int`, `add_double`을 따로 만들 필요 없이 `add`라는 **'기능의 틀'** 하나만 만들면, 컴파일러가 사용된 타입을 보고 알아서 `T` 자리에 `int`나 `double`을 넣어 코드를 생성해줍니다. 훨씬 간결하고 효율적이죠!

---

## 🛠️ 템플릿 기본 문법

### 1. 함수 템플릿 (Function Templates)

함수 템플릿은 특정 기능(알고리즘)을 여러 다른 타입에 재사용하고 싶을 때 사용합니다.
```c++
template <typename T> // 또는 template <class T>
void swap_values(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// 사용 예시
int x = 10, y = 20;
swap_values(x, y); // T는 int로 결정됨

double d1 = 5.5, d2 = 10.1;
swap_values(d1, d2); // T는 double로 결정됨
```

- `template <typename T>` : "이제부터 템플릿을 사용할 것이고, 타입의 이름은 `T`라는 이름으로 대신 부르겠다"는 선언입니다. `T`는 'Type'의 약자로 관례적으로 많이 사용하며, 다른 이름을 써도 무방합니다. `typename` 대신 `class`를 써도 동일하게 동작합니다.
- `T& a, T& b`: `T`라는 미확정 타입을 매개변수로 받습니다.
- `T temp`: `T` 타입의 임시 변수를 선언합니다.
    
### 2. 클래스 템플릿 (Class Templates)

클래스 템플릿은 여러 다른 타입을 담을 수 있는 자료구조를 만들 때 사용됩니다.

```c++
template <typename T>
class Box {
private:
    T item;

public:
    void set_item(T value) {
        item = value;
    }

    T get_item() {
        return item;
    }
};

// 사용 예시
// 정수를 담는 Box
Box<int> int_box;
int_box.set_item(100);
int number = int_box.get_item(); // 100

// 문자열을 담는 Box
Box<std::string> string_box;
string_box.set_item("Hello World");
std::string message = string_box.get_item(); // "Hello World"
```

- 함수 템플릿과 달리, 클래스 템플릿은 사용할 때 `Box<int>` 처럼 타입을 명시적으로 지정해주어야 합니다.
- 이렇게 `int`를 담는 박스와 `std::string`을 담는 박스를 하나의 '틀'로 만들어낼 수 있습니다.

---

### ✨ 템플릿의 핵심 장점 요약
1. **코드 재사용성**: 똑같은 로직을 타입별로 중복해서 작성할 필요가 없습니다.
2. **타입 안전성**: 컴파일 시점에 타입 검사가 이루어져 안전합니다. `Box<int>`에 문자열을 넣으려고 하면 컴파일 에러가 발생합니다.
3. **성능**: 템플릿은 컴파일 시점에 실제 코드를 생성합니다. 실행 시간에 추가적인 비용이 없어 속도 저하가 없습니다. (런타임 다형성과 대조적)


----
