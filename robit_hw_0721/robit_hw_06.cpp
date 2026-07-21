#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

//숫자 무늬를 출력하는 함수
void number_print(int *numbers, int len)
{
    int count = 0;   //배열에서 몇 번째 숫자를 찍을 차례인지

    for (int i = 0; i < 3; i++) {      //3열
        for (int j = 0; j < 4; j++) {  //4행

            printf("%d", numbers[count]);

            count++;

            if (count >= len) {   //지금까지 입력받은 개수(len)에 도달하면 다시 0번째로 되돌아감
                count = 0;        //줄이 바뀌어도 count를 초기화하지 않아서 len과 4가 안 맞아떨어지면 다음 줄부터 시작 위치가 밀리며 회전 무늬가 생김
            }
        }
        printf("\n");
    }
}

int main(void)
{
    int capacity = 1;   //numbers 배열 크기
    int len = 0;         //지금까지 입력받은 숫자의 개수

    int *numbers = (int*)malloc(sizeof(int) * (size_t)capacity);

    while (1) {   //입력 오류가 나기 전까지 계속 반복

        //배열 크기가 부족하면 딱 1칸만 늘려서 메모리 최소화하기(아까것들 계속 이용)
        if (len == capacity) {
            capacity += 1;
            numbers = (int*)realloc(numbers, sizeof(int) * (size_t)capacity);
        }

        if (len == 0) {
            printf("input: ");
        } else {
            printf("next input: ");
        }

        int num;
        if (scanf("%d", &num) != 1) {   //입력이 숫자가 아니면 종료
            printf("ERROR");
            break;
        }

        numbers[len++]=num;

        number_print(numbers, len);   //지금까지 입력받은 숫자로 도형을 다시 그려서 출력
    }

    free(numbers);   //해제하기
    return 0;
}