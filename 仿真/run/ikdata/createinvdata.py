from lib import vrep
import time
import math
import threading

clientID = -1

zeroPoint = [0.028999147936701775, -0.3000001013278961, 0.17600001394748688]



def Connect(port=20001, ip='127.0.0.1'):
    global clientID
    print('Program started')
    vrep.simxFinish(-1)  # just in case, close all opened connections
    clientID = vrep.simxStart(ip, port, True,
                              True, 5000, 1)  # Connect to V-REP
    if clientID != -1:
        print('Connected to remote API server')
    else:
        print('Failed connecting to remote API server')
        exit()
    return clientID


#####################################
clientID = Connect()

code,targethandle = vrep.simxGetObjectHandle(clientID,"Dummy_target",vrep.simx_opmode_blocking)
code,tiphandle = vrep.simxGetObjectHandle(clientID,"Dummy_tip",vrep.simx_opmode_blocking)

joint_hanldes = [0,0,0,0,0]
for i in range(5):
    code,joint_hanldes[i] = vrep.simxGetObjectHandle(clientID,"Revolute_joint"+str(i),vrep.simx_opmode_blocking)
####################################

def SetTargetPos(set_pos):
    global zeroPoint,clientID,targethandle
    # code,pos = vrep.simxGetObjectPosition(clientID,targethandle,-1,vrep.simx_opmode_blocking)
    pos = []
    for i in range(len(zeroPoint)):
        pos.append(zeroPoint[i]+set_pos[i]/1000.0)
    vrep.simxSetObjectPosition(clientID,targethandle,-1,pos,vrep.simx_opmode_oneshot_wait)

def ReadJointPosStart():
    pos = [0,0,0,0,0]
    for i in range(5):
        code,pos[i] = vrep.simxGetJointPosition(clientID,joint_hanldes[i],vrep.simx_opmode_streaming)
    time.sleep(1)


def ReadJointPos():
    pos = [0,0,0,0,0]
    for i in range(5):
        code,pos[i] = vrep.simxGetJointPosition(clientID,joint_hanldes[i],vrep.simx_opmode_buffer)
        pos[i] = round(pos[i]*180/math.pi)
    return pos

def ReadTipPos():
    code,pos = vrep.simxGetObjectPosition(clientID,tiphandle,-1,vrep.simx_opmode_blocking)
    for i in range(len(zeroPoint)):
        pos[i] = pos[i]-zeroPoint[i]
    return pos

def ReadTipAngle():
    code,pos = vrep.simxGetObjectOrientation(clientID,tiphandle,-1,vrep.simx_opmode_blocking)
    for i in range(len(pos)):
        pos[i] = pos[i]*180/math.pi
    return pos



def WaitArrivalPos(pos):
    wait = True
    while wait == True:
        wait = False

        pos_now = ReadTipPos()
        angle_now = ReadTipAngle()
     
        for i in range(len(pos)):
            if (pos[i] - pos_now[i]*1000)>1:
                wait = True
        
        for i in range(len(angle_now)):
            if (angle_now[i])>1:
                wait = True
        time.sleep(0.001)






# code,targethandle = vrep.simxGetObjectHandle(clientID,"Dummy_target",vrep.simx_opmode_blocking)
# code,pos = vrep.simxGetObjectPosition(clientID,targethandle,-1,vrep.simx_opmode_blocking)

SetTargetPos([0,0,0]) 
ReadJointPosStart()
time.sleep(0.5)

filep = open("invdata.csv","w")

for z in range(-20,21):
    for x in range(-50,51):
        for y in range(-60,61):
            pos = [x,y,z]
            SetTargetPos(pos)
            WaitArrivalPos(pos)
            joint_pos = ReadJointPos()


            # print(pos,joint_pos)
            writestr =  str(pos[0])+","+\
                        str(pos[1])+","+\
                        str(pos[2])+","+ \
                        str(joint_pos[0])+","+\
                        str(joint_pos[1])+","+\
                        str(joint_pos[2])+","+\
                        str(joint_pos[3])+","+\
                        str(joint_pos[4])+",\n"
            # print(writestr,end=" ")
            filep.write(writestr)


filep.close()




# pos = [0,0,0]

# for i in range(100):
#     # pos[0]+=-0.5/1000
#     time.sleep(0.01)