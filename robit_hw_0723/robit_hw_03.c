#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

//$$$$$$용어 혼동 주의$$$$$$

//  top == front
//  tail == rear

//$$$$$$용어 혼동 주의$$$$$$

typedef struct _Node {
    int data;
    struct _Node* next;
}Node;

typedef struct _queue {
    Node* top;   //front
    Node* tail;  //rear
    int size;
}queue;

void init_queue(queue* q) {
    q->top= NULL;
    q->tail= NULL;
    q->size= 0;
}

//큐가 비었는지 확인
int isEmpty(queue* q) {
    return (q->size== 0);
}

//큐의 테일에 새 노드 삽입
void enqueue(queue* q, int value) {
    Node* newnode= (Node*)malloc(sizeof(Node));
    newnode->data= value;
    newnode->next= NULL;

    if (isEmpty(q)) {
        //큐가 비어있으면 탑, 테일 모두 새 노드 삽입
        q->top= newnode;
        q->tail= newnode;
    }
    else {
        //기존 테일 뒤에 새 노드 연결 후 태일 갱신
        q->tail->next= newnode;
        q->tail= newnode;
    }
    q->size++;
}

//큐의 탑에 있는 노드를 삭제하고 값 반환
int dequeue(queue* q) {
    if (isEmpty(q)) {
        printf("큐가 빔\n");
        return -1; //비어있을 때의 예외 처리용 반환값
    }

    Node* temp= q->top;
    int value= temp->data;

    q->top= q->top->next;
    if (q->top== NULL) {
        //마지막 노드를 삭제한 경우 태일도 널 값으로
        q->tail= NULL;
    }

    free(temp);
    q->size--;//사이즈 줄이기

    printf("Dequeue된 값: %d\n", value);
    return value;
}

//큐 크기 반환
int size(queue* q) {
    return q->size;
}

//프론트 값 반환
int front(queue* q) {
    if (isEmpty(q)) {
        printf("큐가 빔\n");
        return -1;
    }
    return q->top->data;
}

//테일 값 반환
int rear(queue* q) {
    if (isEmpty(q)) {
        printf("큐가 빔\n");
        return -1;
    }
    return q->tail->data;
}

//큐 내 모든 값 출력
void printQueue(queue* q) {
    if (isEmpty(q)) {
        printf("큐가 빔\n");
        return;
    }

    Node* cur= q->top;
    printf("Queue: ");
    while (cur!= NULL) {
        printf("%d ", cur->data);
        cur= cur->next;
    }
    printf("\n");
}


int main(void) {
    queue q;
    init_queue(&q);
    int command;
    int a = 0;

    printf("모드선택: 0.exit 1.enqueue 2.dequeue 3.size 4.front 5.rear 6.isEmpty 7.printQueue\n");
    printf("ex) mode [정수]\n 1 5 => 모드: enqueue, 정수: 5\n 2 => 모드: dequeue\n\n");

    while (1) {
        printf("명령 입력: ");
        scanf("%d", &command);

        if (command == 0) {
            printf("exit");
            break;
        }
        else if (command == 1) {
            scanf("%d", &a);
            enqueue(&q, a);
        }
        else if (command == 2) {
            dequeue(&q);
        }
        else if (command == 3) {
            printf("q size: %d\n", size(&q));
        }
        else if (command == 4) {
            printf("at front value: %d\n", front(&q));
        }
        else if (command == 5) {
            printf("at rear value: %d\n", rear(&q));
        }
        else if (command == 6) {
            if (isEmpty(&q)) {
                printf("true\n");
            }
            else {
                printf("false\n");
            }
        }
        else if (command == 7) {
            printQueue(&q);
        }
    }

    return 0;
}