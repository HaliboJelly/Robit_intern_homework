#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define STR_LEN 30    //이름,주소 등 문자열 최대길이
#define MAX_DUP 100   //번호 중복 검색시 최대 저장개수


//테스트파일로 "1" 파일 첨부 불러오기 메뉴 선택 후 1 입력


typedef struct {        //주소 구조
    char country[STR_LEN];   //나라
    char province[STR_LEN];  //도
    char city[STR_LEN];      //시
    char district[STR_LEN];  //구
}Address;

typedef struct {        //학생 구조
    int id;              //번호
    char name[STR_LEN];  //이름
    Address addr;        //주소
    double grade;        //성적
}Student;

enum {       //정렬/검색 기준
    KEY_ID = 1, KEY_NAME, KEY_COUNTRY, KEY_PROVINCE, KEY_CITY, KEY_DISTRICT, KEY_GRADE
};

//함수 원형
int str(const char s1[], const char s2[]);     //문자열 비교

void clear_buffer(void);                              //입력버퍼 비우기
int input_int(const char* msg);                        //정수 예외처리 입력
double input_double(const char* msg);                  //실수 예외처리 입력
void input_str(const char* msg, char out[], int len);  //문자열 예외처리 입력

int select_key(void);                                          //기준선택 메뉴
int cmp_student(const Student* a, const Student* b, int key);  //기준별 비교
void print_header(void);                                       //출력 헤더
void print_student(const Student* s);                          //학생 한명 출력

void stu_print(const Student* list, int size);                  //전체출력
void stu_sort(Student* list, int size, int key);                //정렬
void stu_search(const Student* list, int size);                  //검색
void stu_add(Student** list, int* size, int* capacity);          //추가
void stu_del(Student* list, int* size);                          //삭제
void stu_save(const Student* list, int size);                    //저장
void stu_read(Student** list, int* size, int* capacity);         //불러오기

int main(void){
    int capacity = 4;               //현재 할당된 칸수
    int size = 0;                   //실제 등록된 학생수
    Student* list = (Student*)malloc(sizeof(Student) * (size_t)capacity);  //동적할당
    int menu;

    if(list == NULL){
        printf("메모리 할당 실패\n");
        return 1;
    }

    while(1){
        printf("\n[1]추가 [2]삭제 [3]정렬 [4]검색 [5]전체출력 [6]저장 [7]불러오기 [0]종료\n");
        menu = input_int("메뉴 선택: ");

        if(menu == 1){
            stu_add(&list, &size, &capacity);
        }
        else if(menu == 2){
            stu_del(list, &size);
        }
        else if(menu == 3){
            int key = select_key();     //기준 입력받음
            if(key != 0){
                stu_sort(list, size, key);
                printf("정렬 완료\n");
                stu_print(list, size);
            }
        }
        else if(menu == 4){
            stu_search(list, size);
        }
        else if(menu == 5){
            stu_print(list, size);
        }
        else if(menu == 6){
            stu_save(list, size);
        }
        else if(menu == 7){
            stu_read(&list, &size, &capacity);
        }
        else if(menu == 0){
            free(list);      //종료시 반드시 해제
            printf("프로그램을 종료\n");
            break;
        }
        else{
            printf("ERROR   없는 메뉴\n");
        }
    }

    return 0;
}

int str(const char s1[], const char s2[]){   //s1>s2:1  s1==s2:0  s1<s2:-1
    int i = 0;
    while(s1[i] != '\0' && s2[i] != '\0'){
        if((unsigned char)s1[i] < (unsigned char)s2[i]) return -1;
        if((unsigned char)s1[i] > (unsigned char)s2[i]) return 1;
        i++;
    }
    if(s1[i] == '\0' && s2[i] == '\0'){
    return 0;
    }
    return (s1[i] == '\0') ? -1 : 1;      //짧은쪽이 앞
}

void clear_buffer(void){        //버퍼에 남은 문자 비우기
    int c;
    while((c = getchar()) != '\n' && c != EOF)
        ;
}

int input_int(const char* msg){
    int value;
    while(1){
        printf("%s", msg);
        int r = scanf("%d", &value);
        if(r == 1){
            clear_buffer();
            return value;
        }
        if(r == EOF){          // 입력 자체가 끊긴 경우
            printf("입력이 종료됨\n");
            exit(0);
        }
        printf("ERROR   숫자 입력만\n");
        clear_buffer();
    }
}

double input_double(const char* msg){     
    double value;
    while(1){
        printf("%s", msg);
        int r = scanf("%lf", &value); 
        if(r == 1){
            clear_buffer();
            return value;
        }
        if(r == EOF){          
            printf("입력이 종료됨\n");
            exit(0);
        }
        printf("ERROR 숫자 입력만\n");
        clear_buffer();
    }
}

void input_str(const char* msg, char out[], int len){   //공백없는 한단어 입력
    printf("%s", msg);
    if(scanf("%29s", out) != 1){
        out[0] = '\0';
    }
    clear_buffer();
    (void)len;
}

int select_key(void){       //정렬/검색 기준 고르는 메뉴
    int key;
    printf("선택 [1]번호 [2]이름 [3]나라 [4]도 [5]시 [6]구 [7]성적\n");
    key = input_int("번호 입력: ");
    if(key < 1 || key > 7){
        printf("ERROR 1~7 사이로 입력\n");
        return 0;
    }
    return key;
}

int cmp_student(const Student* a, const Student* b, int key){   //key기준 비교
    if(key == KEY_ID){
        if(a->id < b->id){
        return -1;
        }
        if(a->id > b->id){
        return 1;
        }
        return 0;
    }
    else if(key == KEY_NAME)     
        return str(a->name, b->name);
    else if(key == KEY_COUNTRY)  
        return str(a->addr.country, b->addr.country);
    else if(key == KEY_PROVINCE) 
        return str(a->addr.province, b->addr.province);
    else if(key == KEY_CITY)     
        return str(a->addr.city, b->addr.city);
    else if(key == KEY_DISTRICT) 
        return str(a->addr.district, b->addr.district);
    else if(key == KEY_GRADE){
        if(a->grade > b->grade){
        return -1;
        }
        if(a->grade < b->grade){
        return 1;
        }
        return 0;
    }
    return 0;
}

void print_header(void){       //출력용 헤더 한줄
    printf("\n%-6s %-10s %-8s %-8s %-8s %-8s %6s\n",
           "번호", "이름", "나라", "도", "시", "구", "성적");
}

void print_student(const Student* s){    //학생 한명 정보 출력
    printf("%-6d %-10s %-8s %-8s %-8s %-8s %6.2lf\n",
           s->id, s->name,s->addr.country, s->addr.province,s->addr.city, s->addr.district,s->grade);
}

void stu_print(const Student* list, int size){    //전체출력
    if(size == 0){
        printf("등록된 학생이 없음\n");
        return;
    }
    print_header();
    for(int i = 0; i < size; i++){
        print_student(&list[i]);
    }
}

void stu_sort(Student* list, int size, int key){   //선택정렬, 구조체 통째로 교환
    for(int i = 0; i < size - 1; i++){
        int min = i;
        for(int j = i + 1; j < size; j++){
            if(cmp_student(&list[j], &list[min], key) < 0)
                min = j;
        }
        if(min != i){
            Student tmp = list[i];    //구조체 교환
            list[i] = list[min];
            list[min] = tmp;
        }
    }
}

void stu_search(const Student* list, int size){    //조건에 맞는 학생 이름 전부 출력
    int key = select_key();
    int found = 0;
    if(key == 0){ 
    return;
    }

    if(size == 0){
        printf("등록된 학생이 없음\n");
        return;
    }

    if(key == KEY_ID){
        int target = input_int("찾을 번호: ");
        for(int i = 0; i < size; i++)
            if(list[i].id == target){
                printf("%s\n", list[i].name);
                found++;
            }
    }
    else if(key == KEY_GRADE){
        double target = input_double("찾을 성적: ");
        for(int i = 0; i < size; i++){
            double d = list[i].grade - target;
            if(d < 0) {
            d = -d;
            }
            if(d < 0.0001){      //실수는 오차범위로 비교
                printf("%s\n", list[i].name);
                found++;
            }
        }
    }
    else{
        char target[STR_LEN];
        input_str("찾을 값: ", target, STR_LEN);
        for(int i = 0; i < size; i++){
            const char* field;
            if(key == KEY_NAME){
            field = list[i].name;
            }
            else if(key == KEY_COUNTRY){
            field = list[i].addr.country;
            }
            else if(key == KEY_PROVINCE){
            field = list[i].addr.province;
            }
            else if(key == KEY_CITY){
            field = list[i].addr.city;
            }
            else{
            field = list[i].addr.district;
            }

            if(str(field, target) == 0){
                printf("%s\n", list[i].name);
                found++;
            }
        }
    }

    if(found == 0){
    printf("해당하는 학생이 없음\n");
    }
    else{
    printf("총 %d명 찾음.\n", found);
    }
}

void stu_add(Student** list, int* size, int* capacity){    //추가, 용량부족시 2배확장
    Student* s;
    printf("※ 도가 없는 지역은 '-' 를 입력하세요\n");
    if(*size >= *capacity){
        int new_cap = (*capacity == 0) ? 4 : (*capacity) * 2;
        Student* tmp = (Student*)realloc(*list, sizeof(Student) * (size_t)new_cap);   //재할당 필요
        if(tmp == NULL){
            printf("메모리 재할당 실패\n");
            return;      //기존 데이터는 그대로 유지
        }
        *list = tmp;
        *capacity = new_cap;
    }

    s = &(*list)[*size];    //새로 채울 칸

    s->id = input_int("번호: ");
    input_str("이름: ", s->name, STR_LEN);
    input_str("나라: ", s->addr.country, STR_LEN);
    input_str("도: ", s->addr.province, STR_LEN);
    input_str("시: ", s->addr.city, STR_LEN);
    input_str("구: ", s->addr.district, STR_LEN);
    s->grade = input_double("성적: ");

    (*size)++;
    printf("추가 완료   현재 %d명\n", *size);
}

void stu_del(Student* list, int* size){    //번호로 검색, 중복이면 목록에서 선택삭제
    int idx[MAX_DUP];
    int found = 0;
    int target_id;
    int del;

    if(*size == 0){
        printf("등록된 학생이 없음\n");
        return;
    }

    target_id = input_int("삭제할 학생 번호: ");

    for(int i = 0; i < *size && found < MAX_DUP; i++)
        if(list[i].id == target_id){
            idx[found++] = i;
        }

    if(found == 0){
        printf("해당 번호의 학생이 없음\n");
        return;
    }

    if(found == 1){
        del = idx[0];
    }
    else{      //중복이면 목록보여주고 선택
        int pick;
        printf("중복된 학생이 %d명 있음\n", found);
        print_header();
        for(int i = 0; i < found; i++){
            printf("[%d] ", i + 1);
            print_student(&list[idx[i]]);
        }
        pick = input_int("삭제할 항목 번호: ");
        if(pick < 1 || pick > found){
            printf("ERROR   범위를 벗어남\n");
            return;
        }
        del = idx[pick - 1];
    }

    for(int i = del; i < *size - 1; i++){    //뒤 원소를 한칸씩 당김
        list[i] = list[i + 1];
    }
    (*size)--;
    printf("삭제 완료      현재 %d명\n", *size);
}

void stu_save(const Student* list, int size){    //파일 저장
    char filename[STR_LEN];
    FILE* fp;

    input_str("저장할 파일 이름: ", filename, STR_LEN);
    fp = fopen(filename, "w");
    if(fp == NULL){
        printf("ERROR   파일을 열 수 없음\n");
        return;
    }

    fprintf(fp, "%d\n", size);      //첫줄에 학생수
    for(int i = 0; i < size; i++){
        fprintf(fp, "%d %s %s %s %s %s %.2lf\n",
                list[i].id, list[i].name,
                list[i].addr.country, list[i].addr.province,
                list[i].addr.city, list[i].addr.district,
                list[i].grade);
    }
    fclose(fp);
    printf("%s 저장 완료    %d명\n", filename, size);
}

void stu_read(Student** list, int* size, int* capacity){    //파일 불러오기
    char filename[STR_LEN];
    FILE* fp;
    int n;

    input_str("불러올 파일 이름: ", filename, STR_LEN);
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("ERROR   파일을 열 수 없음\n");
        return;
    }

    if(fscanf(fp, "%d", &n) != 1 || n < 0){      //파일 형식 예외처리
        printf("ERROR   파일 형식이 잘못됨.\n");
        fclose(fp);
        return;
    }

    if(n > *capacity){      //필요하면 확장
        Student* tmp = (Student*)realloc(*list, sizeof(Student) * (size_t)n);
        if(tmp == NULL){
            printf("메모리 재할당 실패\n");
            fclose(fp);
            return;
        }
        *list = tmp;
        *capacity = n;
    }

    for(int i = 0; i < n; i++){
        Student* s = &(*list)[i];
        if(fscanf(fp, "%d %29s %29s %29s %29s %29s %lf",
                  &s->id, s->name,
                  s->addr.country, s->addr.province,
                  s->addr.city, s->addr.district,
                  &s->grade) != 7){
            printf("ERROR   %d번째 줄이 손상됨.\n", i + 1);
            *size = i;
            fclose(fp);
            return;
        }
    }

    *size = n;
    fclose(fp);
    printf("%s 에서 %d명 불러옴.\n", filename, n);
}