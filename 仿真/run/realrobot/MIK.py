binfp = open("ikdata.bin","rb")

data = binfp.read()

def GetJointData(x,y,z):

    znum = (4-round(z))*525
    xnum = (10+round(x))*25
    ynum = 12+round(y)

    lineNum = (znum+xnum+ynum)*5

    # binfp.seek(lineNum)
    a = data[lineNum:lineNum+5] # binfp.read(5)
    b = [0]*5
    for i in range(5):
        b[i] = a[i]-256 if a[i]>127 else a[i]
    return b

def InserVal(a,b,maxval,val):
    c = [0]*len(a)
    for i in range(len(a)):
        c[i] = (a[i]*(maxval-val)+b[i]*val)/maxval
    return c


def listdiff(x,y):
    out = [0]*len(x)
    for i in range(len(x)):
        out[i] = x[i]-y[i]
    return out


def GetJointAngle(x,y,z):
    x0 = int(x//5)
    y0 = int(y//5)
    z0 = int(z//5)

    x0y0z0 = GetJointData(x0,y0,z0)
    x1y0z0 = GetJointData(x0+1,y0,z0)
    x0y1z0 = GetJointData(x0,y0+1,z0)
    x0y0z1 = GetJointData(x0,y0,z0+1)

    dx = listdiff(x1y0z0,x0y0z0)
    dy = listdiff(x0y1z0,x0y0z0)
    dz = listdiff(x0y0z1,x0y0z0)

    kx = (x%5)/5
    ky = (y%5)/5
    kz = (z%5)/5

    dxyz = [0]*len(x0y0z0)
    xkykzk = [0]*len(x0y0z0)

    for i in range(len(x0y0z0)):
        dxyz[i] = dx[i]*kx+dy[i]*ky+dz[i]*kz
        xkykzk[i] = x0y0z0[i]+dxyz[i]

    for i in range(len(xkykzk)):
        xkykzk[i] = int(round(xkykzk[i]))
    return xkykzk