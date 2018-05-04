PathKeyPoint = [[0, 0], [1, 0], [1, 1], [0, 1]]  # xyz
BezierPoint = []


def GetMidPoint(points):
    MidPoint = []

    for i in range(len(points)):
        MidPoint.append([])
        nex = i + 1
        if nex == len(points):
            nex = 0

        for j in range(len(points[i])):
            MidPoint[i].append((points[i][j] + points[nex][j]) / 2.0)

    return MidPoint


def GetBezierPoint(pathpoints):
    midpoint = GetMidPoint(PathKeyPoint)
    leng = len(pathpoints)
    BezierPoint = []

    for i in range(leng):
        pre_point = i - 1
        if pre_point == -1:
            pre_point = leng-1
        BezierPoint.append(
            [midpoint[pre_point], pathpoints[i], midpoint[i]])
    return BezierPoint


def BezierCal(p0, p1, p2, t):
    leng = len(p0)
    val = []
    for i in range(leng):
        val.append(p0[i] * (1 - t) * (1 - t) + p1[i]
                   * 2 * t * (1 - t) + p2[i] * t * t)
    return val


def BezierCalAll(bezierpoint, t):
    leng = len(bezierpoint)

    t_real = t * leng
    n = int(t_real)
    t_real = t_real - n

    val = BezierCal(bezierpoint[n][0], bezierpoint[n]
                    [1], bezierpoint[n][2], t_real)
    return val


BezierPoint = GetBezierPoint(PathKeyPoint)

# print BezierPoint

for i in range(100):
    val = BezierCalAll(BezierPoint, i / 100.0)
    print val[0], val[1]
