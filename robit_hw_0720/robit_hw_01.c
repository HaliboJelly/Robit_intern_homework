#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

int main(void)
{
    int array[5][5] = {0};   // 미리 0으로 초기화 0 0 0 0 0
    int count = 1;           //                . . . . . 
                            //                 0 0 0 0 0
    for (int i = 0; i < 5; i++)
    {   
        int diff = i-2;             //diff는 절댓값
        if (diff < 0) diff = -diff; //ex) diff -2 -> 2

        int width = 1 + 2*diff;     //각 행별로 숫자가 들어갈 칸의 개수 구하기
        int start = (5 - width) / 2;
        int end   = start + width - 1;

        for (int j = start; j <= end; j++)
        {
            array[i][j] = count++;  //개수마다 숫자 넣기
        }
    }

    for (int i = 0; i < 5; i++)     //출력
    {
        for (int j = 0; j < 5; j++)
            printf("%2d ", array[i][j]);
        printf("\n");
    }

    return 0;
}
