
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

### PART 2. 첫 프로젝트 및 테스트 환경 구축

이제 C++ 코드를 작성하고, 내가 짠 코드가 잘 작동하는지 자동으로 검증해 줄 테스트 환경을 만들어 봅시다.

#### 🚀 1단계: 솔루션 및 메인 프로젝트 생성

'솔루션'은 여러 '프로젝트'를 담는 하나의 큰 바구니라고 생각하면 쉬워요. 우리는 코드 바구니(`AlgorithmProject`)와 테스트 바구니(`AlgorithmTests`)를 하나의 솔루션 안에 만들 거예요.

1. Visual Studio 2022를 실행하고 `새 프로젝트 만들기`를 선택합니다.
2. **`빈 프로젝트(Empty Project)`** 를 검색해서 선택하고 `다음`을 누릅니다.
    - _C++ 콘솔 앱을 선택하면 불필요한 파일이 생길 수 있으니, 가장 깔끔한 '빈 프로젝트'로 시작하는 게 좋아요._
3. 프로젝트 이름은 `dsa_main`, 솔루션 이름은 `dsa` 등으로 정하고 `만들기`를 누릅니다.


#### 📕2단계: 라이브러리 솔루션 생성

우리는 자료구조와 알고리즘을 배웁니다. 이 자료구조와 알고리즘은, 다른 프로그램에 의해서 사용되는 일종의 **라이브러리** 입니다. 따라서, `라이브러리`와 `클라이언트`를 분리하는 것은 좋은 시도가 될 것입니다.
1. **솔루션 탐색기**(보통 화면 오른쪽에 있음)에서 최상단 `솔루션 '`dsa`'`을 마우스 오른쪽 클릭하고 `추가` > `새 프로젝트`를 선택하세요.
2. **`빈 프로젝트(Empty Project)`** 를 검색해서 선택하고 `다음`을 누릅니다.
3. 프로젝트 이름은 dsa_lib으로 정하고 `만들기`를 누릅니다.
4. 해당 프로젝트를 `우클릭`하여, `속성(Properties)`를 누릅니다.
5. `General`에서 `Configuration Type`을 `Static library (.lib)`으로 변경합니다.
6. 이제 main 프로젝트가 실제 코드를 "알아볼 수 있도록" 연결해 줍시다.
    - `dsa_main` 프로젝트 아래의 **`참조`**를 마우스 오른쪽 클릭 > `참조 추가` 선택.
    - `dsa_lib`를 체크하고 `확인`을 누릅니다.


---

### PART 3. 실전 코드 작성 및 테스트

자, 모든 준비가 끝났습니다! 간단한 덧셈 함수를 만들고, 이 함수가 올바르게 작동하는지 테스트해 봅시다.
#### ✅ 1단계: Profiler 클래스 코드 작성하기

먼저, 시간 측정을 담당할 `Profiler` 클래스를 만듭니다. 이 클래스는 `.h` 파일(설계도)과 `.cpp` 파일(구현부)로 나뉩니다.

1. `dsa_lib` 프로젝트의 `소스 파일` 폴더를 오른쪽 클릭 > `추가` > `새 항목`을 선택합니다.
2. **`헤더 파일(.h)`**을 선택하고, 이름은 `Profiler.h`로 지정합니다.
3. `Profiler.h` 파일에 `Profiler` 클래스의 구조를 작성합니다.    
    ```c++
// Profiler.h

#pragma once

#include <chrono>

namespace gb
{
	class Profiler
	{
	private:
		double& result;
		std::chrono::time_point<std::chrono::high_resolution_clock> start_time_point;

	public:
		Profiler(double& result_ref);
		~Profiler();
	};
}
    ```
    
4. 다시 `dsa_lib` 프로젝트의 `소스 파일` 폴더를 오른쪽 클릭 > `추가` > `새 항목`을 선택합니다.
5. 이번에는 **`C++ 파일(.cpp)`**을 선택하고, 이름은 `Profiler.cpp`로 지정합니다.
6. `Profiler.cpp` 파일에 `Profiler` 클래스의 실제 동작 코드를 작성합니다.
    ```c++
// Profiler.cpp

#include "Profiler.h"

namespace gb
{
	// 생성자 구현
	Profiler::Profiler(double& result_ref)
		: result(result_ref) // 멤버 변수 초기화
	{
		// 생성 시점의 시간을 기록
		start_time_point = std::chrono::high_resolution_clock::now();
	}

	// 소멸자 구현
	Profiler::~Profiler()
	{
		// 소멸 시점의 시간을 기록
		auto end_time_point = std::chrono::high_resolution_clock::now();

		// 시작 시간과 끝 시간의 차이를 마이크로초(long long) 단위로 계산
		long long start_us = std::chrono::time_point_cast<std::chrono::microseconds>(start_time_point).time_since_epoch().count();
		long long end_us = std::chrono::time_point_cast<std::chrono::microseconds>(end_time_point).time_since_epoch().count();
		
		// 경과 시간 계산
		long long duration_us = end_us - start_us;
		
		// 결과를 밀리초(double) 단위로 변환하여 참조하고 있던 외부 변수에 저장
		result = duration_us * 0.001;
	}
}
    ```

### ✅ 2단계: Main에서 실험해보기

```c++
#include <iostream>
#include "Profiler.h"

int main() 
{
	long long result = 0;
	double elapsed_time_ms = 0.0;

	{
		gb::Profiler profiler(elapsed_time_ms);
		for (int i = 1; i <= 100000000; ++i)
		{
			result += i;
		}
	}

	std::cout << "result: " << result << " elapsed time: " << elapsed_time_ms << "ms" << std::endl;

	return 0;
}
```

- 하지만 main()은 한 build 단위에서 하나만 존재해야 합니다.
- 매번 이렇게 임시로 만든 main()에서 테스트를 해보고, 정상적으로 동작하는지 확인해야 할까요?
- 만약 그러다가 Profiler가 변경되었을 때, Profiler가 여전히 잘 동작한다는 보장을 어떻게 할 수 있을까요?

### 🧪 3단계: 테스트 프로젝트 추가 및 연결
1. **솔루션 탐색기**(보통 화면 오른쪽에 있음)에서 최상단 `솔루션 '`dsa`'`을 마우스 오른쪽 클릭하고 `추가` > `새 프로젝트`를 선택하세요.
2. **`네이티브 단위 테스트 프로젝트(Native Unit Test Project)`** 를 검색해서 선택하고 `다음`을 누릅니다.
3. 프로젝트 이름은 `dsa_test` 로 정하고 `만들기`를 누릅니다.
4. 이제 테스트 프로젝트가 실제 코드를 "알아볼 수 있도록" 연결해 줍시다.
    - ``dsa_test`` 프로젝트 아래의 **`참조`**를 마우스 오른쪽 클릭 > `참조 추가` 선택.
    - `dsa_lib`를 체크하고 `확인`을 누릅니다.


### ✅ 4단계: 테스트 코드 작성하기

`Profiler` 클래스가 의도대로 시간을 잘 측정하는지 확인하는 테스트 코드를 작성합니다.
1. `MyAlgorithmTests` 프로젝트의 `unittest1.cpp` 파일을 엽니다.
2. 아래와 같이 `Profiler.h`를 테스트하는 코드를 작성합니다.
    ```c++
// ProfilerTest.cpp

#include "pch.h"
#include "CppUnitTest.h"
#include "../gbstudy/Profiler.h"

#include <thread>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace gb;

namespace UnitTest
{
	TEST_CLASS(ProfilerTest)
	{
	public:

		TEST_METHOD(UpdatesVariableOnDestruction)
		{
			// 1. 준비 (Arrange)
			double elapsed_time_ms = 0.0;

			// 2. 실행 (Act)
			{
				Profiler profiler(elapsed_time_ms);
				std::this_thread::sleep_for(std::chrono::milliseconds(20));
			}

			// 3. 검증 (Assert)
			Assert::IsTrue(elapsed_time_ms >= 20.0, L"Elapsed time should be at least 20ms.");
			Assert::IsTrue(elapsed_time_ms < 30.0, L"Elapsed time should be reasonable.");
		}

		TEST_METHOD(WorksWithNoDelay)
		{
			// 1. 준비 (Arrange)
			double elapsed_time_ms = -1.0;

			// 2. 실행 (Act)
			{
				Profiler profiler(elapsed_time_ms);
			}

			// 3. 검증 (Assert)
			Assert::IsTrue(elapsed_time_ms >= 0.0, L"Elapsed time should be non-negative.");
			Assert::IsTrue(elapsed_time_ms < 1.0, L"Elapsed time should be very small.");
		}
	};
}
    ```

### ▶️ 3단계: 테스트 실행 및 결과 확인

1. Visual Studio 상단 메뉴에서 `테스트` > `테스트 탐색기`를 엽니다.
2. 테스트 탐색기 창에 `ProfilerTests` 아래 `UpeateVariablesOnDestruction`이 보일 거예요.
3. 창 왼쪽 상단의 초록색 재생 버튼 **`모두 실행(▶▶)`**을 클릭하세요.
4. 테스트가 성공적으로 통과하면, 테스트 이름 옆에 **녹색 체크(✔)** 표시가 나타납니다!



---

### 🤔 왜 프로그램을 두 개나 만들어야 할까요?

우리가 최종적으로 사용자에게 줄 프로그램은 `.exe` 파일 하나입니다. 그런데 개발할 때는 "테스트용 프로그램"을 하나 더 만들어요. 왜 이런 번거로운 일을 할까요?


![[C_Programming_04_010_WhyTest]]


**자동차 공장 🚗을 생각해보면 아주 쉬워요.**

1. **우리가 만드는 코드 (엔진, 브레이크 등 부품)** `Profiler.cpp` 같은 코드 하나하나는 자동차의 **엔진, 브레이크, 타이어** 같은 핵심 **부품**이에요.
2. **메인 프로그램 (`.exe`) (완성된 자동차)** 이 부품들을 모두 조립해서 만든 **완성된 자동차**가 바로 우리가 만들려는 `.exe` 프로그램입니다. 고객은 이 차를 받아서 실제 도로에서 운전하죠.
3. **테스트 프로젝트 (성능 시험장, 안전 검사장)** 자동차 공장에서는 완성된 차를 내보내기 전에, **부품들이 제대로 작동하는지 미리 시험**해보는 안전 검사장이 있습니다. 브레이크만 따로 가져와서 제동력을 시험하고, 엔진만 따로 돌려서 성능을 확인하죠. 이 **"부품 성능 시험장"** 이 바로 **"테스트 프로젝트"** 입니다.
    
---

### 🌟 테스트 프로젝트를 만들면 좋은 점 3가지
#### 1. 믿음과 확신이 생겨요 👍
> "내 코드는 확실히 잘 돌아가!"
> 
자동차 전체를 조립하기 전에 브레이크 부품이 완벽하다고 확인했다면, 나중에 완성된 차에 문제가 생겨도 "적어도 브레이크 문제는 아닐 거야"라고 확신할 수 있죠.

마찬가지로, `Profiler`가 시간을 잘 재는지 미리 테스트해두면, 나중에 프로그램 전체가 이상하게 동작해도 `Profiler` 자체는 믿고 다른 곳을 점검할 수 있습니다.

#### 2. 버그를 엄청나게 빨리 찾을 수 있어요 🐞

> "문제가 생기면, 범인은 바로 너!"

차가 고장 났을 때, 엔진 문제인지, 바퀴 문제인지, 핸들 문제인지 처음부터 다 뜯어보려면 너무 힘들어요. 하지만 평소에 부품별로 성능을 기록해뒀다면 "아, 엔진 소리가 이상하네. 엔진부터 보자!"라고 바로 원인을 좁힐 수 있죠.

테스트가 있으면, 코드에 문제가 생겼을 때 **어떤 부품(어떤 함수나 클래스)에서 문제가 발생했는지** 테스트가 즉시 알려줍니다. 전체 프로그램을 뒤질 필요 없이 고장 난 곳만 바로 고칠 수 있어요.

#### 3. 코드를 마음껏 바꿀 수 있어요 🧑‍🔧

> "업그레이드는 자신 있게!"

기존 엔진을 더 좋은 신형 엔진으로 바꾸고 싶을 때, 바로 차에 넣지 않죠. 성능 시험장에서 신형 엔진을 충분히 테스트해보고, 문제가 없다고 확인되면 그때 차에 조립합니다.

마찬가지로, `Profiler`의 성능을 개선하거나 코드를 수정했을 때, 테스트 프로젝트를 돌려서 **기존 기능들이 여전히 잘 동작하는지** 바로 확인할 수 있습니다. 덕분에 코드를 고쳤다가 다른 기능까지 망가뜨리는 "끔찍한 재앙"을 막을 수 있습니다.

**결론적으로, 테스트 프로젝트는 우리가 만든 코드 부품들의 "품질 보증서"를 발급해주는 아주 중요하고 고마운 존재랍니다!**