# 1. C 언어와 파이썬의 비교

## 1.1 왜 C 언어를 사용해야 하나요?

### 컴퓨터 내부를 깊이 이해할 수 있습니다.

- 파이썬은 우리가 직접 메모리를 관리하거나 하드웨어를 제어할 필요가 없습니다.
	- 매우 편리하지만, 학습자는 컴퓨터 내부의 동작에 대해 잘못된 추측을 할 가능성이 높으며 크고 작은 오해들이 쌓여 많은 불편함과 생산성의 저해를 초래합니다.
- C 언어는 우리가 메모리를 직접 할당하고 해제하며, 데이터가 물리적으로 어떻게 저장되는지를 고민하게 만듭니다.
- 처음에는 어렵겠지만, 이후 자바나 파이썬 등 훨씬 추상화 수준이 높은 언어를 사용할 때, 통찰력을 가지게 되어 더 효율적이고 견고한 코드를 작성하게 될 것입니다.

----
### 성능의 한계를 돌파할 수 있습니다.

- 파이썬은 편리하지만, 처리 속도 면에서 C 언어보다 느린 경우가 많습니다.
	- 파이썬은 실행될 때마다 코드를 한 줄씩 해석하는 '인터프리터 언어'이기 때문입니다.
- 반면 C 언어는 한 번 작성하면 기계어로 '컴파일'되어 실행되기 때문에 훨씬 빠릅니다.
- 또한 명령의 추상화 수준이 훨씬 낮기 때문에, 조금은 복잡한 코드지만 훨씬 세세하게 개발자의 의도를 적용할 수 있습니다.
#### 고성능 계산에서의 우위
- 수많은 데이터를 빠르게 처리해야 하는 과학 계산, 시뮬레이션, 이미지/영상 처리 같은 분야에서는 파이썬만으로는 속도 한계에 부딪힐 수 있습니다.
- 이때 핵심적인 계산 부분만 C로 작성하고 파이썬에서 불러와 사용하면 성능 문제를 해결할 수 있습니다. 
	- 여러분이 사용하는 NumPy, Pandas 같은 라이브러리의 핵심 부분도 사실 C나 Fortran, C++으로 구현되어 있습니다.
#### 임베디드 시스템
- 리소스(메모리, 처리 능력)가 제한적인 소형 장치(라즈베리 파이 같은 보드, 각종 센서, 웨어러블 기기 등)에서는 파이썬 같은 고수준 언어는 부담스럽습니다. 
- 이때 C 언어는 하드웨어를 직접 제어하고 최소한의 리소스로 최대한의 성능을 뽑아낼 수 있는 강력한 도구가 됩니다.

----
### 다른 언어의 '뼈대'를 이해하게 됩니다.

- 자바(Java), C++, C#, Go, 심지어 파이썬 자체도 그 기저에는 C 언어 또는 C++이 깔려 있습니다. 
	- 예를 들어, 파이썬의 핵심 엔진(CPython)은 C로 작성되어 있습니다. 
- C를 배우면 다른 고수준 언어들이 '내부적으로' 어떻게 작동하는지, 메모리를 어떻게 관리하는지 등을 더 쉽게 이해할 수 있게 됩니다. 
- 마치 모든 그림의 기본이 되는 '데생'을 배우는 것과 같을 것입니다.
- C를 통해 단단한 기초를 다지면, 새로운 프로그래밍 언어를 배우는 속도와 깊이가 달라질 것입니다.

----
### 시스템 프로그래밍의 문을 엽니다.

- **운영체제(OS), 디바이스 드라이버, 파일 시스템, 네트워크 스택** 등 컴퓨터 시스템의 가장 낮은 수준에서 작동하는 소프트웨어들은 거의 대부분 C 언어로 작성됩니다. 
- 만약 여러분이 이런 분야에 관심을 가지고 있다면, C 언어는 필수적인 도구입니다. 
	- 파이썬으로는 접근하기 어려운 영역입니다.


**결론적으로, C 언어는 파이썬의 편리함 뒤에 숨겨진 '원리'를 이해하고, 파이썬이 도달하기 어려운 '극한의 성능'과 '시스템 제어' 영역을 탐험할 수 있게 해주는 열쇠입니다.** 처음에는 낯설고 불편할 수 있지만, C 언어를 배우는 시간은 여러분을 더 깊이 있는 개발자로 성장시키는 소중한 경험이 될 것입니다.

----
## 1.2 파이썬과 C 언어의 차이점

- 파이썬과 C 언어는 둘 다 프로그램을 만드는 데 사용되지만, 작동 방식과 개발자가 얻는 '제어권' 측면에서 큰 차이를 보입니다. 
- 파이썬이 마치 잘 정돈된 만능 도구 상자라면, C 언어는 각 도구를 직접 만들고 조립해야 하는 정밀 공작실에 가깝다고 할 수 있습니다. 
- 이러한 차이점을 이해하는 것이 C 언어 학습의 첫걸음입니다.

### 인터프리터 언어 vs 컴파일 언어

- **파이썬 (인터프리터 언어):** 파이썬 코드는 여러분이 작성한 그대로 (또는 중간에 바이트코드라는 형태로 변환되어) **인터프리터**라는 프로그램에 의해 한 줄씩 읽히고 즉시 실행됩니다. 마치 통역사가 말을 듣자마자 바로 통역해 주는 것과 같습니다.
    - **장점:** 코드를 저장하고 바로 실행해 볼 수 있어 개발 속도가 빠르고, 오류를 즉시 확인할 수 있습니다.
    - **단점:** 매번 해석 과정을 거치기 때문에 컴파일 언어보다 실행 속도가 느릴 수 있습니다.

![[Pasted image 20250702110054.png]]

- **C 언어 (컴파일 언어):** C 코드는 실행하기 전에 **컴파일러**라는 특별한 프로그램에 의해 컴퓨터가 이해할 수 있는 **기계어 코드**로 전체가 한 번에 변환됩니다. 이 변환된 파일(.exe, .out 등)을 실행 파일이라고 부르며, 이 실행 파일은 컴파일러 없이도 독립적으로 실행될 수 있습니다. 마치 미리 번역된 책을 읽는 것과 같습니다.
    - **장점:** 한 번 컴파일되면 실행 속도가 매우 빠릅니다. 컴퓨터의 하드웨어에 직접 명령을 내리는 것에 가깝기 때문입니다.
    - **단점:** 코드를 수정할 때마다 다시 컴파일 과정을 거쳐야 하므로 개발 과정이 다소 번거로울 수 있습니다.

![[Pasted image 20250702110108.png]]

----

### 동적 타이핑 vs 정적 타이핑

- **파이썬 (동적 타이핑):** 파이썬에서는 변수를 선언할 때 그 변수에 어떤 종류의 데이터(정수, 문자열, 리스트 등)를 담을지 미리 지정할 필요가 없습니다. 프로그램이 실행되는 동안 값이 할당될 때 파이썬이 알아서 타입을 결정합니다. 한 변수에 정수를 넣었다가 나중에 문자열을 넣어도 문제가 되지 않습니다.
    ```run-python
    my_variable = 10         # 정수 할당
    my_variable = "Hello"    # 문자열 할당, 오류 없음
    ```
    - **장점:** 코드를 훨씬 유연하게 작성할 수 있고, 개발 속도가 빠릅니다.
    - **단점:** 런타임(프로그램 실행 중)에 타입 관련 오류가 발생할 가능성이 있고, 코드 가독성 측면에서 혼란을 줄 수도 있습니다.
- **C 언어 (정적 타이핑):** C 언어에서는 변수를 선언할 때 반드시 그 변수가 어떤 타입의 데이터를 저장할 것인지 명시해야 합니다. 한 번 타입을 정하면 그 변수에는 해당 타입의 데이터만 저장할 수 있습니다.
	``` c
	int my_integer = 10;     // 정수형 변수 선언 및 초기화
	// my_integer = "Hello"; // 오류 발생! 정수형 변수에 문자열 할당 불가
	```
	- **장점:** 컴파일 시점에 타입 오류를 잡아낼 수 있어 프로그램의 안정성이 높아집니다. 또한, 컴파일러가 변수에 필요한 메모리 크기를 미리 알 수 있어 효율적인 메모리 관리가 가능합니다.
	- **단점:** 코드가 파이썬보다 길어질 수 있고, 개발자가 항상 변수의 타입을 신경 써야 합니다.

----
### 자동 메모리 관리 (Garbage Collection) vs 수동 메모리 관리

- **파이썬 (자동 메모리 관리 - Garbage Collection):** 파이썬은 **가비지 컬렉션(Garbage Collection)** 이라는 기능을 통해 개발자가 직접 메모리를 할당하거나 해제할 필요 없이 자동으로 관리해 줍니다. 
- 변수를 만들거나 객체를 생성하면 파이썬이 알아서 메모리를 할당하고, 더 이상 사용하지 않는 메모리는 자동으로 회수(청소)합니다.
    - **장점:** 메모리 누수(Memory Leak)와 같은 복잡한 메모리 관리 오류로부터 자유롭습니다. 개발 생산성이 크게 향상됩니다.
    - **단점:** 개발자가 메모리 관리의 세부 사항을 제어할 수 없으며, 가비지 컬렉터가 작동하는 시점을 예측하기 어려워 때로는 성능 저하를 야기할 수 있습니다.

- **C 언어 (수동 메모리 관리):** C 언어에서는 개발자가 직접 `malloc()`, `free()` 같은 함수를 사용하여 메모리를 '빌려 쓰고' 다 쓴 후에는 '반납'해야 합니다. 마치 도서관에서 책을 빌리고 다 읽으면 직접 반납해야 하는 것과 같습니다.
    - **장점:** 메모리 사용을 개발자가 원하는 대로 최대한 효율적으로 제어할 수 있습니다. 이는 제한된 리소스를 가진 환경(임베디드 시스템)이나 초고성능이 요구되는 애플리케이션에서 매우 중요합니다.
    - **단점:** 개발자가 메모리 관리에 대한 책임이 커지므로, 메모리 누수, 잘못된 메모리 접근(Segmentation Fault) 등과 같은 심각한 오류가 발생할 위험이 있습니다.

----
### 4. 구문 및 기본적인 코드 구조 (Hello World 예시)
``` c
// c_hello.c
#include <stdio.h> // 표준 입출력 라이브러리를 포함합니다.

int main() { // 프로그램의 시작점인 main 함수를 정의합니다.
    printf("Hello, World!\n"); // 화면에 문자열을 출력하는 함수입니다.
    return 0; // 프로그램이 성공적으로 종료되었음을 나타냅니다.
}
```

- **특징:**
    - `#include <stdio.h>`: `printf` 함수를 사용하기 위해 **헤더 파일**을 포함해야 합니다. C 언어는 필요한 기능을 직접 불러와야 합니다.
    - `int main() { ... }`: 모든 C 프로그램은 `main`이라는 특별한 함수에서 시작합니다. `main` 함수는 운영체제가 프로그램을 실행할 때 가장 먼저 호출하는 함수입니다.
    - `printf()`: 파이썬의 `print()`와 유사하게 화면에 출력하는 함수입니다.
    - `;`(세미콜론): 각 문장의 끝에는 세미콜론을 붙여야 합니다.
    - `\n`: "줄 바꿈"을 의미하는 특수 문자입니다.
    - `return 0;`: 프로그램이 오류 없이 정상적으로 종료되었음을 운영체제에 알려주는 코드입니다.

----
## 1.3 개발 환경 설정

- 실습
- Visual Studio Code
- https://winlibs.com/
- 에디터 없이 gcc와 메모장만을 이용해서 코딩해보기


----

# 2. C 언어의 기본 문법

### 2.1 변수와 데이터 타입

- 파이썬에서는 변수에 어떤 데이터든 자유롭게 담을 수 있었습니다.
- 하지만 C 언어에서는 다릅니다.
	- C 언어의 변수는 '그릇'에 비유할 수 있는데, 이 그릇은 처음에 어떤 종류의 데이터를 담을지 미리 정해져야 합니다. 
	- 그리고 한 번 정해진 그릇에는 그 종류의 데이터만 담을 수 있습니다. 이것이 바로 C 언어의 **정적 타이핑(Static Typing)** 특징입니다.

#### C 언어의 데이터 타입
 
- **정수형 (Integers):** 소수점이 없는 숫자를 저장합니다.
    - `int`: 가장 기본적인 정수형입니다. 대부분의 경우 `int`를 사용합니다.
    - `short`: `int`보다 작은 범위의 정수를 저장합니다. 메모리를 절약할 때 사용될 수 있습니다.
    - `long`: `int`보다 큰 범위의 정수를 저장합니다.
    - `long long`: 가장 큰 범위의 정수를 저장합니다.
    - **부호 없는 정수형 (Unsigned Integers):** 위에 언급된 정수형들 앞에 `unsigned`를 붙여서 사용할 수 있습니다 (`unsigned int`, `unsigned short` 등). 이들은 음수를 표현할 수 없는 대신, 양수의 표현 범위가 두 배로 늘어납니다. (예: `unsigned int`는 0부터 양수만 표현)
- **실수형 (Floating-point Numbers):** 소수점이 있는 숫자를 저장합니다.
    - `float`: 단정밀도 부동 소수점 숫자입니다. 비교적 작은 범위의 소수점을 저장하며, 정밀도가 낮습니다.
    - `double`: 배정밀도 부동 소수점 숫자입니다. `float`보다 훨씬 넓은 범위와 높은 정밀도를 제공합니다. 대부분의 경우 `double`을 사용하는 것이 좋습니다.
- **문자형 (Characters):** 단일 문자를 저장합니다.
    - `char`: 하나의 문자를 저장합니다. 내부적으로는 문자에 해당하는 정수 값(ASCII 코드 등)으로 저장됩니다.
- **논리형 (Boolean - C99 표준 이후):** 
	- C 언어에는 파이썬의 `True`/`False`와 같은 독립적인 `bool` 타입이 원래 없었습니다. 
	- 보통 `0`을 `False`로, `0`이 아닌 모든 값을 `True`로 간주하여 사용했습니다.
	- 하지만 C99 표준부터 `<stdbool.h>` 헤더 파일을 포함하면 `_Bool` 타입과 `true`, `false` 매크로를 사용할 수 있게 되었습니다.

- **메모리 크기:** 
	- 각 데이터 타입은 컴퓨터 메모리에서 차지하는 공간(바이트 수)이 다릅니다. 
	- 이 크기는 시스템(운영체제, 컴파일러)에 따라 조금씩 다를 수 있지만, 일반적으로 `char`는 1바이트, `short`는 2바이트, `int`는 4바이트, `long`은 4 또는 8바이트, `long long`은 8바이트, `float`는 4바이트, `double`은 8바이트를 차지합니다. 
	- 메모리 사용량을 직접 제어할 수 있다는 것이 C 언어의 강점 중 하나입니다.

----
#### 변수 선언 및 초기화

- C 언어에서 변수를 만들고 값을 할당하는 방법은 다음과 같습니다.

- **선언 (Declaration):** 변수를 사용하겠다고 컴파일러에게 알리는 과정입니다. 어떤 '타입'의 '이름'을 가진 변수를 만들겠다고 명시합니다.

```c
int score;       // score라는 이름의 정수형 변수를 선언합니다.
float pi_value;  // pi_value라는 이름의 실수형 변수를 선언합니다.
char initial;    // initial이라는 이름의 문자형 변수를 선언합니다.
```

- **초기화 (Initialization):** 선언된 변수에 처음으로 값을 할당하는 과정입니다. 초기화하지 않은 변수에는 '쓰레기 값'이 들어있을 수 있으므로, 항상 변수를 사용하기 전에 초기화하는 것이 좋습니다.

``` c
int age = 25;              // age 변수를 정수 25로 초기화합니다.
float pi_value = 3.14f;    // pi_value 변수를 3.14로 초기화합니다.
double temperature = 27.5; // temperature 변수를 실수 27.5로 초기화합니다.
char grade = 'A';          // grade 변수를 문자 'A'로 초기화합니다. (문자는 작은따옴표)
```

- 선언과 초기화를 한 줄에 동시에 할 수도 있고, 따로 할 수도 있습니다.

``` c
int width;      // 선언
width = 100;    // 나중에 초기화 또는 값 할당
```

---

#### 4. 타입 캐스팅 (Type Casting): 타입 강제 변환

- C 언어는 정적 타이핑 언어이기 때문에 원칙적으로는 다른 타입의 값을 저장할 수 없습니다. 
- 하지만 특정 상황에서 의도적으로 변수의 타입을 다른 타입으로 '강제로 변환'해야 할 때가 있습니다. 
- 이것을 **타입 캐스팅(Type Casting)** 또는 형 변환이라고 합니다.

- **사용 방법:** `(변환할_타입) 변수_또는_값`

```c
int total_score = 95;
int num_students = 4;

// 정수 나누기: C에서 정수 나누기는 결과도 정수로 나옵니다 (소수점 이하 버림)
// 파이썬의 `//` 연산자와 유사합니다.
double average = total_score / num_students; // 결과: 23.0 (95 / 4 = 23.75 -> 23)
printf("Average (without casting): %.2f\n", average); // 출력: 23.00

// 타입 캐스팅 사용: 나눗셈을 하기 전에 피연산자 중 하나를 double로 변환하여 실수 나눗셈을 유도
average = (double)total_score / num_students; // 결과: 23.75
printf("Average (with casting): %.2f\n", average); // 출력: 23.75

// 다른 예시: float를 int로 변환 (소수점 이하 버려짐)
float pi_float = 3.141592f; // float 타입임을 명시하기 위해 'f' 접미사 사용
int pi_int = (int)pi_float; // pi_int는 3이 됩니다.
printf("Pi as int: %d\n", pi_int); // 출력: 3

// char를 int로 변환 (ASCII 값으로 변환)
char ch = 'A';
int ascii_value = (int)ch; // ascii_value는 'A'의 ASCII 값인 65가 됩니다.
printf("ASCII value of 'A': %d\n", ascii_value); // 출력: 65
```

- **주의사항:**
	- 타입 캐스팅은 데이터 손실이 발생할 수 있습니다. 예를 들어, `double`을 `int`로 캐스팅하면 소수점 이하가 버려집니다.
	- 크기가 큰 타입에서 작은 타입으로 캐스팅할 때는 데이터가 잘릴 수 있습니다 (오버플로우/언더플로우 발생 가능성).
	
---

- C 언어에서 변수와 데이터 타입을 정확히 이해하는 것은 매우 중요합니다. 
	- 이는 메모리 사용의 효율성과 프로그램의 안정성에 직접적인 영향을 미치기 때문입니다. 
- 파이썬처럼 '알아서 해주는' 것이 아니라, 개발자가 직접 '어떤 데이터를 어디에 어떻게 저장할지'를 명확히 지시해야 한다는 점을 기억하세요.


----
### 2.2 연산자: C 언어에서 값들을 '조작'하는 방법

연산자는 변수나 값들을 가지고 덧셈, 비교, 논리 판단 등의 작업을 수행할 때 사용됩니다. 파이썬과 C 언어는 많은 연산자를 공유하지만, C 언어에만 있는 독특한 연산자도 있습니다.
#### 산술 연산자: 계산의 기본
- 파이썬과 거의 동일합니다.
- `+` (덧셈): `a + b`
- `-` (뺄셈): `a - b`
- `*` (곱셈): `a * b`
- `/` (나눗셈): `a / b`
    - **주의:** C 언어에서 **정수와 정수의 나눗셈은 결과도 정수**로 나옵니다 (소수점 이하 버림). 
    - 파이썬의 `//` 연산자와 같습니다. 
	    - 정확한 실수 나눗셈을 원한다면, 피연산자 중 하나를 실수형으로 **타입 캐스팅**해야 합니다 (예: `(double)a / b`).
- `%` (나머지): `a % b`

```c
int a = 10, b = 3;
printf("a + b = %d\n", a + b); // 13
printf("a / b (integer) = %d\n", a / b); // 3 (소수점 버림)
printf("a / b (double) = %.2f\n", (double)a / b); // 3.33
printf("a %% b = %d\n", a % b); // 1
```

#### 관계 연산자: 값들의 관계 비교

- 두 값의 크기 관계를 비교하여 **참(True) 또는 거짓(False)**을 판단합니다. C 언어에서는 참은 **`0이 아닌 값`**으로, 거짓은 **`0`**으로 표현합니다. 
- == (같다): a == b
- `!=` (같지 않다): `a != b`
- `<` (작다): `a < b`
- `>` (크다): `a > b`
- `<=` (작거나 같다): `a <= b`
- `>=` (크거나 같다): `a >= b`

```c
int x = 5, y = 10;
printf("x == y is %d\n", x == y); // 0 (False)
printf("x < y is %d\n", x < y);   // 1 (True)
```

#### 논리 연산자: 조건들의 논리적 결합

- 여러 조건을 조합하여 최종적인 참/거짓을 판단합니다.
- `&&` (AND): 두 조건이 모두 참일 때만 참 (파이썬의 `and`)
- `||` (OR): 두 조건 중 하나라도 참이면 참 (파이썬의 `or`)
- `!` (NOT): 조건의 참/거짓을 반대로 바꾼다 (파이썬의 `not`)

``` c
int age = 20;
int has_license = 1; // 1은 true, 0은 false로 가정

if (age >= 18 && has_license) {
    printf("운전 가능\n");
} else {
    printf("운전 불가능\n");
}
```

#### 증감 연산자 (`++`, `--`): C 언어의 독특한 편리함

- 이 연산자들은 C 언어에서 아주 자주 사용되며, 파이썬에는 없는 개념입니다. 변수의 값을 **1 증가시키거나 1 감소**시킬 때 사용합니다.
- `++` (증가 연산자): 변수 값을 1 증가시킵니다.
- `--` (감소 연산자): 변수 값을 1 감소시킵니다.

- 이 연산자들은 변수 앞에 붙을 때(전위 연산)와 뒤에 붙을 때(후위 연산) 약간의 차이가 있습니다.
	- **전위 연산 (`++변수`, `--변수`):** 변수의 값을 먼저 1 증가/감소시킨 후, 그 값을 현재 문장에서 사용합니다.
	- **후위 연산 (`변수++`, `변수--`):** 변수의 값을 현재 문장에서 먼저 사용한 후, 그 값을 1 증가/감소시킵니다.

```c
int i = 5;
int j = 5;

int result1 = ++i; // i를 먼저 6으로 만들고, result1에 6을 할당
int result2 = j++; // result2에 먼저 5를 할당하고, 그 후에 j를 6으로 만듦

printf("i: %d, result1: %d\n", i, result1); // i: 6, result1: 6
printf("j: %d, result2: %d\n", j, result2); // j: 6, result2: 5
```

처음에는 헷갈릴 수 있지만, 코드를 짧고 효율적으로 만들 때 유용하게 쓰입니다.

---

### 2.3 조건문: 특정 조건에 따라 코드 실행하기

- 조건문은 특정 조건이 참일 때만 특정 코드 블록을 실행하도록 합니다. 파이썬과 비슷하지만, 구문에서 차이가 있습니다.
#### `if`, `else if`, `else`: 가장 기본적인 조건문
- 파이썬의 `if`/`elif`/`else`와 동일한 역할을 합니다.
- `if (조건)`: 조건이 참일 때 실행될 코드 블록
- `else if (조건)`: 앞의 `if`나 `else if`가 거짓이고, 현재 조건이 참일 때 실행될 코드 블록
- `else`: 앞의 모든 조건이 거짓일 때 실행될 코드 블록

**구문 특징:**
- **괄호 `()`:** 조건식은 반드시 괄호 안에 넣어야 합니다.
- **중괄호 `{}`:** 실행될 코드 블록은 반드시 중괄호로 묶어야 합니다. (한 줄짜리 코드 블록은 생략 가능하지만, 명시적으로 사용하는 것이 좋습니다.)
- **참/거짓:** C 언어에서 **`0`은 거짓**이고, **`0이 아닌 모든 값`은 참**입니다.

```c
int score = 85;

if (score >= 90) {
    printf("학점: A\n");
} else if (score >= 80) { // 파이썬의 elif
    printf("학점: B\n");
} else if (score >= 70) {
    printf("학점: C\n");
} else {
    printf("학점: F\n");
}
```

#### `switch` 문: 여러 개의 '정확한 값'과 비교할 때 유용
- `switch` 문은 하나의 변수나 표현식의 값이 여러 경우의 수 중 어떤 것과 일치하는지에 따라 다른 코드를 실행할 때 사용합니다. 파이썬 3.10부터 추가된 **구조적 패턴 매칭(Structural Pattern Matching)**과 유사한 기능을 제공하지만, C의 `switch`는 주로 **정수형 값**에 대한 비교에 특화되어 있습니다.
```c
int day = 3; // 1: 월요일, 2: 화요일, ...

switch (day) {
    case 1:
        printf("월요일\n");
        break; // break를 사용하여 해당 case 실행 후 switch 문을 빠져나옵니다.
    case 2:
        printf("화요일\n");
        break;
    case 3:
        printf("수요일\n");
        break;
    default: // case에 해당하지 않는 모든 경우 (파이썬의 else와 유사)
        printf("다른 요일\n");
        break;
}
```

- **`switch` 문의 주요 특징:**
	- `switch (표현식)`: `표현식`의 값은 **정수형(int, char 등)**이어야 합니다.
	- `case 값:`: `표현식`의 값이 `값`과 일치할 때 해당 `case` 아래의 코드가 실행됩니다.
	- `break;`: **매우 중요!** `break` 문을 만나면 `switch` 문을 빠져나옵니다. 
		- `break`가 없으면, 일치하는 `case` 이후의 모든 `case` 문이 연달아 실행됩니다 (이를 **Fall-through**라고 부르며, 의도적으로 사용하는 경우도 있지만 대부분의 경우 오류를 유발합니다).
	- `default:`: 어떤 `case`에도 해당하지 않을 때 실행됩니다 (선택 사항).
    

---

### 2.4 반복문: 코드 블록을 여러 번 실행하기

- 반복문은 특정 코드 블록을 조건이 만족하는 동안 또는 특정 횟수만큼 반복 실행할 때 사용합니다.
#### `for` 문: 반복 횟수가 명확할 때 주로 사용
- 파이썬의 `for item in list:` 형태와는 구조가 완전히 다릅니다. C 언어의 `for` 문은 반복 횟수를 직접 제어할 때 강력합니다.
- **구조:** `for (초기화; 조건; 증감)`
- **초기화:** 반복문이 시작될 때 한 번 실행됩니다 (예: 반복 변수 선언 및 초기화 `int i = 0;`).
- **조건:** 매 반복마다 검사합니다. 조건이 **참(0이 아닌 값)**이면 반복을 계속하고, **거짓(0)**이면 반복을 종료합니다 (예: `i < 5;`).
- **증감:** 한 번의 반복이 끝날 때마다 실행됩니다 (예: `i++` 또는 `i = i + 1;`).

```c
// 0부터 4까지 출력
for (int i = 0; i < 5; i++) {
    printf("%d ", i);
}
printf("\n"); // 출력: 0 1 2 3 4
```

- **파이썬 `for` 루프와의 차이:** 파이썬의 `for` 루프는 주로 `list`나 `range` 같은 **반복 가능한(iterable) 객체**를 순회하는 데 사용됩니다.

```python
# 파이썬 for 루프
for i in range(5): # 0, 1, 2, 3, 4를 순회
    print(i, end=" ")
```

- C 언어의 `for`는 반복 횟수와 증감 조건을 개발자가 직접 명시하여 제어하는 방식입니다.

#### `while` 문, `do-while` 문: 조건이 만족하는 동안 반복
- **`while` 문:** 조건이 **참**인 동안 코드 블록을 반복 실행합니다. 코드를 실행하기 **전에** 조건을 먼저 검사합니다.
```c
int count = 0;
while (count < 3) { // count가 3보다 작은 동안 반복
    printf("Count: %d\n", count);
    count++; // count를 1 증가시킵니다.
}
// 출력:
// Count: 0
// Count: 1
// Count: 2
```

- `while` 문은 파이썬의 `while` 문과 동일한 개념입니다.
- **`do-while` 문:** 코드 블록을 **최소 한 번 실행한 후** 조건을 검사합니다. 조건이 참이면 반복을 계속합니다.

```c
int num = 5;
do {
    printf("Do-while test: %d\n", num);
    num++;
} while (num < 5); // 조건이 거짓이므로 한 번만 실행됨
// 출력:
// Do-while test: 5
```

- `do-while`은 파이썬에는 없는 구문입니다. 적어도 한 번은 실행되어야 하는 특정 상황(예: 사용자 입력 유효성 검사)에서 유용하게 사용됩니다.

#### 3. `break`와 `continue`: 반복문 제어
- `break`와 `continue`는 파이썬과 동일한 방식으로 작동하며, 반복문의 흐름을 제어합니다.
- **`break`:** 현재 반복문을 **즉시 종료**하고, 반복문 다음의 코드로 넘어갑니다.
```c
for (int i = 0; i < 10; i++) {
    if (i == 5) {
        break; // i가 5가 되면 반복문 종료
    }
    printf("%d ", i);
}
printf("\n"); // 출력: 0 1 2 3 4
```

- **`continue`:** 현재 반복의 나머지 부분을 **건너뛰고**, 다음 반복으로 넘어갑니다.

``` c
for (int i = 0; i < 5; i++) {
    if (i == 2) {
        continue; // i가 2일 때는 이 아래 코드를 건너뛰고 다음 반복으로
    }
    printf("%d ", i);
}
printf("\n"); // 출력: 0 1 3 4 (2는 출력되지 않음)
```

- 이러한 연산자와 조건문, 반복문은 모든 프로그래밍 언어의 기본 골격이 됩니다. 
- 파이썬에서의 경험을 바탕으로 C 언어의 미묘한 구문적 차이와 메모리/타입 처리 방식의 차이를 이해하는 데 집중하면 빠르게 익숙해질 수 있을 것입니다.