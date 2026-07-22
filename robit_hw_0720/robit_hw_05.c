#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

int main(void)
{
    int N;
    printf("N: ");


    if (scanf("%d", &N) != 1) {                     //scanf에 대한 예외처리
    printf("오류: 정수가 아닌 값이 입력되었습니다.\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return 1;
    }

    if (N <= 0) {                                   //scanf에 대한 예외처리
    printf("잘못된 입력입니다. N은 1 이상이어야 합니다.\n");
    return 1;
    }

    int row = N; // 행 크기
    int col = N; // 열 크기

    // 행의 포인터 배열 동적 할당
    int **arr = (int **)malloc(sizeof(int *) * (size_t)row);
    //예외처리 (말록에러)
    if (arr == NULL) {
    printf("malloc error\n");
    return 1;
    }

    // 각 행마다 열 메모리 동적 할당
    for (int i = 0; i < row; i++) {
        arr[i] = (int *)malloc(sizeof(int) * (size_t)col);
        //예외처리 (말록에러)
        if (arr[i] == NULL) {
        printf("malloc error\n");
        for (int k = 0; k < i; k++) free(arr[k]);
        free(arr);
        return 1;
        }
    }

    //로직: 대각선 마다 고유 번호를 매긴다.
    //매기는 방법: 각 칸들을 좌표로 나타낼 시 같은 대각선에서는 arr[a][b]에서 a+b의 값들이 동일
    int count = 1;

    // d = i + j: 대각선 번호(0~row+col-2)
    for (int d=0;d<row+col-1;d++) {
        // 이 대각선에서 i가 가질 수 있는 최소/최대값 계산
        int i_start=(d-(col-1)>0)?(d-(col-1)):0;
        int i_end=(d<row-1)?d:(row-1);

        for (int i=i_start;i<=i_end;i++) {
            int j=d-i;
            arr[i][j]= count++;
        }
    }


    //출력
    printf("----------------\n");
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            printf("%2d ", arr[i][j]);
        }
        printf("\n");
    }
    

    // 메모리 해제
    for (int i = 0; i < row; i++) {
        free(arr[i]);
    }
    
    free(arr);

    return 0;
}
