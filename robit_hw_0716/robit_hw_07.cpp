#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_LEN 100   // 최대 99개 문자 + NULL 문자를 위한 크기

int getLength(char str[]);                                  // 문자열의 길이를 구함
int isMatchAt(char inputStr[], int start, char subStr[], int subLength);  // start 위치부터 subStr과 일치하는지 확인
void findAllPositions(char inputStr[], char subStr[]);      // subStr이 등장하는 모든 위치를 찾아 출력

int main(void)
{
    char inputStr[MAX_LEN];   // 전체 입력 문자열 저장
    char subStr[MAX_LEN];     // 찾으려는 문자열 저장

    printf("최대 99개 문자 입력 <inputStr> : ");
    if (scanf("%99s", inputStr) != 1)   // 전체 문자열을 입력받음 (예외처리: %99s로 오버플로우 방지)
    {
        printf("입력이 잘못되었습니다.\n");
        return 0;
    }

    printf("찾는 문자열 <subStr> : ");
    if (scanf("%99s", subStr) != 1)   // 찾을 문자열을 입력받음  (예외처리: %99s로 오버플로우 방지)
    {
        printf("입력이 잘못되었습니다.\n");
        return 0;
    }

    findAllPositions(inputStr, subStr);   // 위치를 찾아서 바로 출력

    return 0;
}

int getLength(char str[])
{
    int length = 0;

    while (str[length] != '\0')   // 문자열의 끝인 '\0'을 만날 때까지 이동
    {
        length++;
    }

    return length;
}

// inputStr의 start 위치부터 subLength만큼 subStr과 완전히 같은지 확인 (
int isMatchAt(char inputStr[], int start, char subStr[], int subLength)
{
    int j;

    for (j = 0; j < subLength; j++)
    {
        if (inputStr[start + j] != subStr[j])   // 한 글자라도 다르면 일치하지 않음
        {
            return 0;
        }
    }

    return 1;   // 끝까지 다 같으면 일치
}

void findAllPositions(char inputStr[], char subStr[])
{
    int inputLength;
    int subLength;
    int i;
    int count = 0;   // 찾은 위치의 개수

    inputLength = getLength(inputStr);
    subLength = getLength(subStr);

    printf("%s의 위치 : ", subStr);

    if (subLength == 0 || subLength > inputLength)   // 찾는 문자열이 없거나 더 긴 경우
    {
        printf("없음\n");
        return;
    }

    for (i = 0; i <= inputLength - subLength; i++)   // 찾기를 시작할 위치를 한 칸씩 이동
    {
        if (isMatchAt(inputStr, i, subStr, subLength) == 1)
        {
            printf("%d ", i + 1);   // 배열 인덱스는 0부터 시작하므로 1을 더해서 출력
            count++;
        }
    }

    if (count == 0)   // 끝까지 찾았지만 한 번도 못 찾은 경우
    {
        printf("없음");
    }

    printf("\n");
}