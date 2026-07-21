#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define SIZE 5  //리스트 사이즈

int string_compare(char s1[], char s2[]){   //strcmp를 대신하는 함수[문자배열 비교 함수]
    int i =0;
    while (s1[i] != '\0'||s2[i] != '\0') {
        if (s1[i] > s2[i])      
            return 1;               //문자1>문자2: 1 
        else if (s1[i]<s2[i])
            return -1;              //문자1<문자2: -1 
        else
            i++;
    }
    return 0;                       //문자1=문자2: 0 
}

typedef struct _Student
{
    int cls;    //반
    double acv;  //성적
    char name[10];  //이름
}Student;

int main(void)
{
    Student list[SIZE];
    Student temp;
    int i =0,j=0;

    for(i=0;i<SIZE;i++)     //입력 값 받아오기(SIZE만큼)
    {
        scanf("%d %lf %9s",&list[i].cls,&list[i].acv,list[i].name);
    }

    //먼저 학년 순으로 줄을 세운다.
    for(int j = 0; j < SIZE - 1; j++){      // 몇 번 훑을지
        
        for(i = 1; i < SIZE; i++){     // 인접 비교
            
            if(list[i-1].cls > list[i].cls){    //i번쨰 리스트와 i-1비교

                temp = list[i-1];
                list[i-1] = list[i];
                list[i] = temp;
            }
        }
    }
    //그다음 성적순으로 세운다.
   for(int j = 0; j < SIZE - 1; j++){      // 몇 번 훑을지
        
        for(i = 1; i < SIZE; i++){     // 인접 비교
            
            if(list[i-1].cls == list[i].cls && list[i-1].acv > list[i].acv){     //i번쨰 리스트와 i-1비교(단, 학년 순은 바뀌면 안되므로 같은학년일때 조건 추가)

                temp = list[i-1];
                list[i-1] = list[i];
                list[i] = temp;
            }
        }
    }
    //그다음 이름순서로 세운다. 이름 비교시 string_compare함수 이용
    for(int j = 0; j < SIZE - 1; j++){      // 몇 번 훑을지
        
        for(i = 1; i < SIZE; i++){     // 인접 비교
            
            if(list[i-1].acv == list[i].acv && list[i-1].cls == list[i].cls && string_compare(list[i-1].name, list[i].name)>0){     //i번쨰 리스트와 i-1비교(단, 학년순과 성적순은 바뀌면 안되므로 같은 학년,성적 일 때 조건 추가)

                temp = list[i-1];
                list[i-1] = list[i];
                list[i] = temp;
            }
        }
    }   

    printf("------------------\n");
    for(i=0;i<SIZE;i++)     //입력 값 출력하기(SIZE만큼)
    {
        printf("%d %.1lf %s\n",list[i].cls,list[i].acv,list[i].name);
    }

    return 0;
}