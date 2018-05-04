import time
import math
import serial

IDMap = [0, 5, 6, 2, 3, 1, 4]

Angle_offset = [0, 1, 2, 3, 4, 5, 6, \
92, 90+5, 120+5, 98, 90,\
92, 91-1, 50+2, 90, 89, \
17, 18, 19, 20]

Angle_dir = [1, 1, 1, 1, 1, 1, 1, \
1, 1, -1, -1, 1,\
1, -1, 1, 1, 1, \
1, 1, 1, 1]
# Angle_offset = [0, 1, 2, 3, 4, 5, 6, \
# 91, 90, 120, 98, 89,\
# 91, 91, 53, 91, 90, \
# 17, 18, 19, 20]

ser = serial.Serial("COM4",115200,timeout=100)


def serial_flush():
    #ser.init(115200, timeout=100)
    serial_flush()


def serial_write(data):
    ser.write(data)


def serial_read(lengh):
    return (ser.read(lengh))


def add_check(data):
    data_len = len(data)
    sum_val = 0
    for i in range(2, data_len-2):
        sum_val += data[i]
    sum_val = sum_val % 256
    data[data_len-2] = sum_val
    return sum_val


def check_is_macth(data):
    if data:
        if len(data) != 10:
            return False
        data_len = len(data)
        sum_val = 0
        for i in range(2, data_len-2):
            sum_val += data[i]
        return(data[data_len - 2] == (sum_val %256))
    else:
        return False


def head_is_macth(data):
    if data:
        if len(data) != 10:
            return False
        return ((data[0] == 0xfa) and (data[1] == 0xaf))
    else:
        return False

def id_is_macth(data, servo_id):
    if data:
        if len(data) != 10:
            return False
        return(data[2] == servo_id)
    else:
        return False


def ReadID():
    val = bytearray([0xFA, 0xAF, 0x00, 0xD4, 0x00,
                     0x00, 0x00, 0x00, 0xD4, 0xED])
    #                0,    1,    2,    3,    4,
    add_check(val)
    serial_write(val)
    rev = serial_read(10)
    if (head_is_macth(rev) and check_is_macth(rev)):
        return rev[2], rev[7]
    else:
        return -1, -1


def SetID(servo_id, new_id):
    val = bytearray([0xFA, 0xAF, servo_id, 0xCD, 0x00,
                     new_id, 0x00, 0x00, 0xD4, 0xED])
    #                0,    1,    2,    3,    4,
    add_check(val)
    serial_write(val)
    rev = serial_read(10)
    if (head_is_macth(rev) and check_is_macth(rev) and id_is_macth(rev, servo_id)):
        return True
    else:
        return False


def SetOffset(servo_id, offset):
    val = bytearray([0xFA, 0xAF, servo_id, 0xD2, 0x00,
                     0x00, 0x00, offset, 0xD4, 0xED])
    #                0,    1,    2,    3,    4,
    add_check(val)
    serial_write(val)
    rev = serial_read(10)
    if (head_is_macth(rev) and check_is_macth(rev) and id_is_macth(rev, servo_id)):
        return True
    else:
        return False


def SetPos(servo_id, pos, time, n1=0, n2=1):
    val = bytearray([0xFA, 0xAF, servo_id, 0x01, pos*Angle_dir[servo_id]+Angle_offset[servo_id],
                     time, n1, n2, 0xD4, 0xED])
    #                0,    1,    2,    3,    4,
    add_check(val)
    serial_write(val)
    rev = serial_read(1)
    if (len(rev) == 1):
        return True
    else:
        return False


def DisableTorque(servo_id):
    val = bytearray([0xFA, 0xAF, servo_id, 0x02, 0x00,
                     0x00, 0x00, 0x00, 0xD4, 0xED])
    #                0,    1,    2,    3,    4,
    add_check(val)
    serial_write(val)
    rev = serial_read(10)
    if (head_is_macth(rev) and check_is_macth(rev) and id_is_macth(rev, servo_id)):
        return rev[5], rev[7]
    else:
        return - 1, -1


def ReadPos(servo_id):
    val = bytearray([0xFA, 0xAF, servo_id, 0x03, 0x00,
                     0x00, 0x00, 0x00, 0xD4, 0xED])
    #                0,    1,    2,    3,    4,
    add_check(val)
    serial_write(val)
    rev = serial_read(10)
    # print (rev)
    if (head_is_macth(rev) and check_is_macth(rev) and id_is_macth(rev, servo_id)):
        return rev[5], rev[7]
    else:
        return - 1, -1

def SendData(data0, data1, data2, data3, data4, data5):
    val = bytearray([0xFA, 0xAF, data0, data1, data2,
                     data3, data4, data5, 0xD4, 0xED])
    add_check(val)
    serial_write(val)

def ReadData():
    rev = serial_read(10)
    if rev:
        for i in rev:
            print(hex(rev), end=" ")
        print(" ")
    else:
        print("no data")

# SetTorqueLimit(0xfe, 1000)
# new_id = 12
# # revID, offset = ReadID()
# # a = SetID(revID, new_id)
# # a = SetOffset(new_id, 18)
# a = SetPos(new_id, 90, 10)
# # seta, nowa = ReadPos(new_id)
# scs_id = 0xfe

# SetPos(scs_id, -60, 70)
# time.sleep(0.7)
# SetPos(scs_id, 0, 70)
# time.sleep(0.7)
