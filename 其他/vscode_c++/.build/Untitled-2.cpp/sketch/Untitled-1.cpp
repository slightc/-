#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000)  ? 1:0) //必要的，我是背下来的   
  
using namespace std;  
  
int main(){  
    char a;  
    int now=1;  
    printf("按Q开始左键点击\n");  
    printf("按W开始右键点击\n");  
    printf("按空格停止点击\n");  
    while(1){  
        if(KEY_DOWN(VK_SPACE)){//VK_SPACE 是空格的虚拟键值   
            now=0;  
            Sleep(1);//你的手不会再一瞬间送开，所以要处理一下   
        }  
        if(KEY_DOWN('A')){  

            mouse_event(MOUSEEVENTF_MOVE,-2,0,0,0);
            Sleep(10);  
        }  

        if(KEY_DOWN('S')){  
            now++;
        }  

        if(KEY_DOWN('D')){  
           
            mouse_event(MOUSEEVENTF_MOVE,2,0,0,0);
            Sleep(10);  
        }  

 //       if(now==1){//模拟点击左键   
  //          mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);  
 //           Sleep(10);//要留给某些应用的反应时间   
 //           mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);  
 //       }  
 //       if(now==2){//模拟点击右键   
  //          mouse_event(MOUSEEVENTF_RIGHTDOWN,0,0,0,0);  
  //          Sleep(10);   
  //          mouse_event(MOUSEEVENTF_RIGHTUP,0,0,0,0);  
 //       }  
        //MOUSEEVENTF_MOVE;
        now=0;  
       // Sleep(20);//点击间隔 单位是毫秒   
    }  
}  