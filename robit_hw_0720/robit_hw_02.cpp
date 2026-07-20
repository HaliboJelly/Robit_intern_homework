#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

int main(void)
{
    int N1,N2;
    printf("N1 ");
    scanf("%d",&N1);
    printf("N2 ");
    scanf("%d",&N2);
    
    //*예외처리
    if (N1 <= 0 || N2 <= 0) 
    {
    printf("잘못된 입력입니다. N1, N2는 1 이상이어야 합니다.\n");
    return 1;   // 여기서 종료
    }

    int row = N1; // 행 크기
    int col = N2; // 열 크기

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
        // 이미 할당된 이전 행들 먼저 해제하고 종료
        for (int k = 0; k < i; k++) {
            free(arr[k]);
        }
        free(arr);
        return 1;
        }
    }

    // 값 할당 및 출력 테스트
    int count = 1;
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            arr[i][j] = count;
            count++;
        }
    }
    printf("----------------\n");
    printf("배열A\n");
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            printf("%2d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("----------------\n");
    printf("배열B\n");
    for(int i = 0; i < col; i++){
        for(int j = 0; j < row; j++){
            printf("%2d ", arr[j][i]);
        }
        printf("\n");
    }

    // 메모리 해제 (역순으로 해제)
    // 각 행의 열 메모리 해제
    for (int i = 0; i < row; i++) {
        free(arr[i]);
    }
    //  행 포인터 배열 메모리 해제
    free(arr);

    return 0;
}