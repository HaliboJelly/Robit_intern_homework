#include <stdio.h>

int main(void)
{
    int n = 0;
    int i, j;

    printf("값을 입력하세요.");
    scanf_s("%d", &n);

    // 위쪽 절반 (1행 ~ n행, n행이 가운데 줄)
    for (i = 1; i <= n; i++)
    {
        // "*" "공백" "*" 순으로 쓰기 반복
        for (j = 0; j < i; j++)
            printf("*");
        for (j = 0; j < (n - i) * 2; j++)
            printf(" ");
        for (j = 0; j < i; j++)
            printf("*");
        printf("\n");
    }

    // 아래쪽 절반 (n-1행 ~ 1행, 위쪽과 대칭)
    for (i = n - 1; i >= 1; i--)
    {
        // "*" "공백" "*" 순으로 쓰기 반복
        for (j = 0; j < i; j++)
            printf("*");
        for (j = 0; j < (n - i) * 2; j++)
            printf(" ");
        for (j = 0; j < i; j++)
            printf("*");
        printf("\n");
    }

    return 0;
}