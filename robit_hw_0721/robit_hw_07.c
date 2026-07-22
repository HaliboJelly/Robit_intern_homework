#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/* =========================================================

                            명령어  

 *   insert_first <data>              : 맨 앞에 노드 추가
 *   insert_back  <data>              : 맨 뒤에 노드 추가
 *   insert index <index> <data>      : index 위치에 노드 추가 (0부터 시작)
 *   insert data <targetData> <data>  : targetData 노드 뒤에 추가
 *
 *   delete_first                     : 맨 앞 노드 삭제
 *   delete_back                      : 맨 뒤 노드 삭제
 *   delete index <index>             : index 위치의 노드 삭제
 *   delete data <targetData>         : targetData를 가진 노드 삭제
 *
 *   get_entry index <index>          : index로 data 조회
 *   get_entry data <targetData>      : data로 index 조회
 *   get_length                       : 리스트 전체 길이 출력
 *   print_list                       : 리스트 전체 요소 출력
 *   reverse                          : 리스트를 역순으로 뒤집기
 *   exit                             : 프로그램 종료


 *  사용예시
 *   입력: insert_back 10
 *   출력: 10를 맨 뒤에 삽입했습니다
 
 * ========================================================= */


//노드 구조체: 데이터 + 다음 노드를 가리키는 포인터
typedef struct _Node
{
    int data;
    struct _Node* next;
} Node;

//연결리스트 구조체: head, tail, size를 함께 관리
typedef struct
{
    Node* head;
    Node* tail;
    int size;
} LinkedList;

LinkedList list;   //전역 리스트 하나만 사용

//문자열 비교 함수 (strcmp 대신 직접 구현|아까처럼)
int string_compare(const char s1[],const char s2[])
{
    int i = 0;
    while (s1[i] != '\0' || s2[i] != '\0') {
        if (s1[i] > s2[i]) return 1;
        else if (s1[i] < s2[i]) return -1;
        else i++;
    }
    return 0;
}

//새 노드 하나 생성
Node* create_node(int data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

//insert_first: 맨 처음에 노드 추가
void insert_first(int data)
{
    Node* newNode = create_node(data);
    newNode->next = list.head;   //새 노드가 기존 head를 가리킴
    list.head = newNode;         //head를 새 노드로 갱신

    if (list.tail == NULL) {     //리스트가 비어있던 경우
        list.tail = newNode;
    }

    list.size++;
    printf("%d를 맨 앞에 삽입했습니다\n", data);
}

//insert_back: 맨 끝에 노드 추가
void insert_back(int data)
{
    Node* newNode = create_node(data);

    if (list.head == NULL) {     //리스트가 비어있던 경우
        list.head = newNode;
        list.tail = newNode;
    }
    else {
        list.tail->next = newNode;   //마지막 노드 뒤에 연결
        list.tail = newNode;         //tail을 새 노드로 갱신
    }

    list.size++;
    printf("%d를 맨 뒤에 삽입했습니다\n", data);
}

//insert: 원하는 위치에 노드 추가 (index 또는 이전 data 값 기준)
//입력형식:
//  insert index <index> <data>          -> index번째 위치에 data를 삽입 (0부터 시작)
//  insert data <targetData> <newData>   -> targetData를 가진 노드 뒤에 newData 삽입
void insert(void)
{
    char mode[10];
    scanf("%s", mode);

    if (string_compare(mode, "index") == 0) {
        int index, data;
        scanf("%d %d", &index, &data);

        if (index < 0 || index > list.size) {
            printf("잘못된 인덱스입니다\n");
            return;
        }

        if (index == 0) {
            insert_first(data);   //맨 앞 삽입과 동일하니 재사용
            return;
        }

        Node* prev = list.head;
        for (int i = 0; i < index - 1; i++) {   //삽입 위치 바로 앞 노드까지 이동
            prev = prev->next;
        }

        Node* newNode = create_node(data);
        newNode->next = prev->next;   //새 노드가 뒤쪽을 가리키고
        prev->next = newNode;         //앞 노드가 새 노드를 가리킴

        if (newNode->next == NULL) {   //맨 뒤에 삽입된 경우 tail 갱신
            list.tail = newNode;
        }

        list.size++;
        printf("index %d 위치에 %d를 삽입했습니다\n", index, data);
    }
    else if (string_compare(mode, "data") == 0) {
        int targetData, newData;
        scanf("%d %d", &targetData, &newData);

        Node* cur = list.head;
        while (cur != NULL && cur->data != targetData) {
            cur = cur->next;
        }

        if (cur == NULL) {
            printf("해당 data를 가진 노드를 찾을 수 없습니다\n");
            return;
        }

        Node* newNode = create_node(newData);
        newNode->next = cur->next;
        cur->next = newNode;

        if (newNode->next == NULL) {
            list.tail = newNode;
        }

        list.size++;
        printf("data %d 뒤에 %d를 삽입했습니다\n", targetData, newData);
    }
    else {
        printf("잘못된 모드입니다 (index 또는 data)\n");
    }
}

//delete_first: 맨 처음 노드 삭제
void delete_first(void)
{
    if (list.head == NULL) {
        printf("리스트가 비어있습니다\n");
        return;
    }

    Node* target = list.head;
    list.head = list.head->next;   //head를 다음 노드로

    if (list.head == NULL) {       //노드가 하나였던 경우
        list.tail = NULL;
    }

    printf("%d를 맨 앞에서 삭제했습니다\n", target->data);
    free(target);
    list.size--;
}

//delete_back: 맨 마지막 노드 삭제
void delete_back(void)
{
    if (list.head == NULL) {
        printf("리스트가 비어있습니다\n");
        return;
    }

    if (list.head == list.tail) {   //노드가 하나뿐인 경우
        printf("%d를 맨 뒤에서 삭제했습니다\n", list.tail->data);
        free(list.head);
        list.head = NULL;
        list.tail = NULL;
    }
    else {
        Node* cur = list.head;
        while (cur->next != list.tail) {   //마지막 바로 앞 노드까지 이동
            cur = cur->next;
        }
        printf("%d를 맨 뒤에서 삭제했습니다\n", list.tail->data);
        free(list.tail);
        list.tail = cur;
        list.tail->next = NULL;   //새로운 마지막 노드는 NULL을 가리키게
    }

    list.size--;
}

//delete: 원하는 요소 삭제 (index 또는 data 값 기준)
//입력형식:
//  delete index <index>
//  delete data <targetData>
void delete_node(void)
{
    char mode[10];
    scanf("%s", mode);

    if (list.head == NULL) {
        printf("리스트가 비어있습니다\n");
        int dummy;
        scanf("%d", &dummy);   //그래도 인자는 읽어서 버려줘야 함
        return;
    }

    if (string_compare(mode, "index") == 0) {
        int index;
        scanf("%d", &index);

        if (index < 0 || index >= list.size) {
            printf("잘못된 인덱스입니다\n");
            return;
        }

        if (index == 0) {
            delete_first();
            return;
        }

        Node* prev = list.head;
        for (int i = 0; i < index - 1; i++) {
            prev = prev->next;
        }

        Node* target = prev->next;
        prev->next = target->next;   //대상을 건너뛰고 연결

        if (target == list.tail) {
            list.tail = prev;
        }

        printf("index %d의 %d를 삭제했습니다\n", index, target->data);
        free(target);
        list.size--;
    }
    else if (string_compare(mode, "data") == 0) {
        int targetData;
        scanf("%d", &targetData);

        if (list.head->data == targetData) {
            delete_first();
            return;
        }

        Node* prev = list.head;
        Node* cur = list.head->next;
        while (cur != NULL && cur->data != targetData) {
            prev = cur;
            cur = cur->next;
        }

        if (cur == NULL) {
            printf("해당 data를 가진 노드를 찾을 수 없습니다\n");
            return;
        }

        prev->next = cur->next;

        if (cur == list.tail) {
            list.tail = prev;
        }

        printf("data %d를 삭제했습니다\n", targetData);
        free(cur);
        list.size--;
    }
    else {
        printf("잘못된 모드입니다 (index 또는 data)\n");
    }
}

//get_entry: 요소 찾기
//입력형식:
//  get_entry index <index>      -> 해당 index의 data 출력
//  get_entry data <targetData>  -> 해당 data를 가진 첫 노드의 index 출력
void get_entry(void)
{
    char mode[10];
    scanf("%s", mode);

    if (string_compare(mode, "index") == 0) {
        int index;
        scanf("%d", &index);

        if (index < 0 || index >= list.size) {
            printf("잘못된 인덱스입니다\n");
            return;
        }

        Node* cur = list.head;
        for (int i = 0; i < index; i++) {
            cur = cur->next;
        }
        printf("index %d의 data는 %d입니다\n", index, cur->data);
    }
    else if (string_compare(mode, "data") == 0) {
        int targetData;
        scanf("%d", &targetData);

        Node* cur = list.head;
        int index = 0;
        while (cur != NULL && cur->data != targetData) {
            cur = cur->next;
            index++;
        }

        if (cur == NULL) {
            printf("해당 data를 가진 노드를 찾을 수 없습니다\n");
            return;
        }
        printf("data %d의 index는 %d입니다\n", targetData, index);
    }
    else {
        printf("잘못된 모드입니다 (index 또는 data)\n");
    }
}

//get_length: 리스트 전체 길이 반환
void get_length(void)
{
    printf("리스트의 길이: %d\n", list.size);
}

//print_list: 리스트의 모든 요소 출력
void print_list(void)
{
    if (list.head == NULL) {
        printf("리스트가 비어있습니다\n");
        return;
    }

    Node* cur = list.head;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

//reverse: 화살표(next) 방향을 전부 뒤집어서 리스트를 역순으로 만듦
void reverse(void)
{
    Node* prev = NULL;
    Node* cur = list.head;
    Node* next = NULL;

    list.tail = list.head;   //기존 head가 새로운 tail이 됨

    while (cur != NULL) {
        next = cur->next;   //다음 노드 미리 저장 (안 하면 방향 바꾸는 순간 잃어버림)
        cur->next = prev;   //화살표 방향 뒤집기
        prev = cur;          //prev 한 칸 전진
        cur = next;          //cur 한 칸 전진
    }

    list.head = prev;   //마지막에 도달한 노드가 새로운 head
    printf("리스트를 역순으로 만들었습니다\n");
}

//리스트 전체 메모리 해제
void free_list(void)
{
    Node* cur = list.head;
    while (cur != NULL) {
        Node* next = cur->next;
        free(cur);
        cur = next;
    }
    list.head = NULL;
    list.tail = NULL;
    list.size = 0;
}

int main(void)
{
    char command[20];

    //리스트 초기화
    list.head = NULL;
    list.tail = NULL;
    list.size = 0;

    while (1) {
        printf("입력: ");
        scanf("%s", command);

        if (string_compare(command, "insert") == 0) {
            insert();
        }
        else if (string_compare(command, "insert_back") == 0) {
            int data;
            scanf("%d", &data);
            insert_back(data);
        }
        else if (string_compare(command, "insert_first") == 0) {
            int data;
            scanf("%d", &data);
            insert_first(data);
        }
        else if (string_compare(command, "delete") == 0) {
            delete_node();
        }
        else if (string_compare(command, "delete_first") == 0) {
            delete_first();
        }
        else if (string_compare(command, "delete_back") == 0) {
            delete_back();
        }
        else if (string_compare(command, "get_entry") == 0) {
            get_entry();
        }
        else if (string_compare(command, "get_length") == 0) {
            get_length();
        }
        else if (string_compare(command, "print_list") == 0) {
            print_list();
        }
        else if (string_compare(command, "reverse") == 0) {
            reverse();
        }
        else if (string_compare(command, "exit") == 0) {
            break;
        }
        else {
            printf("잘못된 입력입니다\n");
        }
    }

    free_list();
    return 0;
}
