#include <stdio.h>

int main(void)
{
    int i, n, num1, num2, num3, x = 0;
    printf("n을 입력하시오. ");
    scanf_s("%d",&n);

    for(i=0;i<n;i++)
    {
        if (i==0)
        {
            num1 = 0;//초기 첫번째 두번째순느 미리 등록
            num2 = 1;
            x = num1;
        }
        else if (i==1)
        {
            x= num2;
        }
        else
        {
            //저장의 개념으로 접근
            num3 = num1 + num2;
            num1 = num2;
            num2 = num3;
            x=num3;    
        }
    }
    printf("%d번쨰 피보나치 수: %d",n,x);

    return 0;
}