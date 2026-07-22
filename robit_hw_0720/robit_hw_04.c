#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

int main(void)
{
    int n,max=0,min=0,sum=0;
    double avg=0.0;
    
    printf("몇 개의 원소를 할당하겠습니까? : ");
    scanf("%d",&n);
    //예외처리(n이 1보다 작고 다른 값들이 처리될떄)
    if (n <= 0) {
    printf("잘못된 입력입니다. 1 이상의 값을 입력하세요.\n");
    return 1;
    }

    int* arr = (int*)malloc(sizeof(int)*(size_t)n);//동적할당
    //예외처리 (말록에러)
    if (arr == NULL) {
    printf("malloc error\n");
    return 1;
    }
    int i =0;
    for(i=0;i<n;i++)
    {
        printf("정수형 데이터 입력:");
        if (scanf("%d", &arr[i]) != 1) {        //다른 값들이 처리될 때 예외처리
        printf("오류: 정수가 아닌 값이 입력되었습니다.\n");
        return 0;
        }

        if(i==0){                 // 첫 원소일 때만 초기화
        max = arr[i];
        min = arr[i];
        } 
        else {
        if(arr[i] > max) max = arr[i];  //max값 구하기
        if(arr[i] < min) min = arr[i];  //min값 구하기
        }
        //전체합 구하기
        sum = sum + arr[i];
        //평균 구하기
        avg = (double)sum / n;
    }

    printf("최대값: %d\n",max);
    printf("최소값: %d\n",min);
    printf("전체합: %d\n",sum);
    printf("평 균: %0.6f", avg);

    free(arr);
    return 0;
}
