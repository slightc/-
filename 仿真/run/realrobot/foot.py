import hid_servo
import MIK
import time
import math
import _thread

def SetRightFoot(x,y,z,time_set):
    a = MIK.GetJointAngle(round(x),round(y),round(z+1))
    hid_servo.SetPos(11,a[0],time_set)
    hid_servo.SetPos(10,a[1],time_set) #I
    hid_servo.SetPos(9,a[2],time_set) #I
    hid_servo.SetPos(8,a[3],time_set)
    hid_servo.SetPos(7,a[4],time_set)

def SetLeftFoot(x,y,z,time_set):
    
    a = MIK.GetJointAngle(round(x),round(y),round(z))
    hid_servo.SetPos(16,a[0],time_set)
    hid_servo.SetPos(15,a[1],time_set)
    hid_servo.SetPos(14,a[2],time_set)
    hid_servo.SetPos(13,a[3],time_set) #I
    hid_servo.SetPos(12,a[4],time_set)

def SetFoot(x,yl,yr,zl,zr):
    timestart = time.time() 

    SetLeftFoot(round(x),round(yl),round(zl),0)
    SetRightFoot(round(x),round(yr),round(zr),0)

    use_time = (time.time()-timestart)
    delay_time = 0.04 - use_time

    if delay_time < 0.001:
        delay_time = 0.001

    time.sleep(delay_time)

dir = -1
yllast = 0

def SetFootY(val,step,h):
    dir = 0
    wave = int(val+0.5*step)%(2*step)
    if wave > step:
        wave = 2*step - wave
        dir = 1
    wave = wave - 0.5*step

    if dir == 0:
        setzr = math.fabs((wave+0.5*step)*(wave-0.5*step)*4/step/step*h)
        setzl = 0
    else:
        setzl = math.fabs((wave+0.5*step)*(wave-0.5*step)*4/step/step*h)
        setzr = 0

    print(dir)


    # left right
    return round(wave),-round(wave),setzl,setzr


for i in range(320):
    setyl,seryr,setzl,setzr = SetFootY(i*1,20,10)
    SetFoot(setyl,setyl,seryr,setzl,setzr)

SetFoot(0,0,0,0,0)