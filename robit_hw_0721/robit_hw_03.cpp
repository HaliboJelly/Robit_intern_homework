#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

struct content
{
    char name[20];
    int price;
};

int string_compare(char s1[], char s2[]){   //strcmp를 대신하는 함수| 이름 비교에 쓰임(과제1에서 만든거)
    int i = 0;
    while (s1[i] != '\0' || s2[i] != '\0') {
        if (s1[i] > s2[i])
            return 1;
        else if (s1[i] < s2[i])
            return -1;
        else
            i++;
    }
    return 0;
}

int main(void)
{
    int n;
    scanf("%d", &n);

    if (n <= 0)     //n을 1보다 작게 입력하면 안되니까 예외처리
    {
        printf("물품의 개수는 1개 이상이어야 합니다.\n");
        return 0;
    }

    struct content *c = NULL; 
    int count = 0;  //몇 칸 만들었는지 카운트

    for (int i = 0; i < n; i++)
    {   
        //메모리 절감을 위해 realloc으로 필요할 때마다 한 칸씩 늘림
        struct content *temp = (struct content*)realloc(c, sizeof(struct content) * (count + 1));

        if (temp == NULL)   //진짜만약 메모리 부족 (과제2처럼)
        {
            printf("메모리 할당 실패\n");
            free(c);
            return 0;
        }

        c = temp;
        count++;

        scanf("%s %d", c[count - 1].name, &c[count - 1].price); //값 구조테에 저장
    }

    //마지막에 물품 이름 하나를 입력받기
    char query[20];
    scanf("%s", query);

    //같은 이름이면 금액 합산하고 같은 이름이 아니면 0
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (string_compare(c[i].name, query) == 0)
        {
            sum += c[i].price;
        }
    }

    printf("%d\n", sum);

    free(c);
    return 0;
}