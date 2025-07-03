#include <stdio.h>

// [반환형] [이름]([인자])
// {
//      [구문]
// }

// Prototype
void HelloFunction();
void PrintInteger(int a);
void PrintTwoInteger(int a, int b);
void PrintChar(char c);
int Add(int a, int b);

int main()
{
    HelloFunction();
    PrintInteger(3);
    PrintInteger(5);
    PrintTwoInteger(10, 20);

    int result = Add(3, 5);
    printf("%d\n", result);

    PrintInteger(Add(10, 20));
    PrintTwoInteger(Add(20, 30), Add(30, 50));

    PrintChar('A');

    PrintChar(Add('A', 1));
    PrintChar(66);
    PrintInteger('A');
}

void HelloFunction()
{
    printf("Hello, Function!\n");
}

void PrintInteger(int a)
{
    printf("Int: %d\n", a);
}

void PrintTwoInteger(int a, int b)
{
    printf("Two Int: %d, %d\n", a, b);
}

int Add(int a, int b)
{
    return a + b;
}

void PrintChar(char c)
{
    printf("Character: %c\n", c);
}