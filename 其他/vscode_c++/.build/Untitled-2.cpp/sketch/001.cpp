#include<stdio.h>
#include<stdlib.h>

struct ROLL
{
    char *p;
    char offset;
    char len;
    
};

void Insert(struct ROLL *p,char num)
{
    p->p[p->offset++]=num;
    if(p->offset==p->len)
    {
        p->offset=0;
    }
}

short Read(struct ROLL *p,char num)
{
    char shift=p->offset;
    shift+=num;
    
    if(shift>=p->len)
    {
        shift-=p->len;
    }

    return p->p[shift];
}


int main(void)
{
    struct ROLL roll;
    short data[7]={0};
    short data1[7]={0};
    short get_num=0;
    int i=0;

    roll.p=(char *)data;
    roll.offset=0;
    roll.len=14; 

    while(1)
    {
        scanf("%d",&get_num);
        
      //  get_num++;
        Insert(&roll,get_num);

        for(i=0;i<14;i++)
        {
            printf("%d  ",Read(&roll,i));
            //printf("%d  ",roll.p[i]);
            
        }
        printf("\n");

    }

    system("pause");
}