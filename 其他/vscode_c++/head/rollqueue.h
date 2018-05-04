#include "stdint.h"

#ifndef __ROLLQUEUE_HEAD__
#define __ROLLQUEUE_HEAD__

struct ROLLQUE
{
    void *p;
    uint32_t offset;
    uint32_t len;
    
};

#define ROLLQUE_INSERT(rp,tpye,val) do{\
                                        *((tpye *)(rp)->p + (rp)->offset) = (val);\
                                        (rp)->offset++;\
                                        if((rp)->offset==(rp)->len) (rp)->offset=0;\
                                    }while(0);

#define ROLLQUE_READ(rp,tpye,num) ((rp)->offset+(num)>=(rp)->len?\
                                  *((tpye *)(rp)->p+(rp)->offset+(num)-(rp)->len):\
                                  *((tpye *)(rp)->p+(rp)->offset+(num)))

#endif