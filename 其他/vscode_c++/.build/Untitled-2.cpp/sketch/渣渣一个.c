#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include <time.h> 

typedef struct
{
        float x_last;   
        float p_last;
        float Q;
        float R;
        float kg;
        float x_mid;
        float x_now;
        float p_mid;
        float p_now;
} Kalman;


float get_rand(float num) 
{      
     return num+140*((rand()/( float )RAND_MAX) - 0.5);  //随机噪声
}  

float Kalman_filter(Kalman* data,float measure)
{
        //	data->x_last = measure;

        data->x_mid = data->x_last;
        //x_last=x(k-1|k-1),x_mid=x(k|k-1)
        data->p_mid = data->p_last+data->Q; 
        //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=噪声
        data->kg = data->p_mid/(data->p_mid+data->R); 
        //kg为kalman filter，R为噪声
        data->x_now=data->x_mid+data->kg*(measure-data->x_mid);
        //估计出的最优值
        data->p_now=(1-data->kg)*data->p_mid;//最优值对应的covariance
        data->p_last = data->p_now;  //更新covariance值
        data->x_last = data->x_now;  //更新系统状态值
        return data->x_now;
}


int main()
{        
float a,b,sum,max,last,eor;
int i;
Kalman data1;
srand(clock());
if (1)
{
	    data1.x_last=get_rand(70);   
        data1.p_last=0.01;
        data1.Q=0.0010;
        data1.R=15;
}

sum=0;
max=0;
for(i=0;i<500;i++)
        {        
 a = 70.0;
 b = get_rand(a);
Kalman_filter(&data1,b);
        }
        for(i=0;i<20000;i++)
        {        
 a = 70.0;
 b = get_rand(a);
printf ("%f\t",Kalman_filter(&data1,b));
printf("%10f\t",b);
printf("%f\n",a);
sum+=fabs(data1.x_now-70.0);

if ( fabs(data1.x_now-70) >max)
max=fabs(data1.x_now-70);
        }
        
        
printf("卡尔曼滤波后\t");
printf("加噪声数据\t\n实际数据");
printf("%f  %f",sum/20000,max);

    return 0;
}