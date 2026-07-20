#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

int main(void)
{
    char input[1000];
    printf("입력: ");
    scanf("%s", input);

    // 동적 스택 준비
    int capacity = 10;
    int top = 0; // 현재 스택에 쌓인 태그 개수
    char** stack = (char**)malloc(sizeof(char*) * (size_t)capacity);
    //예외처리(말록에러)
    if (stack == NULL) {
        printf("malloc error\n");
        return 1;
    }

    int i = 0;
    int error = 0;

    while (input[i] != '\0' && error == 0)
    {
        if (input[i] == '<')
        {
            if (input[i + 1] == '/')
            {
                // 닫는 태그 처리
                i = i + 2; // "</" 건너뜀
                char tagname[50];
                int len = 0;
                while (input[i] != '>')
                {
                    tagname[len] = input[i];
                    len++;
                    i++;
                }
                tagname[len] = '\0';
                i++; // '>' 건너뜀

                if (top == 0)
                {
                    printf("오류: 잘못된 태그 구조입니다.\n");
                    error = 1;
                    break;
                }

                // 스택 맨 위 태그와 이름이 같은지 직접 비교
                int same = 1;
                int j = 0;
                while (stack[top - 1][j] != '\0' || tagname[j] != '\0')
                {
                    if (stack[top - 1][j] != tagname[j])
                    {
                        same = 0;
                        break;
                    }
                    j++;
                }

                if (same == 0)
                {
                    printf("오류: 잘못된 태그 구조입니다.\n");
                    error = 1;
                    break;
                }

                // 자기 자신 깊이(top-1)만큼 들여쓰기 후 출력
                for (int k = 0; k < top - 1; k++) printf("    ");
                printf("</%s>\n", tagname);

                free(stack[top - 1]);
                top--;
            }
            else
            {
                // 여는 태그 처리
                i++; // '<' 건너뜀
                char tagname[50];
                int len = 0;
                while (input[i] != '>')
                {
                    tagname[len] = input[i];
                    len++;
                    i++;
                }
                tagname[len] = '\0';
                i++; // '>' 건너뜀

                // 현재 깊이(top)만큼 들여쓰기 후 출력
                for (int k = 0; k < top; k++) printf("    ");
                printf("<%s>\n", tagname);

                // 스택 공간 부족하면 realloc으로 확장
                if (top == capacity)
                {
                    capacity = capacity * 2;
                    stack = (char**)realloc(stack, sizeof(char*) * (size_t)capacity);
                    if (stack == NULL)
                    {
                        printf("malloc error\n");
                        return 1;
                    }
                }

                stack[top] = (char*)malloc(sizeof(char) * (size_t)(len + 1));
                if (stack[top] == NULL)
                {
                    printf("malloc error\n");
                    return 1;
                }
                for (int k = 0; k <= len; k++) stack[top][k] = tagname[k];
                top++;
            }
        }
        else
        {
            // 태그가 아닌 일반 텍스트
            char text[200];
            int len = 0;
            while (input[i] != '\0' && input[i] != '<')
            {
                text[len] = input[i];
                len++;
                i++;
            }
            text[len] = '\0';

            for (int k = 0; k < top; k++) printf("    ");
            printf("%s\n", text);
        }
    }

    // 다 읽었는데 아직 닫히지 않은 태그가 남아있으면 오류
    if (error == 0 && top != 0)
    {
        printf("오류: 잘못된 태그 구조입니다. (닫히지 않은 태그 존재)\n");
        error = 1;
    }

    // 메모리 해제
    for (int k = 0; k < top; k++)
    {
        free(stack[k]);
    }
    free(stack);

    return 0;
}