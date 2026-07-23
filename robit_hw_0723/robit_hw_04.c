#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

// 노드 구조체 (스택과 큐에서 공통으로 사용)
typedef struct _Node {
    char data;              // 저장할 문자 값
    struct _Node* next;     // 다음 노드를 가리키는 포인터
}Node;

// 스택 구조체
typedef struct _Stack {
    Node* top;   //스택의 최상단 노드 포인터
    int size;    //현재 스택에 저장된 원소의 개수
}Stack;

// 큐 구조체
typedef struct _Queue {
    Node* front;  //큐의 앞부분 (Dequeue할 위치)
    Node* rear;   //큐의 뒷부분 (Enqueue할 위치)
    int size;     //현재 큐에 저장된 원소의 개수
}Queue;

//전역 스택, 큐(문제에서 준 코드 스타일을 따라 전역으로 선언)
Stack stack;
Queue queue;

//함수 선언
void push(char alpa);          // 스택에 문자 alpa 추가
void pop(void);                 // 스택의 최상단 노드 제거 (top을 다음 노드로 이동)
char top(int* success);        // 스택의 top 값을 반환, 비어있으면 success를 0으로 설정

void enqueue(char alpa);       // 큐에 문자 alpa 추가
void dequeue(void);             // 큐의 front 노드 제거 (front를 다음 노드로 이동)
char front(int* success);      // 큐의 front 값을 반환, 비어있으면 success를 0으로 설정

Node* create_stack_node(char data);  // 스택용 새 노드 생성 함수
Node* create_queue_node(char data);  // 큐용 새 노드 생성 함수

int main(void) {
    char alpa = 0;
    char q, s;
    int i, size, ok;

    printf("입력: ");

    //입력받기: 한 글자씩 받아서 스택과 큐에 동시에 저장
    while (1) {
        scanf("%c", &alpa);

        if (alpa == '\n') {   //엔터키 입력 시 루프 탈출
            break;
        }

        if (alpa == ' ') {    //공백은 무시(회문은 공백을 제외한 문자열이 대칭인지를 판단하기 때문)
            continue;
        }

        //스택에 push: 최신 문자가 위에 쌓인다(역순 저장)
        push(alpa);

        //큐에 enqueue: 먼저 들어온 문자가 front에 있다(정순 저장)
        enqueue(alpa);
    }

    size = queue.size;   //스택과 큐에 저장된 문자 개수는 동일하므로 큐 크기를 기준으로 반복

    //회문 판별 로직: 큐(정순)의 front와 스택(역순)의 top을 하나씩 비교
    for (i = 0; i < size; i++) {
        s = top(&ok);      //스택의 top 값(문자열의 뒤에서부터 순서대로 나옴)
        if (!ok) {
            break;          //스택이 비어있으면 더 이상 비교할 필요 없음
        }

        q = front(&ok);     //큐의 front 값(문자열의 앞에서부터 순서대로 나옴)
        if (!ok) {
            break;          //큐가 비어있으면 더 이상 비교할 필요 없음
        }

        if (q != s) {
            printf("회문x\n");
            return 0;
        }

        //비교가 끝난 두 값은 각각 pop, dequeue로 제거하고 다음 값 비교 준비
        pop();
        dequeue();
    }

    printf("회문o\n");
    return 0;
}

//create_stack_node 함수
//스택에 넣을 새로운 노드를 생성하는 함수
Node* create_stack_node(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));  //새로운 노드에 메모리 할당
    newNode->data = data;                          //문자 저장
    newNode->next = NULL;                          //다음 노드가 없음
    return newNode;
}

//create_queue_node 함수
//큐에 넣을 새로운 노드를 생성하는 함수
Node* create_queue_node(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));  //새로운 노드에 메모리 할당
    newNode->data = data;                          //문자 저장
    newNode->next = NULL;                          //다음 노드가 없음
    return newNode;
}

//push 함수
//스택의 최상단에 새로운 문자를 추가하는 함수
void push(char alpa) {
    Node* newNode = create_stack_node(alpa);
    newNode->next = stack.top;   //새 노드가 기존 top을 가리키게 연결
    stack.top = newNode;         //top을 새로운 노드로 재설정
    stack.size++;
    return;
}

//enqueue 함수
//큐의 rear에 새로운 문자를 추가하는 함수
void enqueue(char alpa) {
    Node* newNode = create_queue_node(alpa);

    if (queue.rear == NULL) {    //큐가 비어있는 경우(첫 번째 노드 추가)
        queue.front = newNode;   //이 노드가 front가 됨
        queue.rear = newNode;    //이 노드가 rear가 됨
    }
    else {
        queue.rear->next = newNode;  //기존 rear의 다음에 연결
        queue.rear = newNode;        //새로운 노드가 rear가 됨
    }
    queue.size++;
    return;
}

//pop 함수
//스택의 최상단 노드를 제거하는 함수
void pop(void) {
    if (stack.top == NULL) {     //스택이 비어있으면 아무 동작 없이 종료
        return;
    }

    Node* cur = stack.top;
    Node* nextNode = cur->next;  //top을 이전 노드로 바꾸기 위해 next 값을 미리 저장
                                  //free()하면 top의 데이터가 없어지기 때문
    free(cur);
    stack.top = nextNode;        //top이 기존 top의 다음 노드가 됨
    stack.size--;
    return;
}

//dequeue 함수
//큐의 front 노드를 제거하는 함수
void dequeue(void) {
    if (queue.front == NULL) {   //큐가 비어있으면 아무 동작 없이 종료
        return;
    }

    Node* cur = queue.front;
    Node* nextNode = cur->next;  //front를 이전 노드로 바꾸기 위해 next 값을 미리 저장
                                  //free하면 front의 데이터가 없어지기 때문
    free(cur);
    queue.front = nextNode;      //front가 기존 front의 다음 노드가 됨

    if (queue.front == NULL) {   //마지막 노드를 제거한 경우 rear도 함께 NULL로 초기화
        queue.rear = NULL;
    }
    queue.size--;
    return;
}

//top 함수
//스택의 top 값을 반환하는 함수
//success 포인터를 통해 스택이 비어있는지 아닌지 결과를 확인할 수 있게 함
//(문자 데이터에는 -1 같은 특정 값이 없어도 되므로, 별도의 success 플래그로 비어있음을 판단)
char top(int* success) {
    if (stack.top == NULL) {
        *success = 0;
        return -1;
    }
    *success = 1;
    return stack.top->data;   //top 값 반환
}

//front 함수
//큐의 front 값을 반환하는 함수
//success 포인터를 통해 큐가 비어있는지 아닌지 결과를 확인할 수 있게 함
char front(int* success) {
    if (queue.front == NULL) {
        *success = 0;
        return -1;
    }
    *success = 1;
    return queue.front->data;  //front 값 반환
}