#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int capacity = 1;    //동적할당할 때 쓰는 배열의 크기
    int len = 0;          //입력받은 문자열의 길이
    char *str = (char*)malloc(sizeof(char) * (size_t)capacity);
    char ch;

    int alpa[128] = { 0, };   //아스키 코드 33~126까지가 문자라서 128개로 만듦 /최다 등장 문자를 알아내기 위해 선언함

    //입력받으면서 실시간으로 배열의 크기를 늘려서 메모리 최소화하기(과제 3에서 했던 내용을 이용해봄)
    while (scanf("%c", &ch) == 1) {
        if (ch == '\n') break;     //엔터 입력시 입력 중단

        //공간 부족한지 체크
        if (len == capacity) {
            capacity += 1;
            str = (char*)realloc(str, (size_t)capacity * sizeof(char));
        }

        //글자 저장 후 등장 횟수도 같이 카운트
        *(str + len) = ch;
        *(alpa + ch) += 1;   //문자가 등장할 때 문자에 해당하는 인덱스에 있는 alpa 값을 1씩 증가시킴
        len++;
    }
    str[len] = '\0';   //문자열 끝 표시

    //거꾸로 출력하기| 원리: 마지막 인덱스부터 차례대로 출력
    for (int i = len - 1; i >= 0; i--) {
        printf("%c", *(str + i));
    }
    printf("\n");

    //최다 등장 횟수 찾기 //아스키 문자 !(33) 부터 ~(126) 까지 
    int max = 0;
    for (int i = '!'; i <= '~'; i++) {
        if (*(alpa + i) > max) {
            max = *(alpa + i);
        }
    }

    //최다 등장한 문자 출력 (최다 문자가 여러개면 전부 출력)
    for (int i = '!'; i <= '~'; i++) {  //아스키 문자 !(33) 부터 ~(126) 까지 
        if (*(alpa + i) == max) {
            printf("%c", i);
        }
    }

    free(str);  //해제
    return 0;
}