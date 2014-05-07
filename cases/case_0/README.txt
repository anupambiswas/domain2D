Description:

In this project, a polygon around the origin (0, 0) is studied. The number of sides is input at the command line. If nothing is input, a default polygon with 10 sides is chosen. The convex2D object 'dom' is provided the boundary points of the polygon. Then 5000 points are randomly generated, and 'dom' finds out if any randomly generated point is inside the polygon or outside and accordingly stores its coordinates in the files 'points_i' and 'points_o' (i for inner, o for outer). 

Guidelines to build the project and run the code:

$ make
# It makes the executanle file 'run'

$ ./run
# Studies polygon with 10 sides. If run again, studies a different decagon

$ ./run 100
# Studies a polygon with 100 sides

$./run resetf
# Removes case files written during a previous run

In order to visualize points, there are two options. 

1) If gnuplot is installed, use the following commands:

$ gnuplot
gnuplot> set xrange [-1.5:1.5]
gnuplot> set yrange [-1.5:1.5]
gnuplot> set size ratio 1.
gnuplot> p 'domain_boundary' w l,'points_i','points_o'

2) If python is installed, run the following command at the command line:

$ python plo.py
# numpy and matplotlib should also be installed for the plots, else an error will be thrown

In case of an error/confusion please feel free to email anupambiswas85@gmail.com
