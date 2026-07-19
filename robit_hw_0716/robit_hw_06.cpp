#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_SIZE 20   // 집합에 저장 가능한 원소는 1~20까지 최대 20개

int isSameCommand(char s1[], char s2[]);              // 두 문자열이 같은지 직접 비교
int findElement(int set[], int count, int x);         // 집합에서 x의 위치를 찾음 (없으면 -1)
void printSet(int set[], int count);                  // 현재 집합 출력
void printMenu(void);                                 // 사용 가능한 명령어 출력

int main(void)
{
    int set[MAX_SIZE];
    char command[10];
    int count = 0;   // 현재 집합에 들어있는 원소의 개수
    int x;
    int index;
    int i;

    printMenu();

    while (1)
    {
        printf("\ninput : ");

        if (scanf("%9s %d", command, &x) != 2)   // 명령어와 숫자를 함께 입력받음
        {
            break;   // 입력이 잘못되면 종료 (예외처리)
        }

        if (isSameCommand(command, "add"))
        {
            if (x >= 1 && x <= 20)   // 유효 범위인지 확인
            {
                index = findElement(set, count, x);

                if (index == -1)   // 아직 집합에 없는 경우에만 추가
                {
                    set[count] = x;
                    count++;
                }
            }
        }
        else if (isSameCommand(command, "remove"))
        {
            index = findElement(set, count, x);

            if (index != -1)   // 집합에 있을 때만 제거
            {
                for (i = index; i < count - 1; i++)
                {
                    set[i] = set[i + 1];   // 뒤의 원소들을 한 칸씩 앞으로 이동
                }
                count--;
            }
        }
        else if (isSameCommand(command, "check"))
        {
            index = findElement(set, count, x);

            if (index != -1)
            {
                printf("1\n");
            }
            else
            {
                printf("0\n");
            }
        }
        else if (isSameCommand(command, "toggle"))
        {
            if (x >= 1 && x <= 20)   // 유효 범위인지 확인
            {
                index = findElement(set, count, x);

                if (index != -1)   // 있으면 제거
                {
                    for (i = index; i < count - 1; i++)
                    {
                        set[i] = set[i + 1];
                    }
                    count--;
                }
                else   // 없으면 추가
                {
                    set[count] = x;
                    count++;
                }
            }
        }
        else if (isSameCommand(command, "all"))
        {
            count = MAX_SIZE;

            for (i = 0; i < MAX_SIZE; i++)
            {
                set[i] = i + 1;   // 1부터 20까지 채움
            }
        }
        else if (isSameCommand(command, "empty"))
        {
            count = 0;   // 집합을 공집합으로 초기화
        }
        else
        {
            printf("잘못된 명령어입니다.\n");
            continue;   // 집합 출력 없이 다시 입력받음
        }

        printSet(set, count);
    }

    return 0;
}

void printMenu(void)
{
    printf("연산을 선택하세요. (1 <= x <= 20)\n");
    printf("add x\n");
    printf("remove x\n");
    printf("check x\n");
    printf("toggle x\n");
    printf("all 0\n");
    printf("empty 0\n");
}

void printSet(int set[], int count)
{
    int i;

    printf("집합 : { ");

    for (i = 0; i < count; i++)
    {
        printf("%d, ", set[i]);
    }

    printf("}\n");
}

int findElement(int set[], int count, int x)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (set[i] == x)
        {
            return i;   // x가 저장된 위치 반환
        }
    }

    return -1;   // 찾지 못하면 -1 반환
}

// 두 문자열이 완전히 같으면 1, 다르면 0 반환
int isSameCommand(char s1[], char s2[])
{
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
        {
            return 0;
        }
        i++;
    }

    return (s1[i] == '\0' && s2[i] == '\0');   // 둘 다 동시에 끝나야 완전히 같은 문자열
}