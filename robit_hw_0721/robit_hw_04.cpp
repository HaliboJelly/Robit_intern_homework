#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

struct Date
{
    int year;
    int month;
    int day;
};

struct Time
{
    int hour;
    int min;
    int sec;
};

struct Timestamp   //중첩 구조체
{
    struct Date date;
    struct Time time;
    long long total_sec;   //초 단위로 환산한 전체 시간
};

// 윤년 개수 세기
int ElapsedLeapYears(int year)
{
    int count = 0;
    for (int i = 1; i < year; i++)
    {
        if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) //윤년 판단
        {
            count++;
        }
    }
    return count; 
}

// 해당 연도가 윤년인지 확인
int isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int main(void)
{
    struct Timestamp list[2];

    // 월별 일수를 다 저장한 이유는 1월 2월 3월 4월 .... 다 자기 멋대로 총 일수가 바뀌기 때문이다.
    int month_days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    for (int i = 0; i < 2; i++)     //입력 시퀀스 가동
    {
        scanf("%d %d %d %d %d %d",
            &list[i].date.year, &list[i].date.month, &list[i].date.day,
            &list[i].time.hour, &list[i].time.min, &list[i].time.sec);
    }

    for (int i = 0; i < 2; i++)
    {
        list[i].total_sec = 0;

        //지나간 연도 까지 전체 초 계산 (평년 365일 + 윤년366일 보정)
        list[i].total_sec += (long long)(list[i].date.year - 1) * 365 * 86400;      //평년
        list[i].total_sec += (long long)ElapsedLeapYears(list[i].date.year) * 86400;    //윤년

        //올해 지나간 달 까지 전체 초
        for (int m = 0; m < list[i].date.month - 1; m++)
        {
            int days = month_days[m];
            if (m == 1 && isLeapYear(list[i].date.year))   // m==1 → 2월(index 1), 윤년이면 29일
            {
                days = 29;
            }
            list[i].total_sec += (long long)days * 86400;
        }

        //이번 달 지나간 일 까지 전체 초
        list[i].total_sec += (long long)(list[i].date.day - 1) * 86400;

        list[i].total_sec += (long long)list[i].time.hour * 3600;   //시
        list[i].total_sec += (long long)list[i].time.min * 60;      //분
        list[i].total_sec += list[i].time.sec;                      //초
    }

    //두 시각의 차이 (절댓값)
    long long diff;
    if (list[0].total_sec > list[1].total_sec)
    {
        diff = list[0].total_sec - list[1].total_sec;
    }
    else
    {
        diff = list[1].total_sec - list[0].total_sec;
    }

    //초 단위 차이를 시/분/초로 변환
    int hour = (int)(diff / 3600);
    int min = (int)((diff % 3600) / 60);
    int sec = (int)(diff % 60);

    printf("시간 차이: %d시 %d분 %d초\n", hour, min, sec);

    return 0;
}