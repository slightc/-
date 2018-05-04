T = 0.04

TIME = 2

t = [0]

x = []
y = []

for i in range (int(5/T)):
    t.append(t[-1]+T)

    rate_time = int(t[-1]/TIME)
    cyc_time = t[-1] - rate_time*TIME
    if cyc_time 

