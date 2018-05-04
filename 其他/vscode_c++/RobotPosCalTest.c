#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

#define MOTO_A 0
#define MOTO_B 1
#define MOTO_C 2
#define MOTO_D 3

#define PI                 3.14159265358979f

typedef struct
{
    int last;
    int now;
}Encoder_Typedef;

typedef struct
{
    int xt;
    int yt;
    int at;
    float x;
    float y;
    float a;
}Position_Typedef;

Encoder_Typedef Encoder[4];
Position_Typedef position,realposition;

int main()
{
    float x, y;
	double a;
    double n = 0;

    Encoder[MOTO_A].now = 0;
    Encoder[MOTO_B].now = 0;
    Encoder[MOTO_C].now = 0;
    Encoder[MOTO_D].now = 0;
    
    while(1)
    {
        position.yt = ((Encoder[MOTO_A].now + Encoder[MOTO_B].now + Encoder[MOTO_C].now + Encoder[MOTO_D].now) >> 3);
        position.xt = ((Encoder[MOTO_D].now - Encoder[MOTO_B].now + Encoder[MOTO_A].now - Encoder[MOTO_C].now) >> 3);
        position.at = ((Encoder[MOTO_C].now - Encoder[MOTO_B].now + Encoder[MOTO_A].now - Encoder[MOTO_D].now) >> 3);
        y = position.y;
        x = position.x;
        //a = position.a;
        position.y = position.yt*0.029153;
        position.x = position.xt*0.027370;
        a = position.at*0.003196;
        position.a = a;
        y = position.y-y;
        x = position.x-x;
        //a = position.a-a;

        realposition.a = position.a;
        realposition.x += y * sin(a / 180.0*PI) + x * cos(a / 180.0*PI);
        realposition.y += y * cos(a / 180.0*PI) - x * sin(a / 180.0*PI);

            Encoder[MOTO_A].now += 5;
            Encoder[MOTO_B].now += 5;
            Encoder[MOTO_C].now += 5;
            Encoder[MOTO_D].now += 5;
        n = position.yt/realposition.y;
        Sleep(1);
    }

}