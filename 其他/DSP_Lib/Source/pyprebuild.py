import os

direxp = ["build"]


def getdir(path, direxp=[]):
    a = os.walk(path)

    dirlist = a.next()

    for i in direxp:
        dirlist[1].remove(i)

    for i in range(len(dirlist[1])):
        dirlist[1][i] = path + dirlist[1][i]

    return dirlist[1]


def buildfile(path, fileexp=[]):
    a = os.walk(path)

    filelist = a.next()

    for i in fileexp:
        filelist[2].remove(i)
    # gcc .\StatisticsFunctions\arm_max_f32.c -c -I $pwd -o .\build\$filename.o
    for i in filelist[2]:
        command = "gcc -g " + path + "/" + i + \
            " -c -I "+os.getcwd()+" -o ./build/" + i[: - 1] + "o"
        os.system(command)
        print command


def getfile(path, fileexp=[]):
    a = os.walk(path)
    filelist = a.next()
    for i in fileexp:
        filelist[2].remove(i)

    for i in range(len(filelist[2])):
        filelist[2][i] = path + filelist[2][i]

    return filelist[2]


fileexp1 = ["arm_bitreversal2.S"]
ismake = True
if ismake:
    dirlist = getdir("./", direxp)
    for i in dirlist:
        if i == "./TransformFunctions":
            buildfile(i, fileexp1)
        else:
            buildfile(i)
else:
    a = getfile("./build/")
    objstr = ""
    for i in a:
        objstr = objstr + i + " "

    command = "gcc " + "./test.c " + objstr
    os.system(command)
