#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


void print(int *row, int *col, int **pArr)
{
    for (int i = 0; i < *row; i++) {
        for (int j = 0; j < *col; j++) {
            printf("%3d ", pArr[i][j]);
        }
        printf("\n");
    }
}

void arr_ij(int *sizeRow, int *sizeCol, int **pArr)
{
    int row = *sizeRow;
    int col = *sizeCol;
    int num = 1;
    int top = 0, bottom = row - 1, left = 0, right = col - 1;

    while (num <= row * col) {
        //왼쪽->오른쪽
        for (int j = left; j <= right; j++)
            pArr[top][j] = num++;
        top++;

        //위->아래
        for (int i = top; i <= bottom; i++)
            pArr[i][right] = num++;
        right--;

        //오른쪽->왼쪽
        for (int j = right; j >= left; j--)
            pArr[bottom][j] = num++;
        bottom--;

        //아래->위
        for (int i = bottom; i >= top; i--)
            pArr[i][left] = num++;
        left++;
    }
}



int main(void)
{
    int **arr = NULL;
    int  row,col,sizeRow,sizeCol;

    printf("열의 수를 입력하세요:");
    scanf("%d",&sizeCol);
    printf("행의 수를 입력하세요:");
    scanf("%d",&sizeRow);

    arr = (int**)malloc(sizeof(int*) * (size_t)sizeRow);   //행 개수만큼 포인터 배열 만들기
    for (int i = 0; i < sizeRow; i++) {
    arr[i] = (int*)malloc(sizeof(int) * (size_t)sizeCol);   //각 행마다 실제 칸 만들기
    }

    row = sizeRow;
    col = sizeCol;

    arr_ij(&sizeRow,&sizeCol,arr);

    print(&row,&col,arr);

    for(int i=0; i<row; i++){
        free(arr[i]);
    }
    free(arr);

    return 0;
}