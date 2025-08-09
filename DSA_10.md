
### 프로젝트 테스트 환경 구축

C++ 코드를 작성하고, 내가 짠 코드가 잘 작동하는지 자동으로 검증해 줄 테스트 환경을 만들어 봅시다.

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
    - `dsa_main` 프로젝트 아래의 **`참조`** 를 마우스 오른쪽 클릭 > `참조 추가` 선택.
    - `dsa_lib`를 체크하고 `확인`을 누릅니다.
    - `dsa_main 프로젝트`를 마우스 오른쪽 클릭 > `속성` 선택.
    - Configuration Properties > VC++ Directories를 선택
    - Include Directories의 값 부분을 눌러 Edit을 선택합니다.
    - 위의 빈 공간에 다음과 같이 값을 입력하고, `확인`을 누릅니다.
	    - `$(SolutionDir)dsa_lib\`


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
#include "../dsa_lib/Profiler.h"

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
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}

			// 3. 검증 (Assert)
			Assert::IsTrue(elapsed_time_ms >= 100.0, L"Elapsed time should be at least 20ms.");
			Assert::IsTrue(elapsed_time_ms < 115.0, L"Elapsed time should be reasonable.");
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



# 2. 정렬

## 2.2 병합 정렬

- 이 절에서는 **병합**이라는 단순한 작업에 기반한 정렬 알고리즘을 알아볼 것입니다.
- 병합이란, 두 개의 정렬된 배열을 하나의 큰 정렬된 배열로 합치는 작업을 의미합니다.
- 이 작업은 단순한 재귀적 방법으로 쉽게 구현됩니다.
	- 배열을 정렬할 때, 그것을 반으로 나누어 각각의 절반에 대해서 재귀적으로 정렬을 수행하고,
	- 다시 재귀적으로 정렬 결과를 병합하면 됩니다.

![[02_010_MergeSortIntro]]

----

### In-place 병합의 추상화

- 병합 작업의 구현은 단순합니다.
	- 두 입력 배열을 모두 담을 수 있을 만한 크기의 출력 배열을 준비합니다.
	- 두 입력 배열의 앞에서부터 둘 중 가장 작은 항목을 연속해서 뽑아 출력 배열의 앞에서부터 추가합니다.
- 위 구현의 문제는 다음과 같습니다:
	- 매우 큰 배열을 대상으로 병합 정렬을 할 때에는, 출력 배열을 매번 새로 생성하는 비용이 문제입니다.
- 따라서, 가능하다면 원본 배열 안에서 즉석으로 병합하는 것이 훨씬 더 바람직할 것입니다.
- 즉, 반복적으로 메모리를 할당하는 작업을 피하고, 고정된 메모리로 각각의 절반 크기 배열을 그 안에서 정렬하고 정렬된 두 개의 절반 부분들을 마찬가지로 같은 배열 안에서 병합할 수 있어야 합니다.
- 우선, 잠깐 병합 정렬이 어떤 식으로 흘러가야 좋을지 고민해봅시다.

![[02_020_Think_MergeSortImpl]]


- 구현은 복잡하지만, in-place 병합을 추상화하여 만들면 두고두고 유용하게 활용할 수 있습니다.
- 이를 위해 병합 메서드 merge(a, lo, mid, hi)를 정의합니다.
	- 이 메서드는 입력되는 배열의 정렬된 구간(부분 배열) a\[lo..mid\]와 a\[mid+1..hi]에 대해서 병합 정렬을 수행하여 하나로 정렬된 배열 a\[lo..hi\]를 남깁니다.

#### 구현: in-place 병합 추상화


``` c++

// 두 정렬된 하위 배열 a[lo..mid]와 a[mid+1..hi]를 병합합니다.
void merge(T a[], int lo, int mid, int hi) {
	// a[lo..hi]를 aux[]로 복사
	for (int k = lo; k <= hi; k++) {
		aux[k] = a[k];
	}

	// 다시 a[]로 병합
	int i = lo;
	int j = mid + 1;
	for (int k = lo; k <= hi; k++) {
		if (i > mid) {
			a[k] = aux[j++];
		}
		else if (j > hi) {
			a[k] = aux[i++];
		}
		else if (aux[j] < aux[i]) {
			a[k] = aux[j++];
		}
		else {
			a[k] = aux[i++];
		}
	}
}

```

![[02_030_VisualTraces_Merge]]


### 하향식(top-down) 병합 정렬

- 우리가 알아볼 최초의 병합 정렬은 in-place 병합 추상화 메서드에 기반하여 재귀적으로 구현되었습니다.
- 이것은 효율적인 알고리즘을 설계하는데 분할 정복 기법을 활용한 대표적인 사례라고 할 수 있습니다.
- 이러한 재귀적인 코드 자체가 이 알고리즘이 배열을 올바르게 정렬함을 연역적으로 증명할 수 있는 기반이 되어줍니다.
	- 즉, 만약 이 코드가 두 개의 부분 배열을 정렬한다면, 부분 배열들의 병합을 통해 전체 배열도 정렬하게 됩니다.
- 병합 정렬을 이해하기 위해서는 다음 그림과 같은 호출 동작 과정을 살펴보는 것이 큰 도움이 될 것입니다:
	- 1) 어떻게 분할되어서 정복되는지 확인하세요.
	- 2) 원소가 하나 남았을 때에는 어떻게 동작하는지 확인하세요.

![[02_040_VisualTraces_TopDownMergeSortCallTrace]]


#### 구현: 하향식 병합 정렬

```c++
#pragma once

#include "Sort.h"

namespace gb
{
	template <typename T>
	class MergeSort : public Sort<T> {
	private:
		// 정렬에 필요한 보조 배열
		T* aux = nullptr;

		// 두 정렬된 하위 배열 a[lo..mid]와 a[mid+1..hi]를 병합합니다.
		void merge(T a[], int lo, int mid, int hi) {
			// a[lo..hi]를 aux[]로 복사
			for (int k = lo; k <= hi; k++) {
				aux[k] = a[k];
			}

			// 다시 a[]로 병합
			int i = lo;
			int j = mid + 1;
			for (int k = lo; k <= hi; k++) {
				if (i > mid) {
					a[k] = aux[j++];
				}
				else if (j > hi) {
					a[k] = aux[i++];
				}
				else if (aux[j] < aux[i]) {
					a[k] = aux[j++];
				}
				else {
					a[k] = aux[i++];
				}
			}
		}

		// a[lo..hi]를 재귀적으로 정렬합니다.
		void _sort(T a[], int lo, int hi) {
			if (hi <= lo) return;
			int mid = lo + (hi - lo) / 2;
			_sort(a, lo, mid);
			_sort(a, mid + 1, hi);
			merge(a, lo, mid, hi);
		}

	public:
		// 소멸자에서 동적 할당된 메모리를 해제합니다.
		~MergeSort() override {
			if (aux != nullptr) {
				delete[] aux;
			}
		}

		// GBSort의 순수 가상 함수를 구현합니다.
		void sort(T a[], int n) override {
			// 보조 배열을 한 번만 할당합니다.
			if (aux == nullptr) {
				aux = new T[n];
			}
			_sort(a, 0, n - 1);
		}
	};
}

```

#### 병합 정렬의 실행 시간 분석

- 명제
	- 하향식 병합 정렬은 크기 N인 정렬을 배열할 때 ~1/2 N log N ... N log N 사이의 횟수로 비교 연산을 수행한다.
- 증명
	- C(N)을 크기 N인 배열을 정렬하는데 필요한 비교 연산 횟수라고 하자.
	- 먼저 C(0)=C(1)=0이라는 사실은 자명하다.
	- N>0인 N에 대해, sort() 메서드의 재귀적인 구조를 그대로 투영하여 다음과 같은 상한선과 하한선을 정의할 수 있다.
	- 상한선:
		- $$ C(N) \le C(\lfloor N/2 \rfloor) + C(\lceil N/2 \rceil) + N $$
		- 오른쪽의 첫 번째 항은 배열의 왼쪽 절반을 정렬하기 위한 비교 횟수를 의미하고, 두 번째 항은 오른쪽 절반을 정렬하기 위한 비교 횟수, 그리고 세 번째 항은 병합을 위한 비교 횟수이다.
	- 하한선: 
	- $$C(N) \ge C(\lfloor N/2 \rfloor) + C(\lfloor N/2 \rfloor) + \lfloor N/2 \rfloor$$
		- 왜냐하면, 병합을 위해 최소환 floor(N/2)만큼의 비교가 필요하기 때문이다.
	- 상기 하한에 맞닿는 경우, 그리고 N이 2의 승수인 경우 다음과 같이 정확한 해를 점화식으로 구할 수 있다.
		- $$C(2^n) = 2C(2^{n-1}) + 2^n$$
	- 양쪽을 2^n으로 나누면, 
		- $$\frac{C(2^n)}{2^n} = \frac{C(2^{n-1})}{2^{n-1}} + 1$$
	- 우측 수식에서 좌측 수식과 동일한 항을 추려내면, (C(2^n-1)을 풀어서 정리)
		- $$\frac{C(2^n)}{2^n} = \frac{C(2^{n-2})}{2^{n-2}} + 1 + 1$$
	- 위 과정들을 n-1번 반복하면,
		- $$\frac{C(2^n)}{2^n} = \frac{C(2^0)}{2^0} + n$$
	- 여기서 양쪽 수식에 2^n을 곱하면, 다음과 같은 해가 구해진다:
		- $$C(N) = C(2^n) = n2^n = N \lg N$$
	- 일반적인 N 값에 대한 정확한 해는 좀 더 복잡하나, 위와 같은 형태로 동일하게 적용하는 것은 어렵지 않다. 이 증명은 **입력값의 속성이나 정렬 상태에 무관하게 유효하다.**

![[02_050_MergeSortSubarrayDependenceTree]]

### 생각해보기

- 작은 부분 배열을 정렬하는 데에도 병합 정렬이 더 빠를까요?
- 배열이 이미 정렬된 상태인지 확인 후, 정렬되지 않은 경우에만 병합 정렬을 재귀적으로 수행하고 싶습니다. 어떻게 해야 할까요?
- 임시 작업 배열로의 복제 제거가 가능합니다. 다음 알고리즘을 생각해볼까요?
	- 먼저, 공간이 아닌 시간을 제거한다는 의미입니다.
	- 짝수 번째 sort를 수행하는 경우, aux와 src의 위치를 바꾸어 정렬하도록 하면, 복사 대신 ping-pong하면서 정렬을 수행할 수 있습니다.


#### 하향식 병합 정렬의 동작 과정

![[02_060_VisualTraces_TopDownMergeSort]]


### 상향식(Bottom-up) 병합 정렬

- 병합 정렬의 재귀적인 구현은 "분할 정복"이라는 알고리즘 설계 패러다임의 프로토타입과도 같습니다.
- 병합 정렬의 또 다른 구현 방법은 작은 부분 배열들을 한 번의 순회로 병합할 수 있도록 병합 작업의 순서를 조정하는 것입니다.
	- 그리고 다음번 순회에서 좀 더 커진 부분 배열들을 짝지어서 병합합니다.

![[02_070_VisualTraces_BottomUpMergeSort]]

- 이러한 일괄 병합 작업을 전체 배열이 정렬될 때까지 반복합니다.
	- 이 방법은 재귀적인 방법에 비해 코드 양이 더 적습니다.
- 먼저 1:1 병합 단계부터 시작합니다.
	- 그다음 2:2 병합, 4:4 병합과 같이 계속해 나갑니다.
- 다음 단계의 부분 배열이 이전 단계의 마지막 자투리 부분 배열보다 크기가 작은 역전 현상이 있을 수도 있습니다.
- 그 외의 경우에는 같은 크기의 부분 배열 간에 병합이 각 단계마다 그 크기를 두 배씩 증가시키면서 일어납니다.

```c++
#pragma once

#include "MergeSort.h"
#include <algorithm> // std::min을 사용하기 위해 포함

namespace gb
{

	template <typename T>
	class MergeSortBU : public MergeSort<T> {
	public:
		// MergeSort의 소멸자가 가상 소멸자이므로 자식 클래스의 소멸자도 자동으로 가상이 됩니다.
		// 별도의 동적 할당 멤버가 없으므로 소멸자를 명시적으로 작성할 필요는 없습니다.

		/**
		 * @brief 배열을 Bottom-Up(상향식) 병합 정렬을 사용하여 오름차순으로 정렬합니다.
		 * 재귀를 사용하지 않고 반복문으로 정렬을 수행합니다.
		 * @param a 정렬할 배열
		 * @param n 배열의 크기
		 */
		void sort(T a[], int n) override {
			// 보조 배열을 한 번만 할당합니다.
			// 부모 클래스인 MergeSort에 aux 포인터가 protected로 선언되어 있어야 접근 가능합니다.
			// 만약 private이라면, 이 클래스에서 별도로 aux를 선언하거나 부모 클래스의 접근 지정자를 변경해야 합니다.
			// 여기서는 부모의 aux를 사용할 수 있다고 가정합니다.
			if (this->aux == nullptr) {
				this->aux = new T[n];
			}

			// sz는 병합할 하위 배열의 크기를 의미합니다. 1, 2, 4, 8, ... 순으로 증가합니다.
			for (int sz = 1; sz < n; sz = sz + sz) {
				// lo는 병합할 두 하위 배열 중 첫 번째 배열의 시작 인덱스입니다.
				for (int lo = 0; lo < n - sz; lo += sz + sz) {
					// mid: 첫 번째 하위 배열의 끝 인덱스
					int mid = lo + sz - 1; 
					// hi: 두 번째 하위 배열의 끝 인덱스
					// 마지막 하위 배열이 배열의 전체 크기를 넘어가지 않도록 std::min()을 사용합니다.
					int hi = std::min(lo + sz + sz - 1, n - 1);
					
					this->merge(a, lo, mid, hi);
				}
			}
		}
	};

}
```


- 배열의 크기가 2의 승수이면, 하향식과 상향식 둘 다 정확히 같은 횟수의 비교 연산과 배열 접근이 이루어집니다.

- 상향식 병합 정렬의 또 다른 구현 방법으로 연결 리스트로 정렬한 데이터를 관리하는 방법이 있습니다.
	- 정렬되어야 할 부분 리스트로 크기 1인 리스트가 있다고 해봅시다.
	- 병합 단계를 한 번 지나면, 크기 2인 정렬된 부분 리스트가 만들어집니다.
	- ...
	- 이것을 전체 배열이 정렬될 때까지 반복합니다.
- 이 방법은 새로운 링크를 생성하다가 임시 리스트에 복젭할 필요 없이 즉석에서 기존 리스트의 연결 상태만 바꾸어서 리스트를 정렬 상태로 만들 수 있습니다.

### 정렬의 복잡도

- 병합 정렬을 알아야 하는 중요한 이유 중 하나는, 정렬 작업의 본질적인 속성을 이해하는데 필요한 "계산 복잡도"를 구하는 데 있어서 기반이 되는 기초 정보를 제공한다는 점입니다.

- 명제
	- 비교 기반 알고리즘이라면 N개의 항목을 정렬할 때 log(N!) ~ N log N 보다 적은 비교 횟수를 사용해서는 정렬을 완료할 수 없다.
- 증명
	- (귀찮으니 증명 생략)

- 결론: 병합 정렬은 점근적으로 볼 때, 존재할 수 있는 최적의 비교 기반 정렬 알고리즘이다.

### 창의적인 문제
###### 연결 리스트에 대한 병합 정렬을 구현해봅시다

(구조를 그림과 함께 설명)

- 연결 리스트의 경우, "분할"에 대한 고려가 필요합니다.
	- 왜냐하면, 가운데에 있는 원소를 곧바로 접근할 수 없기 때문입니다.
- 따라서 다음과 같은 방법을 사용해 볼 수 있습니다:
	- 두 개의 포인터를 사용합니다. 하나는 slow, 하나는 fast입니다.
	- slow는 한 칸씩 이동하고, fast는 두 칸씩 이동합니다.
	- fast가 끝에 다다르면, slow는 중점을 가리키고 있을 것입니다.
- 

###### 앞서 제안된 최적화 기법을 적용해봅시다.

- 작은 부분 배열을 정렬하는 경우에는, Insertion Sort를 사용합니다.
	- 작은 부분 배열은, 크기가 7 이하인 배열로 생각합니다.
- 배열이 이미 정렬된 상태인지 확인 후, 정렬되지 않은 경우에만 병합 정렬을 재귀적으로 수행하도록 합니다.
- 임시 작업 배열로의 복제를 제거합니다.
	- 항상 aux에서 원본 배열로 merge를 수행하는 것이 아니라, 다음 재귀 수준에서는 aux와 원본 배열의 역할을 바꿉니다.
	- aux와 원본 배열이 서로 Ping-pong 하면서 merge가 수행되도록 개선합니다.
	- Hint:
		- 맨 처음에, 입력 배열을 aux에 복제해야 합니다.
		- 함수의 signature를 변경해야 할 것입니다.
	