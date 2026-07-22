#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void drawShape(int size, int shapeType);   

int main(void)
{
    int size;
    int shapeType;

    printf("크기와 모양 번호를 입력하세요. ");
    if (scanf("%d %d", &size, &shapeType) != 2)   // 두 값을 제대로 못 받으면 예외처리
    {
        printf("입력값을 확인해주세요.\n");
        return 0;
    }

    if (size <= 0)   // 크기는 1 이상이어야 의미가 있음
    {
        printf("크기는 1보다 커야 합니다.\n");
    }
    else if (shapeType < 1 || shapeType > 4)   // 모양 번호는 1~4만 허용
    {
        printf("모양 번호는 1~4 사이여야 합니다.\n");
    }
    else
    {
        drawShape(size, shapeType);
    }

    return 0;
}

void drawShape(int size, int shapeType)
{
    int line;
    int k;
    int center;
    int starCount;
    int blankCount;

    center = (size + 1) / 2;   // 가운데에 해당하는 줄 번호

    for (line = 1; line <= size; line++)
    {
        if (shapeType == 1 || shapeType == 2)   // 1, 2번은 별 개수 변화가 동일
        {
            if (line <= center)
            {
                starCount = line;   // 가운데까지는 한 줄씩 별이 늘어남
            }
            else
            {
                starCount = size - line + 1;   // 가운데 지나면 다시 줄어듦
            }

            if (shapeType == 1)
            {
                blankCount = 0;   // 1번은 왼쪽 정렬이라 공백이 없음
            }
            else
            {
                blankCount = center - starCount;   // 2번은 오른쪽으로 밀어줌
            }
        }
        else if (shapeType == 3)
        {
            if (line <= center)
            {
                blankCount = line - 1;   // 가운데로 갈수록 공백이 늘어남
            }
            else
            {
                blankCount = size - line;   // 가운데 지나면 공백이 줄어듦
            }
            starCount = size - blankCount * 2;   // 공백 하나당 별은 두 개씩 감소
        }
        else   // shapeType == 4
        {
            // 위쪽 절반: 오른쪽 끝은 고정된 채 공백이 늘고 별이 줄어든다 (종류2와 유사)
            // 가운데를 지난 뒤: 공백은 가운데 줄 값으로 고정되고 별만 늘어난다 (번개 모양)
            if (line <= center)
            {
                blankCount = line - 1;
                starCount = center - line + 1;
            }
            else
            {
                blankCount = center - 1;         // 가운데 줄의 공백 값을 그대로 유지
                starCount = line - center + 1;   // 별 개수만 계속 증가
            }
        }

        for (k = 1; k <= blankCount; k++)
        {
            printf(" ");   // 공백부터 채우고 
        }
        for (k = 1; k <= starCount; k++)
        {
            printf("*");   // 그 다음 별을 채운다
        }
        printf("\n");
    }
}
