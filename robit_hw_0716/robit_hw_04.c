#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_N 1000   // 배열 최대 크기

int countMedianSubsequence(int arr[], int n, int b);  // 중앙값이 b인 부분수열 개수 계산

int main(void)
{
    int arr[MAX_N];
    int n, b, i;
    int result;

    printf("N : ");
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_N)   // N 입력 및 범위 검사 예외처리
    {
        printf("N의 입력이 잘못되었습니다. (1 ~ %d 사이의 정수)\n", MAX_N);
        return 0;
    }

    printf("B : ");
    if (scanf("%d", &b) != 1)   // B 입력값 검사 예외처리
    {
        printf("입력이 잘못되었습니다.\n");
        return 0;
    }

    printf("수열 입력 : ");
    for (i = 0; i < n; i++)
    {
        if (scanf("%d", &arr[i]) != 1)   // N개의 숫자를 배열에 차례대로 저장 예외처리
        {
            printf("입력이 잘못되었습니다.\n");
            return 0;
        }
    }

    result = countMedianSubsequence(arr, n, b);

    printf("중앙값이 %d인 부분수열의 개수 : %d\n", b, result);

    return 0;
}

// 부분수열 A[start..end] 안에서
// B보다 큰 수 - B보다 작은 수 = 0 이고, B를 포함하는 경우를 센다.
// (길이가 홀수이면서 중앙값이 B인 조건과 동일)
int countMedianSubsequence(int arr[], int n, int b)
{
    int start, end;
    int balance;      // B보다 큰 수의 개수 - B보다 작은 수의 개수
    int containsB;     // 부분수열에 B가 포함되어 있는지 여부 (0: 없음, 1: 있음)
    int count = 0;

    for (start = 0; start < n; start++)
    {
        balance = 0;
        containsB = 0;

        for (end = start; end < n; end++)   // end를 늘려가며 balance를 누적 계산
        {
            if (arr[end] > b)
                balance++;
            else if (arr[end] < b)
                balance--;
            else
                containsB = 1;

            if (containsB == 1 && balance == 0)   // B가 포함되어 있고, 큰 수와 작은 수 개수가 같으면 중앙값이 B인 부분수열
                count++;                          
        }
    }

    return count;
}
