#include <stdint.h>

#ifndef __MQUEUE_HEAD__
#define __MQUEUE_HEAD__

typedef struct QueueStrust{
    void *p;
    uint32_t head;
    uint32_t tail;
    uint32_t len;
}QueueTypedef;


#define InitQueue(pqueue,pdata,leng) (pqueue)->head=0;(pqueue)->tail=0;\
                                    (pqueue)->p=(pdata);(pqueue)->len=(leng);

#define IsQueueEmpty(pqueue) ((pqueue)->head == (pqueue)->tail)

#define IsQueueFull(pqueue)  ((pqueue)->head == ((pqueue)->tail+1) || \
                             (pqueue)->head == ((pqueue)->tail+1-(pqueue)->len))

#define EnQueue(pqueue,type,data)    do{*((type *)(pqueue)->p + (pqueue)->tail) = (data);\
                                        (pqueue)->tail = ((pqueue)->tail +1)%(pqueue)->len;\
                                        }while(0);

#define DeQueue(pqueue,type) (((pqueue)->head = ((pqueue)->head +1)%(pqueue)->len) == 0 ?\
                            *((type *)(pqueue)->p + (pqueue)->len -1):\
                            *((type *)(pqueue)->p + (pqueue)->head -1) )

#define GetQueueLen(pqueue) (((pqueue)->tail+(pqueue)->len-(pqueue)->head)%(pqueue)->len)

#endif