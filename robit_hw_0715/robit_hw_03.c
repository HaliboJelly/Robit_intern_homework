#include <stdio.h>

int main(void)
{
    int years =0;
    printf("년도를 입력하세요 : ");
    scanf_s("%d", &years);

    if((years%4==0 && years%100!=0)||(years%400==0))//윤년계산
    {
        printf("윤년");
    }
    else
    {
        printf("윤년 아님");
    }
    
    return 0;
}
