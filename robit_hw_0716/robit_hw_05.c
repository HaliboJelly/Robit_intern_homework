#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NUM 10000

void markSquareMultiples(int isNotSquareFree[], int max);   // 제곱수의 배수를 표시하는 함수

int main(void)
{
    static int isNotSquareFree[MAX_NUM + 1] = { 0, };   // 0이면 제곱ㄴㄴ수, 1이면 제곱수의 배수
    int min, max;
    int number;
    int count = 0;

    printf("min : ");
    if (scanf("%d", &min) != 1)   // 범위의 최솟값을 입력받음
    {
        printf("잘못된 입력입니다.\n");
        return 0;
    }

    printf("max : ");
    if (scanf("%d", &max) != 1)   // 범위의 최댓값을 입력받음
    {
        printf("잘못된 입력입니다.\n");
        return 0;
    }

    if (min < 1 || max > MAX_NUM || min > max)   // 입력 범위가 조건(1~10000)에 맞는지 확인 
    {
        printf("1부터 %d 사이에서 올바른 범위를 입력하세요.\n", MAX_NUM); //예외처리
        return 0;
    }

    markSquareMultiples(isNotSquareFree, max);   // 2^2, 3^2, 4^2 ... 의 배수를 미리 표시

    for (number = min; number <= max; number++)   // min부터 max까지 확인하며 개수를 셈
    {
        if (isNotSquareFree[number] == 0)   // 표시되지 않았다면 제곱ㄴㄴ수
        {
            count++;
        }
    }
    printf("제곱 ㄴㄴ수 : %d개\n", count);

    for (number = min; number <= max; number++)   // 같은 범위를 다시 확인하며 값 출력
    {
        if (isNotSquareFree[number] == 0)
        {
            printf("%d ", number);
        }
    }
    printf("\n");

    return 0;
}

// 2부터 시작하는 divisor의 제곱(4, 9, 16, ...)의 배수를 모두 1로 표시
// (divisor는 1보다 큰 수이므로 2부터 시작 -> 1의 제곱인 1은 제외됨)
void markSquareMultiples(int isNotSquareFree[], int max)
{
    int divisor;
    int multiple;

    for (divisor = 2; divisor * divisor <= max; divisor++)   // divisor^2 이 max를 넘지 않을 때까지
    {
        for (multiple = divisor * divisor; multiple <= max; multiple += divisor * divisor)
        {
            isNotSquareFree[multiple] = 1;   // divisor^2 의 배수를 표시
        }
    }
}
