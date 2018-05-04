//#include<vertor.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Wage{
    int number;
    char name[20];
    int base;
    int add;
    int sub;
    int fact;
};

void Compute(struct Wage *wage,int length);
void Sort(struct Wage *wage,int length);
int Search(struct Wage *wage,int length,int number);
void Output(struct Wage *wage,int length,char *name);

#define LEN 5

int main()
{
    int mode,num;
    char name[20];
    int len=LEN;
    struct Wage wage[LEN]={
        {50001,"zhanghua",6000,1200,500,0},
        {50003,"lifang",5000,1000,200,0},
        {50002,"sunlei",7000,800,100,0},
        {50005,"chenxin",4000,1100,300,0},
        {50004,"guyan",9000,1200,0,0},
    };

    printf("输入你的名字\n");
    scanf("%s",name);

    while(mode!=0)
    {
        system("cls");
        printf("输入要执行的函数1~4\n");
        printf("1:Compute()计算实发工资\n");
        printf("2:Sort()按职工号排序\n");
        printf("3:Search()按职工号搜索\n");
        printf("4:Output()输出所有职工信息\n");
        printf("5:计算,排序,输出\n");
        printf("0:退出程序\n");
        scanf("%d",&mode);

        switch(mode)
        {
            case 0: 
            printf("退出程序\n");
            system("pause"); break;

            case 1:
            printf("计算实发工资\n");
            Compute(wage,len);
            printf("计算完成\n");
            system("pause"); break;

            case 2:
            printf("按职工号排序\n");
            Sort(wage,len);
            printf("排序完成\n");
            system("pause"); break;

            case 3:
            printf("按职工号搜索\n");
            printf("输入要搜索的职工号:");
            scanf("%d",&num);
            if(num>=0 && num<999999)
                {
                    Search(wage,len,num);
                    printf("搜索完成\n");
                }
            else
                 printf("超出搜索范围\n");
            system("pause"); break;

            case 4:
            printf("输出所有职工信息\n");
            Output(wage,len,name);
            printf("输出完成\n");
            system("pause"); break;
            break;

            case 5:
            printf("计算,排序,输出\n");
            Compute(wage,len);
            Sort(wage,len);
            Output(wage,len,name);
            printf("执行完成\n");
            system("pause"); break;
            break;

            default:
            printf("输入错误，请正确输入\n");
            system("pause"); break;
        }
    }

    return 0;   
}

void Compute(struct Wage *wage,int length)
{
    int i;

    for(i=0;i<length;i++)
    {
        wage[i].fact=wage[i].base+wage[i].add-wage[i].sub;
    }
}

void Sort(struct Wage *wage,int length)
{
    struct Wage change;
    
    int i,j;
    for(j=0;j<length-1;j++)
    {
        for(i=j;i<length-1;i++)
        {
            if(wage[i].number>wage[i+1].number)
            {
                change=wage[i];
                wage[i]=wage[i+1];
                wage[i+1]=change;
            }
        }
    }

}

int Search(struct Wage *wage,int length,int number)
{
    int left=0,right=length-1,seek=(length-1)/2;
    for(;left!=right;)
    {
        if(number>wage[seek].number)
            left=seek;
        else if(number<wage[seek].number)
            right=seek;
        else if(number==wage[seek].number)
            {
                printf("num:%d name:%s base:%d add:%d sub:%d fact:%d\n",
                wage[seek].number,wage[seek].name,wage[seek].base,wage[seek].add,wage[seek].sub,wage[seek].fact
                );
                return seek;
            }
        seek=(left+right)/2;
    }
    printf("没有此职工号\n");
    return -1;
}

void Output(struct Wage *wage,int length,char *name)
{
    FILE *outfile;
    char date[20];
    struct tm *timep;
    time_t timel;
    int i;

    time(&timel);
    timep=localtime(&timel);
    sprintf(date,"%d/%d/%d",timep->tm_year+1900,timep->tm_mon+1,timep->tm_mday);

    outfile=fopen("gzbb.dat","w");

    fprintf(outfile,"\t\t\t\t\tGong zi Bao Biao\n");
    fprintf(outfile,"************************************************************\n");
    fprintf(outfile,"\tnum\t\tname\t\tbase\tadd\t\tsub\t\tfact\n");
    for(i=0;i<length;i++)
    {
        fprintf(outfile,"\t%-7d\t%-10s\t%-7d\t%-7d\t%-7d\t%-7d\n",
        wage[i].number,wage[i].name,wage[i].base,wage[i].add,wage[i].sub,wage[i].fact
        );
    }
    fprintf(outfile,"************************************************************\n");
    fprintf(outfile,"\t\t\t\t\t\t\t\t\t\t\tname:%s\n",name);
    fprintf(outfile,"\t\t\t\t\t\t\t\t\t\t\tdate:%s\n",date);
    fclose(outfile);
}
