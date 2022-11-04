import time
import math
from pyb import UART

IDMap = [0, 5, 6, 2, 3, 1, 4]

ser = UART(2, 115200, timeout=100)  # X3 X4


def serial_flush():
    ser.init(115200, timeout=100)


def serial_write(data):
    ser.write(data)


def serial_read(lengh):
    return ser.read(lengh)


def check_val(data):
    data_len = len(data)
    sum_val = sum(data[i] for i in range(2, data_len-1))
    sum_val = 255 - sum_val % 256
    data[data_len-1] = sum_val
    return sum_val


def SetID(scs_id):
    val = bytearray([0xFF, 0xFF, 0xFE, 0x04, 0x03, 0x05, 0x01, 0xF4])
    #                0,    1,    2,    3,    4,    5,    6,    7
    val[6] = scs_id
    check_val(val)
    serial_write(val)


def write_reg(scs_id, addr, val1):
    val = bytearray([0xFF, 0xFF, 0x00, 0x04, 0x03, 0x05, 0x01, 0xF4])
    #                0,    1,    2,    3,    4,    5,    6,    7
    val[2] = scs_id
    val[5] = addr
    val[6] = val1
    check_val(val)
    serial_write(val)


def write_d_reg(scs_id, addr, val1):
    val = bytearray([0xFF, 0xFF, 0x00, 0x05, 0x03, 0x00, 0x00, 0x00, 0xF4])
    #                0,    1,    2,    3,    4,    5,    6,    7,    8
    val[2] = scs_id
    val[5] = addr
    val[6] = (val1 >> 8) & 0x00ff
    val[7] = (val1) & 0x00ff
    check_val(val)
    serial_write(val)


def write_q_reg(scs_id, addr, val1, val2):
    val = bytearray([0xFF, 0xFF, 0x00, 0x07, 0x03,
                     0x00, 0x00, 0x00, 0xF4, 0xF4, 0xF4])
    #                0,    1,    2,    3,    4,
    #                5,    6,    7,    8,    9,    10
    val[2] = scs_id
    val[5] = addr
    val[6] = (val1 >> 8) & 0x00ff
    val[7] = (val1) & 0x00ff
    val[8] = (val2 >> 8) & 0x00ff
    val[9] = (val2) & 0x00ff
    check_val(val)
    serial_write(val)


def SetPos(scs_id, pos, time):
    pos = int(pos*13.654) + (2048)  # 12.8
    time = int(time*(10))
    write_q_reg(scs_id, 0x2a, pos, time)


def SetPosReal(scs_id, pos, time):
    write_q_reg(scs_id, 0x2a, pos, time)


def SetTorque(scs_id, val):
    write_reg(scs_id, 0x28, val)


def SetTorqueLimit(scs_id, val):
    write_d_reg(scs_id, 0x10, val)


def SetOffset(scs_id, val):
    if val < 0:
        val = -val+2000
    write_d_reg(scs_id, 0x14, val)


def SetOffset2(scs_id, val):
    write_d_reg(scs_id, 0x14, val)


def SetMode(scs_id, val):
    write_d_reg(scs_id, 0x1c, val)


def SetSpeed(scs_id, val):
    write_d_reg(scs_id, 0x3a, val)


def read_reg(scs_id, addr):
    val = bytearray([0xFF, 0xFF, 0x00, 0x04, 0x02, 0x05, 0x01, 0xF4])
    #                0,    1,    2,    3,    4,    5,    6,    7
    val[2] = scs_id
    val[5] = addr
    val[6] = 1
    check_val(val)
    serial_write(val)
    # rev 6+1


def read_d_reg(scs_id, addr):
    val = bytearray([0xFF, 0xFF, 0x00, 0x04, 0x02, 0x05, 0x02, 0xF4])
    #                0,    1,    2,    3,    4,    5,    6,    7
    val[2] = scs_id
    val[5] = addr
    val[6] = 2
    check_val(val)
    for i in val:
        print (hex(i)[2:]),
    print ("\n")
    serial_write(val)
    # rev 6+2


def read_n_reg(scs_id, addr, size):
    val = bytearray([0xFF, 0xFF, 0x00, 0x04, 0x02, 0x05, 0x01, 0xF4])
    #                0,    1,    2,    3,    4,    5,    6,    7
    val[2] = scs_id
    val[5] = addr
    val[6] = size
    check_val(val)
    serial_write(val)
    # rev 6+1

# val = bytearray([0xFF, 0xFF, 0xFE, 0x02, 0x06, 0x05])

# check_val(val)
# serial_write(val)

# scs_id = 0xfe
# offset = -10

# if offset >= 0:
#     SetOffset(scs_id, offset)
# else:
#     SetPos(scs_id, 90, 30)
#     time.sleep(1)
#     SetPos(scs_id, 120, 30)
# SetPos(scs_id, 120, 30)
# if scs_id != 0:
# SetID(scs_id)
#     #write_d_reg(1, 20, 195)
# else:
#     while True:
#         scs_id += 1
#         if scs_id == 7:
#             scs_id = 1
#         time.sleep(0.5)
#         SetPos(scs_id, 120, 30)
#         time.sleep(0.5)
#         SetPos(scs_id, 90, 30)

# SetMode(scs_id, 1)

# while True:
#     for i in range(30, 210):
#         SetPos(scs_id, i, 10)
#         time.sleep(6)
#         SetPos(scs_id, i+0.5, 10)
#         time.sleep(6)

#     for i in range(30, 210):
#         SetPos(scs_id, 240-i, 10)
#         time.sleep(6)
#         SetPos(scs_id, 240-i-0.5, 10)
#         time.sleep(6)

# SetTorque(scs_id, 1)


##### set zhongwei ######
# scs_id = 0xfe

# SetPos(scs_id, 0, 50)
# time.sleep(0.7)

# if 1:
#     SetOffset2(scs_id, -50)
#     time.sleep(1)

# SetPos(scs_id, -60, 40)
# time.sleep(0.4)
# SetPos(scs_id, 0, 40)
# time.sleep(0.4)


###############

#### set ID #####
# for scs_id in range(1, 7):
#     print("set id", scs_id, " real id", IDMap[scs_id])
#     SetPos(IDMap[scs_id], -30, 60)
#     time.sleep(0.6)
#     SetPos(IDMap[scs_id], 0, 60)
#     time.sleep(0.6)
    # SetID(IDMap[scs_id])

###############

# SetTorqueLimit(0xfe, 1000)


# SetPos(scs_id, -60, 70)
# time.sleep(0.7)
# SetPos(scs_id, 0, 70)
# time.sleep(0.7)

# SetTorque(0xfe, 0)

# SetID(4)
# dtime = 0.6

def speed_test(speed_time=0.25):
    scs_id = 0xfe
    start_a = -90
    delta = 180
    set_time = speed_time*delta/60.0
    SetPos(scs_id, start_a, set_time*50)
    time.sleep(set_time)
    SetPos(scs_id, start_a+delta, set_time*50)
    time.sleep(set_time)


def current_test():
    scs_id = 0xfe
    start_a = -90
    delta = 180
    set_time = 0.3*delta/60.0
    SetPos(scs_id, start_a, set_time*100)
    time.sleep(set_time)
    SetPos(scs_id, start_a+delta, set_time*100)
    time.sleep(set_time)


def load_test(offset=0):
    scs_id = 0xfe
    start_a = offset - 45
    delta = 90
    set_time = 1.5  # 1.5*delta/60.0
    SetPos(scs_id, start_a, set_time*100)
    time.sleep(set_time)
    SetPos(scs_id, start_a+delta, set_time*100)
    time.sleep(set_time)


def test():
    scs_id = 0xfe
    SetPos(scs_id, -30, 70)
    time.sleep(0.7)
    SetPos(scs_id, 0, 70)
    time.sleep(0.7)


def ReadPos(scs_id=0xfe):
    read_d_reg(scs_id, 0x38)
    serial_flush()
    if a := serial_read(8):
        if(a[0] == 0xff) & (a[1] == 0xf5):
            return(a[5] << 8) + a[6]
    return - 1
