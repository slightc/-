#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "head/rollqueue.h"

//g++ -mwindows -o MoveWin.exe .\Untitled-1.cpp -l gdi32

#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000)  ? 1:0) //必要的，我是背下来的   
  
using namespace std;  
#define LEFTMOVE VK_SCROLL
#define RIGHTMOVE VK_PAUSE

void LEFTMOVEWIN(){
    keybd_event(VK_CONTROL, 0, 0 ,0);  
    keybd_event(VK_LWIN, 0, 0 ,0);  
    keybd_event(VK_RIGHT, 0, 0 ,0);  
    keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP ,0);  
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP,0);  
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP,0);
}

void RIGHTMOVEWIN(){
    keybd_event(VK_CONTROL, 0, 0 ,0);  
    keybd_event(VK_LWIN, 0, 0 ,0);  
    keybd_event(VK_LEFT, 0, 0 ,0);  
    keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP ,0);  
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP,0);  
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP,0);
}

void SHOWWIN(){
    keybd_event(VK_LWIN, 0, 0 ,0);  
    keybd_event(VK_TAB, 0, 0 ,0);  
    keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP ,0);  
    keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP,0);  
}


#define VAL1 3
#define VAL2 10
#define VAL3 250
#define VAL4 10000

int main(){  
    //system("start /b ping 10.10.10.11 -t");
    POINT data[100]={0};
    POINT mousepos;
    ROLLQUE rque1={.p=data, .offset=0, .len=100};
    int tick;
    
    while(1){  

        GetCursorPos(&mousepos);
        printf("%d %d\n",ROLLQUE_READ(&rque1,POINT,99).x,ROLLQUE_READ(&rque1,POINT,99).y);

        ROLLQUE_INSERT(&rque1,POINT,mousepos);

        // if(KEY_DOWN(RIGHTMOVE)){  
        //     LEFTMOVEWIN();
        //     while(KEY_DOWN(RIGHTMOVE));  
        //     Sleep(10);
        // }  
        // if(KEY_DOWN(LEFTMOVE)){  
        //     RIGHTMOVEWIN();
        //     while(KEY_DOWN(LEFTMOVE));  
        //     Sleep(10);
        // }

        if( ROLLQUE_READ(&rque1,POINT,100 - 1).y<VAL4 &&
            ROLLQUE_READ(&rque1,POINT,100 - 1).x<VAL1 &&
            ROLLQUE_READ(&rque1,POINT,100 - 2).x<VAL2 &&
            ROLLQUE_READ(&rque1,POINT,100 - 4).x>VAL3 &&
            tick>10){  
            RIGHTMOVEWIN();
            tick = 0;
        }  

        if( ROLLQUE_READ(&rque1,POINT,100 - 1).y<VAL4 &&
            ROLLQUE_READ(&rque1,POINT,100 - 1).x>(1920-VAL1) &&
            ROLLQUE_READ(&rque1,POINT,100 - 2).x>(1920-VAL2) &&
            ROLLQUE_READ(&rque1,POINT,100 - 4).x<(1920-VAL3) &&
            tick>10){  
            LEFTMOVEWIN();
            tick = 0;
        }

        if( ROLLQUE_READ(&rque1,POINT,100 - 1).y>(1080-VAL1) &&
            ROLLQUE_READ(&rque1,POINT,100 - 2).y>(1080-VAL2) &&
            ROLLQUE_READ(&rque1,POINT,100 - 4).y<(1080-VAL3) &&
            tick>10){  
            SHOWWIN();
            tick = 0;
        }
        

        Sleep(20);//点击间隔 单位是毫秒   
        tick++;
    }  
}  