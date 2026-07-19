#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NOTE_COUNT 8   // 다장조 음의 개수 (c d e f g a b C)

int getLength(char str[]);          // 문자열의 길이를 직접 세어서 반환 ('\0' 전까지)
int isValidNote(char ch);           // c d e f g a b C 중 하나인지 검사
int isValidInput(char scale[]);     // 길이와 문자 구성이 올바른 입력인지 검사
int checkScale(char scale[]);       // 입력한 음의 순서가 어떤 형태인지 판별

int main(void)
{
    char scale[20];   // 잘못된 긴 입력까지 받아서 검사할 수 있도록 여유 있게 확보
    int result;

    printf("음 입력 (예 : cdefgabC) : ");
    if (scanf("%19s", scale) != 1)   // 공백 없이 문자열로 입력받음
    {
        printf("입력이 잘못되었습니다.\n");
        return 0;
    }

    if (!isValidInput(scale))   // 개수가 8개가 아니거나 이상한 문자가 섞인 경우 (예외처리 항목)
    {
        printf("잘못된 입력입니다. 숫자 말고 c d e f g a b C 문자 8개만 입력하세요.\n");
        return 0;
    }

    result = checkScale(scale);   // 판별 결과를 result에 저장

    switch (result)
    {
    case 1:
        printf("결과 : ascending\n");   // 함수가 1을 반환하면 오름차순
        break;
    case 2:
        printf("결과 : descending\n");   // 함수가 2를 반환하면 내림차순
        break;
    default:
        printf("결과 : mixed\n");   // 1과 2가 아니면 섞인 순서
        break;
    }

    return 0;
}

// 문자열이 NULL 문자('\0')로 끝날 때까지 직접 세어서 길이를 구한다.
int getLength(char str[])
{
    int count = 0;

    while (str[count] != '\0')
    {
        count++;
    }

    return count;
}

// 한 글자가 c d e f g a b C 중 하나인지 검사한다.
int isValidNote(char ch)  //예외처리 함수 (문자판별)
{
    char validNotes[9] = "cdefgabC";
    int i;

    for (i = 0; i < 8; i++)
    {
        if (ch == validNotes[i])
        {
            return 1;
        }
    }

    return 0;   // 숫자 등 그 외의 문자
}

// 길이가 정확히 8이고, 8글자 모두 유효한 음인지 검사한다.
int isValidInput(char scale[])  //예외처리 함수 (길이판별)
{
    int i;
    int length;

    length = getLength(scale);
    if (length != NOTE_COUNT)
    {
        return 0;
    }

    for (i = 0; i < NOTE_COUNT; i++)
    {
        if (!isValidNote(scale[i]))
        {
            return 0;
        }
    }

    return 1;
}

// 입력한 음을 오름차순 정답, 내림차순 정답과 한 글자씩 비교해서 결과를 반환한다.
int checkScale(char scale[])
{
    char ascending[9] = "cdefgabC";    // 오름차순 정답
    char descending[9] = "Cbagfedc";   // 내림차순 정답
    int isAscending = 1;   // 아직 오름차순과 같음을 나타내는 표시
    int isDescending = 1;  // 아직 내림차순과 같음을 나타내는 표시
    int i;

    for (i = 0; i < NOTE_COUNT; i++)   // 같은 위치끼리 하나씩 비교
    {
        if (scale[i] != ascending[i])
        {
            isAscending = 0;
        }
        if (scale[i] != descending[i])
        {
            isDescending = 0;
        }
    }

    if (isAscending == 1)
    {
        return 1;
    }
    else if (isDescending == 1)
    {
        return 2;
    }

    return 0;   // 두 정답에 모두 해당하지 않으면 섞인 순서
}