#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>

void get_gcode();
FILE *fp;

int main()
{
    char str[128];
    char i;
    char start = 0;
    //printf("ok!");

    fp = fopen("chenhan.gcode","r");



    // while(start != 1)
    // {
    //     fgets(str,100,fp);

    //     for(i=0;i<50;i++)
    //     {
           
    //         if(str[i] == ';' || str[i] == '\n')
    //         {
    //             i=50;
    //         }
    //         else if(str[i] != ' ')
    //             start = 1;
    //     }
    // }

    // char enable =0;
    

    // printf("%s",str);

    get_gcode();
    

    fclose(fp);
    printf("\n");
    system("pause");
    return 0;
    
}

void get_gcode()
{
    char enable =0;
    char str[128];
    char seek=0;
    char i=0;
    char start =0 ;
    char cmd = 0;
    float val=0;
    float point=1;

    float data = 0;

    fgets(str,100,fp);

    for(i=0;i<120;i++)
    {
        if( str[seek] == 'G' || str[seek] == 'g' ||
            str[seek] == 'M' || str[seek] == 'm' ||
            str[seek] == 'T' || str[seek] == 't' ||
            str[seek] == 'F' || str[seek] == 'f' ||
            str[seek] == 'S' || str[seek] == 's' ||
            str[seek] == 'X' || str[seek] == 'x' ||
            str[seek] == 'Y' || str[seek] == 'y' ||
            str[seek] == 'Z' || str[seek] == 'z' ||
            str[seek] == 'A' || str[seek] == 'a' ||
            str[seek] == 'B' || str[seek] == 'b' ||
            str[seek] == 'C' || str[seek] == 'c' ||
            str[seek] == 'E' || str[seek] == 'e' 
        ){
            enable =1;
            cmd = str[seek];
            start =0;
            seek ++;
            val=0;
            point=1;

            while(str[seek] == ' ' || str[seek] == '.' || (str[seek]>='0' && str[seek]<='9'))
            {
                if(str[seek]>='0' && str[seek]<='9')
                {
                    val = val*10 +(str[seek] - '0');
                    if(start==1)
                    {
                        point = point*10;
                    }
                }
                else if(str[seek] == '.' )
                {
                    start=1;
                }
                seek++;
            }
            data = val/point;
        }
        else{
            if(str[seek] == ' ')
            {
                seek++;
            }
            else if(str[seek] == ';' || str[seek] == '\n')
            {
                if(enable==0)
                {
                    fgets(str,100,fp);
                    i=0;
                    seek =0;
                }
                else{
                    printf("%s",str);
                    return ;
                }
            }
        }
        //seek++;
    }
}