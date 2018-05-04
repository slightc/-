# 25 525

z=0
x=0
y=0

znum = (4-z)*525
xnum = (10+x)*25
ynum = 12+y+1

lineNum = znum+xnum+ynum

binfp = open("invbin.bin","wb")

fp = open("invdata.csv","r")

strval = "val"
while strval != "":
    strval = fp.readline()
    if strval != "":
        a = strval.split(',') #3-7

        for i in range(3,8):
            val = bytes(((int(a[i])+256)%256,))
            binfp.write(val)

binfp.close()

print(strval.split(','))