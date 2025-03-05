#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main(){
    srand (time(NULL));
    int num = rand() % 10;
    printf("%d",num);


    return 0;
}