#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

int main(void)
{
    int N1, N2;
    printf("N1 N2: ");

    if (scanf("%d %d", &N1, &N2) != 2) {            //scanf에 대한 예외처리
    printf("오류: 정수가 아닌 값이 입력되었습니다.\n");
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return 1;
    }

    if (N1 <= 0 || N2 <= 0) {                                //scanf에 대한 예외처리
    printf("잘못된 입력입니다. N1, N2는 1 이상이어야 합니다.\n");
    return 1;
    }

    if (N1 % 2 == 0 || N2 % 2 == 0) {                        //scanf에 대한 예외처리(홀수 검증) 
    printf("잘못된 입력입니다. N1, N2는 홀수여야 합니다.\n");
    return 1;
    }


    int row = N1, col = N2;

    int **arr = (int **)malloc(sizeof(int *)*(size_t)row);
    //예외처리(말록에러)
    if (arr == NULL) {
    printf("malloc error\n");
    return 1;
    }
    for (int i= 0;i<row;i++) {
        arr[i] = (int *)malloc(sizeof(int)*(size_t)col);
        //예외처리(말록에러)
        if (arr[i] == NULL) {
        printf("malloc error\n");
        for (int k = 0; k < i; k++) free(arr[k]);
        free(arr);
        return 1;
        }
    }

    int cr=(row-1)/2; // 중심 행
    int cc=(col-1)/2; // 중심 열

    int count=1;
    arr[cr][cc]=count++;

    int maxR=row+col; // 충분히 큰 반지름 상한

    for (int r=1;r<=maxR;r++) {
        // 왼쪽 -> 아래
        for (int t=1;t<=r;t++) {
            int i=cr+t,j=cc+(t-r);
            if (i>=0 && i<row && j>=0 && j<col) 
            {
                arr[i][j]=count++;
            }
        }
        // 아래 -> 오른쪽
        for (int t=1;t<=r;t++) {
            int i=cr+(r-t), j=cc+t;
            if (i>=0 && i<row && j>=0 && j<col)
            {
                arr[i][j]=count++;
            }
        }
        // 오른쪽 -> 위
        for (int t=1;t<=r;t++) {
            int i=cr-t,j=cc+(r-t);
            if (i>=0 && i<row && j>=0 && j<col)
            {
                arr[i][j]=count++;
            }
        }
        // 위 -> 왼쪽
        for (int t=1;t<=r;t++) {
            int i=cr+(t-r),j=cc-t;
            if (i>=0 && i<row && j>=0 && j<col)
            {
            arr[i][j]=count++;
            }
        }

        if (count>row*col)
        {
            break; // 이미 다 채웠으면 종료
        }
    }

    //출력
    for (int i=0;i<row;i++) {
        for (int j=0;j<col;j++) {
            printf("%3d ",arr[i][j]);
        }
        printf("\n");
    }
    //메모리 해제
    for (int i=0;i<row;i++) 
    {
        free(arr[i]);
    }

    free(arr);

    return 0;
}