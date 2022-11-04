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
        


setLeft = [0,0,0]
setRight = [0,0,0]

def SetFoot():
    global setLeft,setRight
    
    left = setLeft
    right = setRight

    SetLeftFoot(left[0],left[1],left[2],0)
    SetRightFoot(right[0],right[1],right[2],0)


sety = 0
dir = 0

for _ in range(400):
    setLeft[0] = setRight[0] = 0 #40*math.sin(i*2*math.pi/100)


    timestart = time.time()
    SetFoot()
    use_time = (time.time()-timestart)
    print(use_time)
    delay_time = 0.04 - use_time

    delay_time = max(delay_time, 0.01)
    time.sleep(delay_time)