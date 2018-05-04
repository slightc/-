#include<stdio.h>

#define DEBUG 

int main(){
    int tempNumber=0;
    //tempNumber=VALUE;
    #ifdef DEBUG
        printf("The VAlUE is %d\n",tempNumber);
    #endif
    printf("1...");
    getchar();
    return 0; 
}