#include <windows.h>
#include <stdio.h>

POINT out(){
    POINT x={5,6};
    return x;
}

int main(void)
{
    POINT a={1,2};

    printf("%d \n",out().x);
}