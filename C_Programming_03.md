#### 5.5. 동적 메모리 할당: 런타임에 메모리 크기 조절하기

- 우리가 지금까지 배운 배열은 선언할 때 크기가 고정되는 **정적 배열**입니다. 
- 하지만 때로는 프로그램이 실행되는 동안 필요한 메모리 크기가 결정되는 경우도 있습니다. 
- 예를 들어, 사용자에게 몇 개의 숫자를 입력받을지 물어보고 그 개수만큼의 배열을 만들어야 할 때가 그렇습니다.
- 이럴 때 사용하는 것이 **동적 메모리 할당(Dynamic Memory Allocation)**입니다.

![[Pasted image 20250703182820.png]]

- C 언어는 표준 라이브러리 함수를 통해 **힙(Heap)**이라는 메모리 영역에서 필요한 만큼의 메모리를 '빌려 쓰고', 다 쓴 후에는 '반납'할 수 있게 해줍니다.

- **`malloc()` (Memory Allocation):** 원하는 크기(바이트 단위)의 메모리 블록을 힙 영역에서 할당하고, 할당된 메모리의 시작 주소(포인터)를 반환합니다. 메모리 할당에 실패하면 `NULL`을 반환합니다.
    - `void* malloc(size_t size);`
    - 사용 예: `int *arr = (int*)malloc(sizeof(int) * 5);` // int 5개 크기 할당
        
- **`calloc()` (Contiguous Allocation):** `malloc`과 유사하지만, 할당된 메모리 영역을 **모두 0으로 초기화**해 준다는 차이가 있습니다.
    - `void* calloc(size_t num, size_t size);`
    - 사용 예: `int *arr = (int*)calloc(5, sizeof(int));` // int 5개 크기 할당 및 0으로 초기화

- **`realloc()` (Reallocation):** 이전에 `malloc`이나 `calloc`으로 할당된 메모리의 크기를 **재조정**합니다.
    - `void* realloc(void* ptr, size_t new_size);`

- **`free()` (Free Memory):** `malloc`, `calloc`, `realloc`으로 할당받은 메모리를 **반드시 운영체제에 반환**해야 합니다. 그렇지 않으면 해당 메모리가 계속 점유되어 프로그램이 느려지거나 충돌할 수 있는데, 이를 **메모리 누수(Memory Leak)**라고 합니다.
    
```c
#include <stdio.h>
#include <stdlib.h> // malloc, free 등을 사용하기 위해 포함

int main() {
    int *arr;
    int n;

    printf("몇 개의 정수를 저장하시겠습니까? ");
    scanf("%d", &n); // 사용자에게 개수 입력받기

    // n개의 정수를 저장할 공간을 동적으로 할당
    // (int*)는 void* 타입을 int* 타입으로 강제 형변환하는 것입니다.
    arr = (int*)malloc(sizeof(int) * n);

    // 메모리 할당 실패 확인
    if (arr == NULL) {
        printf("메모리 할당 실패!\n");
        return 1; // 오류 종료
    }

    // 할당된 메모리 사용 (배열처럼 사용)
    for (int i = 0; i < n; i++) {
        arr[i] = (i + 1) * 10;
        printf("arr[%d] = %d\n", i, arr[i]);
    }

    // 다 사용한 메모리는 반드시 해제
    free(arr);
    arr = NULL; // 해제된 메모리를 가리키지 않도록 NULL로 설정하는 것이 좋습니다.

    return 0;
}
```


**힙(Heap)과 스택(Stack) 메모리:**

- 메모리 누수를 방지하기 위해 C에서 메모리가 관리되는 방식을 이해하는 것이 중요합니다.
	- **스택(Stack):** 지역 변수, 함수 매개변수 등이 저장되는 영역입니다. 함수가 호출될 때 할당되고, 함수가 종료될 때 자동으로 해제됩니다. 크기가 제한적이고 속도가 빠릅니다.
	- **힙(Heap):** `malloc`, `calloc` 등으로 개발자가 직접 동적으로 할당하고 `free`로 해제해야 하는 영역입니다. 크기 제한이 스택보다 훨씬 덜하며, 프로그램 실행 중에 원하는 시점에 원하는 크기로 메모리를 할당할 수 있습니다.

- C 언어의 포인터는 처음에는 복잡하고 어렵게 느껴질 수 있지만, 메모리를 직접 다루는 강력한 능력을 제공합니다. 
- 이를 통해 여러분은 시스템의 동작 원리를 더 깊이 이해하고, 파이썬으로는 불가능했던 저수준 프로그래밍을 수행할 수 있게 될 것입니다. 
- 완벽히 이해하려면 많은 연습과 시간이 필요하지만, 그만큼 C 언어의 핵심에 다가서는 중요한 단계입니다.



---

### 6장: 구조체, 공용체, 열거형, 그리고 클래스 (사용자 정의 데이터 타입의 확장)

- 파이썬에서는 `class`를 이용해 여러분만의 복잡한 데이터 타입(객체)을 만들고, 그 안에 데이터(속성)와 함수(메서드)를 함께 묶어 관리했습니다. C 언어는 파이썬처럼 객체 지향의 모든 기능을 기본으로 제공하진 않지만, `struct`와 `union`을 통해 여러 데이터를 하나로 묶는 **사용자 정의 자료형**을 만들 수 있습니다. 그리고 C++에서는 여기서 한 단계 더 나아가 `class`라는 강력한 개념으로 완전한 객체 지향 프로그래밍을 지원합니다. 이 장에서는 C 언어의 데이터 묶음 방식과 C++의 객체 지향 개념을 함께 살펴보겠습니다.

---

#### 1. 구조체 (Struct): 여러 데이터 타입을 묶어 하나의 덩어리로

**구조체(Structure)**는 서로 다른 데이터 타입의 변수들을 하나로 묶어서 새로운 사용자 정의 데이터 타입을 만드는 C 언어의 핵심 기능입니다. 파이썬의 클래스에서 메서드(함수)를 제외하고, 오직 속성(데이터)만을 묶어 놓은 것이라고 생각하면 이해하기 쉽습니다.

예를 들어, 학생의 이름, 학번, 전공을 하나의 덩어리로 관리하고 싶을 때 구조체를 사용합니다.

C

```c
#include <stdio.h>
#include <string.h> // strcpy 함수 사용을 위해 포함

// Student라는 이름의 구조체 정의 (템플릿)
struct Student {
    char name[50];    // 이름 (문자열)
    int student_id;   // 학번 (정수)
    char major[30];   // 전공 (문자열)
    float gpa;        // 평점 (실수)
}; // 구조체 정의 끝에는 세미콜론(;)을 붙여야 합니다!

int main() {
    // Student 타입의 변수 's1' 선언
    struct Student s1;

    // 구조체 멤버(속성)에 접근하여 값 할당 ('.` 연산자 사용)
    strcpy(s1.name, "김철수"); // 문자열 복사는 strcpy 함수 사용
    s1.student_id = 20230001;
    strcpy(s1.major, "컴퓨터공학");
    s1.gpa = 3.85;

    // 구조체 멤버 값 출력
    printf("학생 이름: %s\n", s1.name);
    printf("학번: %d\n", s1.student_id);
    printf("전공: %s\n", s1.major);
    printf("평점: %.2f\n", s1.gpa);

    // 구조체 변수 선언과 동시에 초기화
    struct Student s2 = {"이영희", 20230002, "전자공학", 4.15};
    printf("\n두 번째 학생 이름: %s\n", s2.name);

    // 구조체 배열: 여러 학생 정보를 한 번에 관리
    struct Student class_members[3] = {
        {"박민준", 20230003, "경영학", 3.50},
        {"최유리", 20230004, "국어국문", 4.30},
        // 나머지 한 칸은 나중에 채울 수 있습니다.
    };

    printf("\n세 번째 학생 이름: %s\n", class_members[0].name);

    // 구조체 포인터: 구조체의 주소를 가리키는 포인터
    struct Student *ptr_s1 = &s1; // s1의 주소를 ptr_s1에 저장

    // 포인터를 통해 구조체 멤버 접근 ('->' 연산자 사용)
    printf("\n포인터를 통한 학생 이름: %s\n", ptr_s1->name);
    // (*ptr_s1).name 과 동일하지만 '->'가 더 간편합니다.

    return 0;
}
```

구조체는 데이터를 논리적으로 묶어 관리할 때 매우 유용하며, 복잡한 데이터 타입을 구성하는 데 필수적입니다.

---

#### 2. 공용체 (Union): 메모리를 공유하는 특별한 구조체

**공용체(Union)**는 구조체와 비슷하게 여러 데이터 타입을 묶을 수 있지만, 가장 큰 차이점은 **모든 멤버가 같은 메모리 공간을 공유한다**는 것입니다. 즉, 공용체의 크기는 그 멤버들 중 가장 큰 멤버의 크기로 결정되며, 한 번에 **오직 하나의 멤버만** 유효한 값을 가질 수 있습니다.

데이터의 종류는 여러 가지이지만, 특정 시점에는 그중 하나만 사용되는 경우에 메모리를 절약하기 위해 사용합니다. 예를 들어, 어떤 값이 정수일 수도, 실수일 수도 있는 경우에 유용합니다.

C

```c
#include <stdio.h>

// Data라는 이름의 공용체 정의
union Data {
    int i;
    float f;
    char str[20];
};

int main() {
    union Data data;

    data.i = 10; // i에 값을 할당하면 f와 str이 사용하는 메모리 공간이 덮어씌워집니다.
    printf("정수: %d\n", data.i); // 출력: 정수: 10

    data.f = 220.5; // f에 값을 할당하면 i와 str이 사용하는 메모리 공간이 덮어씌워집니다.
    printf("실수: %.1f\n", data.f); // 출력: 실수: 220.5

    // data.i와 data.f는 이미 덮어씌워져 유효하지 않은 값이 됩니다.
    // printf("정수 (잘못된 접근): %d\n", data.i); // 예측 불가능한 값 또는 오류

    strcpy(data.str, "C Programming"); // str에 값을 할당하면 i와 f가 덮어씌워집니다.
    printf("문자열: %s\n", data.str); // 출력: 문자열: C Programming

    // 공용체의 크기는 가장 큰 멤버의 크기인 str[20]의 크기 20바이트가 됩니다.
    printf("공용체 Data의 크기: %zu bytes\n", sizeof(union Data));

    return 0;
}
```

공용체는 메모리 최적화에 사용되지만, 어떤 멤버가 현재 유효한 값을 가지고 있는지 개발자가 명확히 관리해야 하므로 사용에 주의가 필요합니다.

---

#### 3. 열거형 (Enum): 상징적인 이름으로 정수 상수 정의하기

**열거형(Enumeration)**은 여러 개의 정수 상수에 의미 있는 이름을 부여하여 코드를 더 읽기 쉽고 오류 발생 가능성을 줄이는 데 사용됩니다. 파이썬의 `Enum` 클래스와 유사한 목적을 가집니다.

```c
#include <stdio.h>

// Weekday라는 이름의 열거형 정의
enum Weekday {
    MONDAY,    // 0으로 자동 할당
    TUESDAY,   // 1으로 자동 할당
    WEDNESDAY, // 2으로 자동 할당
    THURSDAY,  // 3으로 자동 할당
    FRIDAY,    // 4으로 자동 할당
    SATURDAY,  // 5으로 자동 할당
    SUNDAY     // 6으로 자동 할당
};

// 값을 명시적으로 지정할 수도 있습니다.
enum TrafficLight {
    RED = 10,
    YELLOW = 20,
    GREEN = 30
};

int main() {
    enum Weekday today = WEDNESDAY; // Weekday 타입의 변수 today 선언 및 초기화

    if (today == WEDNESDAY) {
        printf("오늘은 수요일입니다.\n");
    }

    printf("MONDAY의 값: %d\n", MONDAY);     // 출력: MONDAY의 값: 0
    printf("THURSDAY의 값: %d\n", THURSDAY); // 출력: THURSDAY의 값: 3

    enum TrafficLight current_light = YELLOW;
    printf("현재 신호등의 값: %d\n", current_light); // 출력: 현재 신호등의 값: 20

    return 0;
}
```

열거형은 코드를 작성할 때 숫자 대신 의미 있는 이름을 사용하게 하여 가독성과 유지보수성을 크게 향상시킵니다.

---

### 4. C++ 시작하기: C언어와의 첫 만남

C++는 C언어의 모든 문법을 포함하면서 객체 지향과 같은 강력한 기능들을 추가한 확장판 언어입니다. 따라서 여러분이 배운 모든 C언어 코드는 C++ 컴파일러에서도 대부분 유효합니다. 하지만 C++는 더 편리하고 안전한 프로그래밍을 위해 몇 가지 새로운 방식들을 도입했습니다. 4장에서 클래스를 본격적으로 배우기 앞서, C++의 기본적인 입출력과 새로운 기능들을 먼저 살펴보겠습니다.

#### 4.1 표준 입출력: `cout`과 `cin`

C언어의 `printf`와 `scanf`는 강력하지만, 데이터 타입에 맞는 서식 지정자(`%d`, `%f`, `%s` 등)를 정확히 사용해야 하는 번거로움이 있습니다. C++는 **스트림(Stream)** 이라는 개념을 사용해 이를 훨씬 직관적으로 만들었습니다.

- **헤더 파일:** C의 `<stdio.h>` 대신 C++의 `<iostream>`을 포함시킵니다.
    
- **출력 (`std::cout`):** "standard output"을 의미하며, `<<` (스트림 삽입 연산자)를 사용해 데이터를 출력 스트림에 흘려보냅니다.
    
- **입력 (`std::cin`):** "standard input"을 의미하며, `>>` (스트림 추출 연산자)를 사용해 입력 스트림에서 데이터를 가져옵니다.
    
- **줄바꿈 (`std::endl`):** "end line"을 의미하며, 줄을 바꾸고 출력 버퍼를 비우는 역할을 합니다. C의 `\n`과 유사하지만, 버퍼를 비운다는 추가 동작이 있습니다.
    


```c++
// C++ 스타일 입출력 예제
#include <iostream> // C++ 표준 입출력 헤더
#include <string>   // C++ 문자열 헤더

int main() {
    int age;
    std::string name; // C++에서는 더 편리한 string 타입을 사용합니다.

    // 1. 출력 (std::cout)
    std::cout << "이름을 입력하세요: ";
    // 2. 입력 (std::cin)
    std::cin >> name;

    std::cout << "나이를 입력하세요: ";
    std::cin >> age;

    // 여러 데이터를 연달아 출력할 수 있습니다.
    std::cout << name << "님의 나이는 " << age << "살입니다." << std::endl;

    return 0;
}
```

`cout`과 `cin`은 변수의 타입을 스스로 파악하기 때문에 서식 지정자가 필요 없어 코드가 간결해지고 타입 관련 실수를 줄여줍니다.

#### 4.2 네임스페이스 (Namespace)와 `std`

위 예제에서 `cout`, `cin`, `string` 앞에 계속 붙는 `std::`가 궁금하셨을 겁니다. `std`는 C++ **표준 라이브러리(Standard Library)**의 모든 기능이 속해있는 **네임스페이스(namespace)**의 이름입니다.

- **네임스페이스란?** 이름이 서로 충돌하는 것을 방지하기 위해 만들어진 공간입니다. 예를 들어, 내가 만든 `cout` 함수와 표준 라이브러리의 `cout` 객체의 이름이 겹치더라도, 각각 다른 네임스페이스에 속해있으면 문제없이 사용할 수 있습니다. `std::cout`은 "std 라는 이름 공간 안에 있는 cout"이라는 뜻입니다.
    
- **`using` 지시어:** 매번 `std::`를 붙이는 것이 번거롭다면, 코드 상단에 `using namespace std;`를 선언하여 `std::`를 생략할 수 있습니다.
    

```c++
#include <iostream>
#include <string>

// 이제 std 네임스페이스의 모든 것을 std:: 없이 사용하겠다고 선언
using namespace std;

int main() {
    string name;
    cout << "이름을 입력하세요: "; // std:: 생략 가능
    cin >> name;
    cout << name << "님, 환영합니다." << endl; // std:: 생략 가능
    return 0;
}
```

> **주의!** 간단한 학습용 코드에서는 `using namespace std;`가 편리하지만, 규모가 큰 프로젝트에서는 다른 라이브러리와 이름이 충돌할 가능성이 있어 `std::`를 명시적으로 붙이는 것이 권장됩니다.

#### 4.3 더 발전된 데이터 타입: `string`과 `bool`

C++는 C언어의 기본 타입에 더해 더 편리하고 명확한 타입을 제공합니다.

- **`std::string` 타입:** C언어에서는 문자열을 다루기 위해 `char` 배열을 사용하고, 문자열 끝을 알리는 `\0`(널 문자)를 항상 신경 써야 했습니다. C++의 `std::string`은 이러한 불편함을 해결한 클래스로, 문자열의 길이를 자동으로 관리하고 `+` 연산자로 쉽게 문자열을 합치는 등 다양한 기능을 제공합니다. 사용하려면 `<string>` 헤더를 포함해야 합니다.
    
- **`bool` 타입:** C언어에서는 `0`을 거짓으로, `0`이 아닌 값을 참으로 간주했습니다. C++는 **`bool`** 이라는 명확한 논리 타입을 도입했습니다. `bool` 타입은 **`true`**와 **`false`** 두 가지 값만 가질 수 있어 코드의 가독성과 안정성을 높여줍니다.
    

```c++
#include <iostream>
#include <string>

using namespace std;

int main() {
    string str1 = "Hello, ";
    string str2 = "World!";
    string result = str1 + str2; // '+' 연산자로 간단하게 문자열 합치기

    cout << "결과 문자열: " << result << endl;
    cout << "문자열 길이: " << result.length() << endl;

    bool is_cpp_fun = true; // bool 타입 변수 선언

    if (is_cpp_fun) { // if문에서 직접 사용
        cout << "C++ is fun!" << endl;
    }

    return 0;
}
```

이제 C++의 기본적인 도구들을 익혔으니, 다음 **4장**에서는 이 모든 것을 활용하여 객체 지향 프로그래밍의 핵심인 **클래스**를 어떻게 설계하고 사용하는지 본격적으로 알아보겠습니다.

#### 5. C++의 클래스 (Class): 객체 지향 프로그래밍의 핵심

C 언어는 절차 지향 언어의 특징이 강합니다. 하지만 C 언어를 기반으로 만들어진 **C++ 언어**는 C 언어의 모든 기능을 포함하면서도 **객체 지향 프로그래밍(Object-Oriented Programming, OOP)**을 완벽하게 지원하기 위해 **클래스(Class)** 개념을 도입했습니다.

파이썬 개발자라면 `class`는 이미 익숙하실 겁니다. C++의 `class`는 파이썬의 클래스와 매우 유사한 개념이며, `struct`가 데이터만 묶는 반면, `class`는 **데이터(멤버 변수)**와 그 데이터를 처리하는 **함수(멤버 함수, 또는 메서드)**를 함께 묶어 하나의 **캡슐화된 단위**로 만듭니다.

**C++ 클래스의 주요 특징:**

- **캡슐화 (Encapsulation):** 데이터와 데이터를 조작하는 함수를 하나의 단위(클래스)로 묶고, 외부로부터 내부 구현을 숨겨 정보 은닉을 가능하게 합니다.
    - `public`, `private`, `protected`와 같은 **접근 지정자(Access Specifier)**를 사용하여 멤버에 대한 접근 권한을 제어합니다.
        - `public`: 어디서든 접근 가능
        - `private`: 클래스 내부에서만 접근 가능 (일반적으로 멤버 변수를 private으로 선언하여 외부에서 직접 접근하는 것을 막습니다)
        - `protected`: 상속 관계에서만 접근 가능 (나중에 배웁니다)
- **상속 (Inheritance):** 기존 클래스(부모 클래스)의 특징을 새로운 클래스(자식 클래스)가 물려받아 재사용하고 확장할 수 있게 합니다.
- **다형성 (Polymorphism):** 같은 이름의 함수나 연산자가 상황에 따라 다르게 동작할 수 있게 하는 개념입니다.

**C++ 클래스 예시:**

```c++
#include <iostream> // C++의 표준 입출력 (printf 대신 cout 사용)
#include <string>   // C++의 문자열 (char 배열 대신 string 객체 사용)

// Person이라는 이름의 클래스 정의
class Person {
    std::string name; // 이름 (멤버 변수)
    int age;          // 나이 (멤버 변수)
    int 목상태; // 0이면 목이나감

public:
    // 생성자 (Constructor): 객체가 생성될 때 자동으로 호출되는 특별한 멤버 함수
    Person(std::string n, int a) {
        name = n;
        age = a;
        목상태 = 3;
        std::cout << "Person 객체 생성: " << name << std::endl;
    }

    // 멤버 함수 (Method): Person 객체의 데이터를 다루는 함수
    void introduce() {
		if (목상태 > 0)
		{
	        std::cout << "안녕하세요, 제 이름은 " << name << "이고, " << age << "살입니다." << std::endl;
		}
		decrease목상태();
    }

	void 소리치기() {

		decrease목상태();
	}

    // 소멸자 (Destructor): 객체가 소멸될 때 자동으로 호출되는 특별한 멤버 함수
    ~Person() {
        std::cout << "Person 객체 소멸: " << name << std::endl;
	}

private:
	void decrease목상태() {
		목상태--;
	}
}; // 클래스 정의 끝에도 세미콜론(;)을 붙여야 합니다!

int main() {
    // Person 클래스의 객체 'p1' 생성 (파이썬처럼 new 키워드 필요 없음)
    Person p1("김철수", 30);

    // 객체의 멤버 함수 호출 ('.` 연산자 사용)
    p1.introduce();

    // 동적으로 객체 생성 (힙 메모리) - 포인터와 new/delete 사용
    // 파이썬의 '객체 생성'과 가장 유사한 형태
    Person *p2 = new Person("이영희", 25);
    p2->introduce(); // 포인터로 멤버 접근 시 '->' 연산자 사용

    delete p2; // 동적으로 할당한 메모리는 반드시 delete로 해제해야 합니다.

    return 0;
}
```

**C++ 컴파일 및 실행 (Windows의 경우):**

```
g++ your_file_name.cpp -o your_program
./your_program
```

**C++ 클래스와 C 구조체의 차이 (간략 비교):**

| 특징         | C `struct`                         | C++ `class`                              |
| ---------- | ---------------------------------- | ---------------------------------------- |
| **목적**     | 단순히 여러 타입의 데이터를 묶는 데 사용            | 데이터와 함수를 묶어 객체를 정의하는 데 사용                |
| **멤버 접근**  | 기본적으로 모든 멤버가 `public` (외부에서 접근 가능) | 기본적으로 모든 멤버가 `private` (클래스 내부에서만 접근 가능) |
| **함수 포함**  | 멤버 함수(메서드)를 직접 포함할 수 없음            | 멤버 함수를 포함하여 데이터와 로직을 캡슐화                 |
| **상속/다형성** | 지원 안 함                             | 지원함 (객체 지향의 핵심)                          |


C 언어의 `struct`는 단순히 데이터만 묶는 기능이지만, C++의 `class`는 여기에 함수와 접근 제어, 상속, 다형성 같은 객체 지향 개념을 더하여 훨씬 강력한 데이터 추상화 및 재사용성을 제공합니다. 파이썬에서 객체 지향 프로그래밍에 익숙하시다면, C++의 클래스 개념은 훨씬 자연스럽게 다가올 것입니다.

### 5.1 클래스의 구성 요소: 생성자, 소멸자, 그리고 `this`

`Person` 클래스 예제를 통해 C++ 클래스를 구성하는 핵심 요소들을 자세히 살펴보겠습니다. 이들은 객체의 '생명 주기(Life Cycle)'를 관리하고, 객체 스스로를 참조하는 중요한 개념들입니다.

#### **생성자 (Constructor): 객체의 탄생을 책임지다**

생성자는 파이썬의 `__init__` 메서드와 정확히 같은 역할을 합니다. 즉, 클래스로부터 객체가 생성(인스턴스화)될 때 **자동으로 호출되어** 멤버 변수를 초기화하고 필요한 초기 작업을 수행하는 특별한 함수입니다.

- **특징:**
    - 생성자의 이름은 **클래스의 이름과 반드시 같아야 합니다.**
    - **반환 타입(return type)을 지정하지 않습니다** (심지어 `void`도 안됩니다).
    - 파이썬처럼, 매개변수를 다르게 하여 여러 개의 생성자를 만들 수 있습니다 (**생성자 오버로딩**, Constructor Overloading).
        

```c++
#include <iostream>
#include <string>

class Student {
private:
    std::string name;
    int studentID;

public:
    // 1. 매개변수가 있는 생성자 (일반적인 경우)
    Student(std::string n, int id) {
        name = n;
        studentID = id;
        std::cout << "Student(이름, 학번) 생성자 호출됨" << std::endl;
    }

    // 2. 매개변수가 없는 기본 생성자 (Default Constructor)
    // - 생성자가 하나라도 정의되면, 컴파일러는 기본 생성자를 자동으로 만들어주지 않습니다.
    // - 따라서 필요하다면 직접 정의해야 합니다.
    Student() {
        name = "이름없음";
        studentID = 0;
        std::cout << "Student() 기본 생성자 호출됨" << std::endl;
    }

    void printInfo() {
        std::cout << "이름: " << name << ", 학번: " << studentID << std::endl;
    }
};

int main() {
    Student s1("홍길동", 2025001); // 1번 생성자 호출
    s1.printInfo();

    Student s2; // 2번 기본 생성자 호출
    s2.printInfo();
    return 0;
}
```

#### **소멸자 (Destructor): 객체의 마지막을 정리하다**

소멸자는 생성자와 정반대의 역할을 합니다. 객체의 수명이 다하여 **메모리에서 소멸될 때 자동으로 호출**됩니다. 주된 용도는 객체가 사용하던 동적 메모리나 파일, 네트워크 연결 등의 자원을 해제(정리)하는 것입니다.
- **특징:**
    - 소멸자의 이름은 **클래스 이름 앞에 물결표(`~`)**를 붙입니다.
    - 생성자와 마찬가지로 **반환 타입이 없으며, 매개변수도 가질 수 없습니다.**
    - 클래스당 오직 하나의 소멸자만 가질 수 있습니다.

`main` 함수의 `p1`처럼 스택 메모리에 생성된 객체는 함수가 끝날 때 소멸자가 호출되고, `new` 키워드를 사용해 힙 메모리에 생성된 `p2`같은 객체는 `delete` 키워드가 호출될 때 소멸자가 호출됩니다.

``` c++
class FileManager {
private:
    FILE* file_ptr; // C언어 스타일 파일 포인터

public:
    FileManager(const char* filename) {
        std::cout << filename << " 파일을 엽니다." << std::endl;
        file_ptr = fopen(filename, "w"); // 쓰기 모드로 파일 열기
    }

    // 소멸자: 객체가 사라질 때 파일을 자동으로 닫아준다.
    ~FileManager() {
        std::cout << "파일을 닫습니다." << std::endl;
        if (file_ptr != NULL) {
            fclose(file_ptr);
        }
    }
};

int main() {
    // 함수가 시작될 때 FileManager 객체 생성 -> 생성자 호출 (파일 열기)
    FileManager myFile("report.txt");
    // ... 파일 관련 작업 수행 ...

    // main 함수가 끝날 때 myFile 객체 소멸 -> 소멸자 호출 (파일 닫기)
    return 0;
}
```

#### **`this` 포인터: 나 자신을 가리키는 숨겨진 포인터**

`this`는 **모든 멤버 함수 안에 숨겨져 있는 특별한 포인터**입니다. 이 포인터는 **현재 멤버 함수를 호출한 객체 자신의 주소**를 담고 있습니다. 파이썬 클래스의 메서드에서 첫 번째 인자로 `self`를 명시적으로 사용하는 것과 거의 동일한 개념입니다.

- **주요 용도:**
    1. **멤버 변수와 매개변수의 이름이 같을 때** 이를 구분하기 위해 사용됩니다.
    2. 객체 자신의 주소를 반환하거나 다른 함수에 전달해야 할 때 사용됩니다.

```c++
class Rectangle {
private:
    int width;
    int height;

public:
    // 매개변수 이름(width, height)이 멤버 변수 이름과 동일하다.
    Rectangle(int width, int height) {
		this->width = width;
		this->height = height;
    }

    int getArea() {
        // 여기서는 이름 충돌이 없으므로 this를 생략해도 된다.
        // 컴파일러는 자동으로 this->width * this->height로 해석한다.
        return width * height;
    }
};
```

C++에서는 `this`를 명시적으로 쓰지 않아도 멤버에 접근할 수 있지만, 파이썬에서는 `self.`을 반드시 붙여야 한다는 문법적 차이가 있습니다. 하지만 '객체 스스로를 참조한다'는 근본적인 아이디어는 같습니다. 이 개념들을 이해하면 C++ 클래스의 동작 방식과 객체 지향 프로그래밍의 원리를 더 깊이 파악할 수 있습니다.