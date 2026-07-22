#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double dist(int x1, int y1, int x2, int y2)     //두 좌표의 거리를 구하는 함수
{
    int xdiff=0,ydiff=0;

    xdiff = x1 - x2;        //x값 차
    ydiff = y1 - y2;        //y값 차

    return sqrt((double)(xdiff * xdiff + ydiff * ydiff));   //거리값 반환
}

struct point    //구조체
{
    int x;
    int y;
    double sum;     //각각의 거리합
};

int main(void)
{
    int n;
    scanf("%d", &n);    //n개 받기

    //만약 n이 1개 보다 적다면 오류가 나므로 예외처리
    if (n <= 0)
    {
    printf("점의 개수는 1개 이상이어야 합니다.\n");
    return 0;
    }

    //구조체 동적할당
    struct point *p = (struct point*)malloc(sizeof(struct point)*(size_t)n);

    if(p==NULL) //진짜만약 메모리 부족
    {
        printf("메모리 할당 실패\n");
        return 0;
    }

    //좌표받기 및 구조체에 저장
    int i =0;
    for(i =0; i<n;i++)
    {
        scanf("%d %d", &p[i].x,&p[i].y);
        p[i].sum = 0.0;
    }

    //각 좌표마다 거리의 총합을 sum구조체에 저장
    int j=0;
    for(j=0;j<n;j++)                  /*과제 예시 로직: j=0과 i=0,1,2,3,4  ->(0,0)부터 (0,0),(1,1),(2,3),(2,1),(7,7)의 거리합*/
    {                                   //              j=1과 i=0,1,2,3,4      ...
        for(i=0;i<n;i++)              //                  ...
        {   
            p[j].sum = p[j].sum + dist(p[j].x,p[j].y,p[i].x,p[i].y);
        }
    }

    //최대 거리 합 판별
    double max = 0.0;
    int maxI = 0;
    for(i=0;i<n;i++){   
        if(max<p[i].sum){   //만약 값이 max보다 크다면 
            max = p[i].sum; //max가 그 값이 됨. -> for문으로 n번 만큼 반복
            maxI = i;   //최대거리 합의 구조체 i값 반환
        }
    }

    // 반올림
    double result;
    result = round(max * 100) / 100.0;

    //출력
    printf("가장 거리가 먼 좌표는 (%d,%d)이며, 다른 좌표의 거리 총합은 약 %.1f입니다",p[maxI].x,p[maxI].y,result);
    
    //동적할당 해제
    free(p); 

    return 0;
}
