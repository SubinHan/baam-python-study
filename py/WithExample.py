class Hello:
    def __enter__(self):
        # 사용할 자원을 가져오거나 만든다(핸들러 등)
        print('Enter...')
        return self # 반환값이 있어야 VARIABLE를 블록내에서 사용할 수 있다
        
    def say_hello(self, name):
        # 자원을 사용한다. ex) 인사한다
        print('Hello ' + name)

    def __exit__(self, exc_type, exc_val, exc_tb):
        # 마지막 처리를 한다(자원반납 등)
        print('Exit...')

print('before with')
my_hello = Hello()
for i in range(3):
    my_hello.say_hello('Obama')

class AnotherClass:
    def __enter__(self):
        print('Enter')
        return self 
        
    def say_hello(self, name):
        print('Hello ' + name)

    def __exit__(self, exc_type, exc_val, exc_tb):
        # 마지막 처리를 한다(자원반납 등)
        print('Exit')


a = AnotherClass()
with a:
    # 입출력 시작
    # 이 안의 구문은 그냥 if문 for문 쓰듯이 쓰면된다.
    my_hello.say_hello('Obama')
    my_hello.say_hello('Trump')
    # 입출력 끝
print('after with')

# 객체의 lifecycle을 조절하고 싶을 때, with를 쓴다.
# (객체가 생성되고, 객체를 다시 파괴하는)
# 왜 이런 일이 있느냐, 예를 들어 파일 입출력을 하는 경우,
# OS랑 소통을 하면서 파일에 대한 권한을 얻어야 한다.

# 만약 파일입출력 권한을 전역적으로 취득하고
# 프로그램이 끝날 때까지 반환을 안한다면?