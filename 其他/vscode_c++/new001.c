#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef struct test
{
    uint8_t initflag;

    uint8_t a;
    void (*fun)(void);
}test_Typedef;


#define obj_def(n)  void n##fun_1(void);\
                    uint8_t n##init(void);\
                    test_Typedef n = {\
                        n##init()\
                    };

#define obj_fun(n,val)  uint8_t n##init(void){\
                            n.fun = &n##fun_1;\
                            n.a = val;\
                        }\
                        void n##fun_1(void){\
                            printf("The a is %d",n.a);\
                        }

#define obj_creat(n,val)    obj_def(n);obj_fun(n,val)

obj_creat(test_1,20);
obj_creat(_try,125);

int main(){
    test_1.fun();
    _try.fun();
}