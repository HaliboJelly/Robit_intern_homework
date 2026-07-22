#include <stdio.h>

int main(void)
{
    int n = 0;
    int i, j;

    printf("값을 입력하세요.");
    scanf_s("%d", &n);

    for (i = 1; i <= n; i++)
    {
        if (i == n)
        {
            // 마지막 줄: 공백 없이 별로 꽉 채움 (2n-1개)
            for (j = 0; j < 2 * n - 1; j++)
                printf("*");
        }
        else
        {
            /*
                *
               * * <- 공백/별/공백/별
              *****
            로직: 공백 -> 오른쪽 별* -> 공백 -> 왼쪽 별*
            */
            for (j = 0; j < n-i; j++)// 공백 -> 오른쪽 별*
                printf(" ");
            printf("*");

            if(i>1)
            {
                for (j = 0; j < 2 * (i - 1) - 1; j++)//공백 -> 왼쪽 별*
                        printf(" ");
                    printf("*");
            }
        }
        printf("\n");
    }
    return 0;
}
