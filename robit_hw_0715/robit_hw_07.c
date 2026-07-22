#include <stdio.h>

int main(void)
{
    int n = 0, r = 0;
    int i = 0;
    int fac_n = 1, fac_r = 1, fac_nr = 1;
    int result1 = 0, result2 = 0, result3 = 0, result4 = 0;

    printf("n을 입력하세요 : ");
    scanf_s("%d", &n);
    printf("r을 입력하세요 : ");
    scanf_s("%d", &r);

     /* 예외 처리 1: 음수 입력 */
    if (n < 0 || r < 0)
    {
        printf("n과 r은 0 이상의 정수여야 합니다.\n");
        return 1;
    }

    /* 예외 처리 2: r이 n보다 큰 경우 */
    if (r > n)
    {
        printf("r은 n보다 클 수 없습니다.\n");
        return 1;
    }

    /* 예외 처리 3: 오버플로우 방지 (int 범위가 너무 작아 13! 이상 계산시 위험) */
    if (n + r - 1 > 12)
    {
        printf("입력한 값이 너무 커서 정수 범위를 초과할 수 있습니다.\n");
        return 1;
    }

    /* n! */
    for (i = 1; i <= n; i++)
        fac_n *= i;

    /* r! */
    for (i = 1; i <= r; i++)
        fac_r *= i;

    /* (n-r)! */
    for (i = 1; i <= n - r; i++)
        fac_nr *= i;

    /* 순열 nPr */
        result1 = fac_n / fac_nr;
    
    /* 중복순열 nΠr */
    result2 = 1;
    for (i = 0; i < r; i++)
        result2 *= n;

    /* 조합 nCr */
    result3 = fac_n / (fac_nr * fac_r);

    /* 중복조합 nHr */
    {
        int fac_h = 1, fac_hr = 1;   // (n+r-1)!, (n+r-1-r)! = (n-1)!
        for (i = 1; i <= n + r - 1; i++)
            fac_h *= i;
        for (i = 1; i <= n - 1; i++)
            fac_hr *= i;
        result4 = fac_h / (fac_hr * fac_r);
    }

    printf("\n----결과----\n");
    printf("순열(%dP%d)   = %d\n", n, r, result1);
    printf("중복순열(%d^%d) = %d\n", n, r, result2);
    printf("조합(%dC%d)   = %d\n", n, r, result3);
    printf("중복조합(%dH%d) = %d\n", n, r, result4);

    return 0;
}
