#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct  _Node {     //node 구조
    int data;
    struct _Node * next;
}Node;

typedef struct _Stack {     //스택
    Node *top;
    int size;
}Stack;

void init_stack(Stack *s) {     //스택 초기화
    s->top = NULL;
    s->size = 0;
    
}

void push(Stack *s,int value){      //푸쉬
    Node *newnode= (Node*)malloc(sizeof(Node));     //동적할당 필요
    newnode->data = value;      //뉴노드 데이타로 밸류 저장
    newnode->next = s->top;     //뉴노드 넥스트로 스택의 탑 저장
    s->top = newnode;           //스택 탑의 뉴노드 저장
    s->size++;                  //스택 사이즈 늘리기
}

void pop(Stack *s){             //팦
    if(s->size ==0){            //스택의 사이즈로 비어있는지 판단
        printf("stack비어있음");
        return;
    }

    Node * temp = s->top;       //탬프(일시적 노드)에 스택 탑 저장
    int value = temp->data;
    s->top = s->top->next;
    free(temp);
    s->size--;
    printf("pop된 값: %d\n", value);
}

void size(Stack *s){        //사이즈
    printf("stack크기: %d\n",s->size);
}

void top_print(Stack *s){       //탑값 프린트
    printf("탑에 위치한 값: %d\n",s->top->data);
}

int isEmpty(Stack *s){      //비어있는지에 따라 반환
    if(s->size==0){
        return 1;       //비어있으면 1
    }
    else{
        return -1;      //아니면 -1
    }
}

void printStack(Stack *s){
    if (s->size == 0) {
        printf("stack이 빔\n");
        return;
    }

    Node *tp = s->top;           // top부터 시작하도록 초기화
    printf("[ ");
    while (tp != NULL) {         // NULL 만날 때까지 반복
        printf("%d ", tp->data);
        tp = tp->next;           // 다음 노드로 이동
    }
    printf("]\n");
}

int main(void){
    Stack s;
    init_stack(&s);
    int command;
    int a =0;

    printf("모드선택: 0.exit 1.push 2.pop 3.size 4.top 5.isEmpty 6.printStack\n");
    printf("ex) mode [정수]\n 1 5 => 모드: push, 정수: 5\n 2 => 모드: pop\n\n");
    

    while (1) {
        printf("명령 입력;");
        scanf("%d",&command);

        if(command == 0){
            printf("exit");
            break;
        }
    
        else if(command==1){
            scanf("%d",&a);
            push(&s,a);
        }
        else if(command==2){
            pop(&s);
        }
        else if(command==3){
            size(&s);
        }
        else if(command==4){
            top_print(&s);
        }
        else if(command==5){
            if(isEmpty(&s)==1){
                printf("true\n");
            }
            else{
                printf("false\n");
            }
        }
        else if(command==6){
            printStack(&s);
        }
    }

    return 0;
}