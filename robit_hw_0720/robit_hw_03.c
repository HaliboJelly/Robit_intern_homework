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
    //예외처리
    if (N1 <= 0 || N2 <= 0) {
    printf("잘못된 입력입니다. N1, N2는 1 이상이어야 합니다.\n");
    return 1;
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
        for (int k = 0; k < i; k++) {
            free(arr[k]);
        }
        free(arr);
        return 1;
        }
    }

    int top = 0, bottom = row - 1;
    int left = 0, right = col - 1;
    int count = 1;

    while (top <= bottom && left <= right) {
        // 위쪽 행: 왼쪽 -> 오른쪽
        for (int j = left; j <= right; j++) {
            arr[top][j] = count++;
        }
        top++;

        // 오른쪽 열: 위 -> 아래
        for (int i = top; i <= bottom; i++) {
            arr[i][right] = count++;
        }
        right--;

        // 아래쪽 행: 오른쪽 -> 왼쪽 (남은 행이 있을 때만)
        if (top <= bottom) {
            for (int j = right; j >= left; j--) {
                arr[bottom][j] = count++;
            }
            bottom--;
        }

        // 왼쪽 열: 아래 -> 위 (남은 열이 있을 때만)
        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                arr[i][left] = count++;
            }
            left++;
        }
    }

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
