#include <stdio.h>

int main(void)
{
    float max = 0.0f, min = 0.0f, avg = 0.0f, num = 0.0f;
    int i = 0;

    for (i = 1; i <= 5; i++)
    {
        printf("%d 번째 실수를 입력하시오. ", i);
        scanf_s("%f", &num);
        avg += num;
        if (i == 1)
        {
            max = num;
            min = num;
        }
        else
        {
            // 두 번째 입력부터 max, min 비교하며 갱신
            if (num > max)
                max = num;
            else if (num < min)
                min = num;
        }
    }
    printf("----결과----\n");
    printf("평균은 %.6f입니다.\n", avg/5.0);
    printf("최대값은 %.6f입니다.\n", max);
    printf("최소값은 %.6f입니다.\n", min);
    
    return 0;
}