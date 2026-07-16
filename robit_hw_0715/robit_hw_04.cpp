#include <stdio.h>

int main(void)
{
    float x = 0.0f, y = 0.0f, r = 0.0f;
    char c;
    printf("Input Arithmetic Operation\n");
    printf("ex)     3.4 + 8.5\n");
    printf("        2.9 - 5.4\n");
    printf("        3.9 * 8.0\n");
    printf("        3.9 / 8\n");
    printf("input : ");
    scanf_s("%f %c %f", &x, &c, 1, &y);

    if (c=='+')
    {
        r=x+y;
    }
    else if (c=='-')
    {
        r=x-y;
    }
    else if (c == '*')
    {
        r=x*y;
    }
    else if (c=='/')
    {
        if(y==0)//0으로 나눌 수 없기에 예외처리
        {
            return printf("0은 쓸 수 없습니다.");
        }
        else
        {
            r=x/y;
        }
    }
    else if (c=='^')
    {
        
        r = 1.0f;
        float i = 0.0f;
        for (i = 1.0f; i <= y; i++)
        {
            r *= x;
        }
    }
    else
    {
        printf("지원하지 않습니다.\n");//다른 기호를 쓸 시 예외처리
    }

    printf("%.2f %c %.2f = %.2f\n", x, c, y, r);

    return 0;
}