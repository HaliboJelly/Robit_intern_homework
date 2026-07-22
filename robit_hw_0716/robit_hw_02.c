#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define LENGTH 8   // 입력받을 숫자의 개수

void printArray(int numbers[], int length);      // 배열을 한 줄로 출력
void selectionSort(int numbers[], int length);   // 선택 정렬 실행

int main(void)
{
    int numbers[LENGTH];   // 입력받은 숫자 8개를 저장
    int i;

    printf("입력\n\n");

    for (i = 0; i < LENGTH; i++)
    {
        printf("%d : ", i);

        if (scanf("%d", &numbers[i]) != 1)   // 배열의 각 위치에 숫자를 입력
        {
            printf("잘못된 입력입니다.\n");
            return 0;
        }
    }

    printf("\n정렬 중간 과정\n\n");

    printArray(numbers, LENGTH);      // 정렬하기 전 상태를 먼저 출력
    selectionSort(numbers, LENGTH);   // 입력한 배열을 선택 정렬

    printf("\n출력\n\n");

    for (i = 0; i < LENGTH; i++)
    {
        printf("%d : %d\n", i, numbers[i]);   // 정렬이 끝난 배열을 출력
    }

    return 0;
}

void selectionSort(int numbers[], int length)
{
    int i;
    int j;
    int maxIndex;   // 현재 범위에서 가장 큰 수의 위치
    int temp;       // 두 숫자를 바꿀 때 잠시 저장

    for (i = length - 1; i > 0; i--)   // 배열의 마지막 자리부터 하나씩 정함
    {
        maxIndex = 0;   // 첫 번째 수를 가장 크다고 가정

        for (j = 1; j <= i; j++)   // 아직 정렬되지 않은 범위만 확인
        {
            if (numbers[j] > numbers[maxIndex])
            {
                maxIndex = j;   // 더 큰 수를 찾으면 그 위치를 저장
            }
        }

        if (maxIndex != i)   // 가장 큰 수가 마지막 자리에 없을 때만 교환
        {
            temp = numbers[i];
            numbers[i] = numbers[maxIndex];
            numbers[maxIndex] = temp;

            printArray(numbers, length);   // 숫자를 바꾼 뒤 중간 과정 출력
        }
    }
}

void printArray(int numbers[], int length)
{
    int i;

    for (i = 0; i < length; i++)
    {
        printf("%4d", numbers[i]);   // 숫자 사이의 간격을 맞춰 한 줄로 출력
    }

    printf("\n");
}
