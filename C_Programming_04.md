
7장에 들어가기 앞서..

### PART 1. Visual Studio Community 설치 (초소형 C++ 환경)

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

### PART 2. 첫 프로젝트 및 테스트 환경 구축

이제 C++ 코드를 작성하고, 내가 짠 코드가 잘 작동하는지 자동으로 검증해 줄 테스트 환경을 만들어 봅시다.

#### 🚀 1단계: 솔루션 및 메인 프로젝트 생성

'솔루션'은 여러 '프로젝트'를 담는 하나의 큰 바구니라고 생각하면 쉬워요. 우리는 코드 바구니(`AlgorithmProject`)와 테스트 바구니(`AlgorithmTests`)를 하나의 솔루션 안에 만들 거예요.

1. Visual Studio 2022를 실행하고 `새 프로젝트 만들기`를 선택합니다.
2. **`빈 프로젝트(Empty Project)`**를 검색해서 선택하고 `다음`을 누릅니다.
    - _C++ 콘솔 앱을 선택하면 불필요한 파일이 생길 수 있으니, 가장 깔끔한 '빈 프로젝트'로 시작하는 게 좋아요._
3. 프로젝트 이름은 `AlgorithmProject`, 솔루션 이름은 `AlgorithmSolution` 등으로 정하고 `만들기`를 누릅니다.
    
#### 🧪 2단계: 테스트 프로젝트 추가 및 연결
1. **솔루션 탐색기**(보통 화면 오른쪽에 있음)에서 최상단 `솔루션 'MyAlgorithmSolution'`을 마우스 오른쪽 클릭하고 `추가` > `새 프로젝트`를 선택하세요.
2. **`네이티브 단위 테스트 프로젝트(Native Unit Test Project)`**를 검색해서 선택하고 `다음`을 누릅니다.
3. 프로젝트 이름은 `MyAlgorithmTests`로 정하고 `만들기`를 누릅니다.
4. 이제 테스트 프로젝트가 실제 코드를 "알아볼 수 있도록" 연결해 줍시다.
    - `MyAlgorithmTests` 프로젝트 아래의 **`참조`**를 마우스 오른쪽 클릭 > `참조 추가` 선택.
    - `MyAlgorithmProject`를 체크하고 `확인`을 누릅니다.

---

### PART 3. 실전 코드 작성 및 테스트

자, 모든 준비가 끝났습니다! 간단한 덧셈 함수를 만들고, 이 함수가 올바르게 작동하는지 테스트해 봅시다.

#### ⌨️ 1단계: 테스트할 코드 작성하기
1. `MyAlgorithmProject`에서 `소스 파일` 폴더를 오른쪽 클릭 > `추가` > `새 항목`을 선택합니다.
2. `헤더 파일(.h)`을 선택하고, 이름은 `MyMath.h`로 지정합니다.
3. `MyMath.h` 파일에 간단한 덧셈 함수를 작성합니다.
    ```c++
    // MyMath.h
    #pragma once
    
    inline int add(int a, int b) {
        return a + b;
    }
    ```
    
#### ✅ 2단계: 테스트 코드 작성하기
1. `MyAlgorithmTests` 프로젝트의 `unittest1.cpp` 파일을 엽니다.
2. 아래와 같이 `MyMath.h`를 테스트하는 코드를 작성합니다.    
```c++
    // unittest1.cpp
    #include "CppUnitTest.h"
    #include "../MyAlgorithmProject/MyMath.h" // 우리가 만든 헤더 파일 포함!
    
    using namespace Microsoft::VisualStudio::CppUnitTestFramework;
    
    TEST_CLASS(MyMathTests) // 테스트들을 묶어줄 클래스
    {
    public:
        TEST_METHOD(TestAddFunction) // 테스트 케이스 하나
        {
            // 2와 3을 더하면 5가 나와야 한다!
            Assert::AreEqual(5, add(2, 3));
    
            // -1과 1을 더하면 0이 나와야 한다!
            Assert::AreEqual(0, add(-1, 1));
        }
    };
    ```
    

#### ▶️ 3단계: 테스트 실행 및 결과 확인
1. Visual Studio 상단 메뉴에서 `테스트` > `테스트 탐색기`를 엽니다.
2. 테스트 탐색기 창에 `MyMathTests` 아래 `TestAddFunction`이 보일 거예요.
3. 창 왼쪽 상단의 초록색 재생 버튼 **`모두 실행(▶▶)`**을 클릭하세요.
4. 테스트가 성공적으로 통과하면, 테스트 이름 옆에 **녹색 체크(✔)** 표시가 나타납니다!







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

