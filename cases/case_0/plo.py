import numpy
import matplotlib.pyplot as plt

try:
    f = open("domain_boundary");
except IOError:
    print '\nThe file \'domain_boundary\' is not present. Probably the executable \'run\' has not been run or some files have been deleted.\n\n'
    quit()

xb = []
yb = []

line = f.readline()

while(line):
    coord = line.split()
    xb.append(float(coord[0]))
    yb.append(float(coord[1]))
    line = f.readline()
    if not line:
        break
f.close();

# i for inner, o for outer

xo = []
yo = []
xi = []
yi = []

try:
    f = open("points_i");
except IOError:
    print '\nThe file \'points_i\' is not present. \nProbably the executable \'run\' has not been run or some files have been deleted.\n\n'
    quit()

line = f.readline()
while(line):
    coord = line.split()
    xi.append(float(coord[0]))
    yi.append(float(coord[1]))
    line = f.readline()
    if not line:
        break
f.close()

try:
    f = open("points_o");
except IOError:
    print '\nThe file \'points_o\' is not present. \nProbably the executable \'run\' has not been run or some files have been deleted.\n\n'
    quit()

line = f.readline()
while(line):
    coord = line.split()
    xo.append(float(coord[0]))
    yo.append(float(coord[1]))
    line = f.readline()
    if not line:
        break
f.close()

plt.plot(xb, yb, 'b-')
plt.plot(xi, yi, 'g+')
plt.plot(xo, yo, 'r+')
plt.show()
