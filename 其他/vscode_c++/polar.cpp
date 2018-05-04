#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define RectPol 0
#define PoltRec 1
#define PI 3.141593

struct Point{
    float x;
    float y;
    float r;
    float a;
};

struct Line{
    struct Point start;
    struct Point end;
};

void CoorChange(struct Point *point,char mode=0);
float CalDist(struct Point point,struct Line line);

int main()
{
    struct Point point1={0,1,0,0},point2={1,0,0,0},point3={0,0,0,0};
    struct Line line;

    CoorChange(&point1);
    CoorChange(&point2);
    line.start=point1;
    line.end=point2;

    point3=point1;
    point3.a+=0.1;
    CoorChange(&point3,1);
    printf("%f \n",CalDist(point3,line));

    point3=point1;
    point3.a-=0.1;
    CoorChange(&point3,1);
    printf("%f \n",CalDist(point3,line));

    point3=point1;
    point3.r+=0.1;
    CoorChange(&point3,1);
    printf("%f \n",CalDist(point3,line));

    point3=point1;
    point3.r-=0.1;
    CoorChange(&point3,1);
    printf("%f \n",CalDist(point3,line));

    system("pause");
    return 0;
}

void CoorChange(struct Point *point,char mode)
{
    if(mode==0)
    {
        point->r=sqrt(point->x*point->x+point->y*point->y);
        point->a=atan(point->y/point->x);
    }
    else
    {
        point->x=point->r*cos(point->a);
        point->y=point->r*sin(point->a);
    }
}

float CalDist(struct Point point,struct Line line)
{
    float dis;
    float a,b,c,p;
    a=sqrt((line.end.y-line.start.y)*(line.end.y-line.start.y)+(line.end.x-line.start.x)*(line.end.x-line.start.x));
    b=sqrt((point.y-line.start.y)*(point.y-line.start.y)+(point.x-line.start.x)*(point.x-line.start.x));
    c=sqrt((point.y-line.end.y)*(point.y-line.end.y)+(point.x-line.end.x)*(point.x-line.end.x));
    p=(a+b+c)/2;

    dis=2*sqrt(p*(p-a)*(p-b)*(p-c))/a;
    return dis;
}