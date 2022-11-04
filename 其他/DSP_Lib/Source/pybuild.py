import os
import sys

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
    # gcc .\StatisticsFunctions\arm_max_f32.c -c -I $pwd -o .\build\$filename.o
    for i in filelist[2]:
        command = f"gcc {path}/{i} -c -I {os.getcwd()} -o ./build/{i[:-1]}o"
        os.system(command)
        print (command)


def getfile(path, fileexp=[]):
    a = os.walk(path)
    filelist = a.next()
    for i in fileexp:
        filelist[2].remove(i)

    for i in range(len(filelist[2])):
        filelist[2][i] = path + filelist[2][i]

    return filelist[2]


filename, filetype = sys.argv[1].split(".")

if filename != "":
    if filetype in("c", "cpp"):

        try:
            os.remove(f"./{filename}.exe")
        except:
            print ("no have file")

        a = getfile("./build/")
        objstr = ""
        for i in a:
            objstr = objstr + i + " "

        command = "gcc -g " + "./"+filename+"." + \
            filetype + " " + objstr + "-o "+filename+".exe"
        os.system(command)
    else:
        print ("input file error !!")
