import numpy as np
import matplotlib.pyplot as plt
from pylab import *
import math

dt = 0.04
t = 2
T = 2/dt

xlim(0, 10)
ylim(-70, 70)

x = np.arange(0.0, 10.0, dt)
y = []


for i in x:
    if i < 2:
        y.append(0)
    else:
        y.append(30)
y += [50] * 500
y += [0] * 100


d = 0
v = 0
a = 0
u = 0

zmp = 0
k = 210/9800
zmpnum = []
dnum = []


def phycal():
    global d, v, a, u
    d += v*dt
    v += a*dt
    a += u*dt


def zmpcal():
    global d, v, a, u, zmp, k
    zmp = d - k * a


errsum = 0
errlast = 0
zmpdis = 0
zmpdis1 = 0
zmpdis2 = 0
zmpdisnum = []
###########################################
for i in range(len(x)):
    # if i == 400:
    #     u = 0.000001
    # if i == 500:
    #     u = -0.000002
    # if i == 600:
    #     u = 0
    phycal()
    zmpcal()
    zmpnum.append(zmp)
    dnum.append(d)
    zmpdis = sum(y[i+m-8]*(1-cos(m/40*2*pi))*(1/19) for m in range(20))

    # zmpdis = y[i]
    zmpdis1 = zmpdis
    zmpdis2 = zmpdis1
    zmpdisnum.append(zmpdis)
    #########################
    #########################
    err = zmpdis - zmp
    errsum += err
    errdif = err-errlast
    errlast = err

    # prew = 0
    # start_val = 0
    # max_val = 0.0005
    # end_val = 0
    # c_time = 50
    # e_time = 100

    # gp = np.linspace(start_val, max_val, c_time)
    # for j in range(c_time):
    #     prew += gp[j] * y[i + j]

    # gp = np.linspace(max_val, end_val, e_time-c_time)
    # for j in range(e_time-c_time):
    #     prew += gp[j]*y[i+c_time+j]

    a = err * 25 + errsum * 0.000 + errdif * -0.00 + \
        v * -6

    # a = (d - zmp)*0.004 + (zmpdis - zmp)*0.003 - v*0.08 + errdif*0.005
    # u = errsum * -0.005 + errdif * 0.0 + err * -0.01 + \
    #     d * -0.01 + v * 0.0 + a * -0.0 + \
    #     prew*0.01
    # y[i + 0] * 0.0000 + y[i + 40] * 0.000165 + y[i + 80] * 0.00000 + \


###########################################
plt.figure(1)

plt.plot(x, y[:int(10/0.04)])
plt.plot(x, zmpnum)
plt.plot(x, dnum)
# plt.plot(x, zmpdisnum)

plt.show()
