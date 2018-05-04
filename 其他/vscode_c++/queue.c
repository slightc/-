#include <stdio.h>
#include <stdint.h>
#include "head/Mqueue.h"


uint16_t test[16]={0};
QueueTypedef queue;

int main(){
    uint16_t i=0;
    InitQueue(&queue,test,16);
    while(1){
        EnQueue(&queue,uint16_t,10);
        EnQueue(&queue,uint16_t,11);
        EnQueue(&queue,uint16_t,12); 

        while (!IsQueueEmpty(&queue)){
            printf("%d \n",GetQueueLen(&queue));
            printf("%d \n",DeQueue(&queue,uint16_t));
        }
    }
}
