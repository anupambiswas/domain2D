Description:

In this project, a polygon around the origin (0, 0) is studied. The number of sides is input at the command line. If nothing is input, a default polygon with 10 sides is chosen. The convex2D object 'dom' is provided the boundary points of the polygon. Then 5000 points are randomly generated, and 'dom' finds out if any randomly generated point inside the polygon or outside and accordingly stores its coordinates in the files 'points_i' and 'points_o' (i for inner, o for outer). 

Guidelines to build the project and run the code:

$ make
# It makes the executanle file 'run'

$ ./run
# Studies polygon with 10 sides. If run again, studies a different decagon

$ ./run 100
# Studies a polygon with 100 sides

$./run resetf
# Removes case files written during a previous run

In case of an error/confusion please feel free to email anupambiswas85@gmail.com
