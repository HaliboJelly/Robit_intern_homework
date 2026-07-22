#include <stdio.h>

int main(void){
    int list1D[5] = {10,20,30,40,50};

    size_t size;

    size = sizeof(list1D);
    printf("size: %d\n",size);
    return 0;
}