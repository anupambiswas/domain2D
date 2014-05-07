domain2D
========
This project is about points and regions in 2-dimensions. Region here refers to a part of the XY plane which has a well defined boundary. For example, x^2 + y^2 < 1 is a region and its boundary is x^2 + y^2 = 1. Not all regions may be represented in simple mathematical terms, for example, a nation's border or an oil spill on the floor. This project has an abstract data type called the convex2D, which, when provided the boundary points of a region in anti-clockwise order, processes it internally and from there on, it may be used to determine if any arbitrary point in XY plane is inside the region or not.

Currently, a project 'case_0' is provided in which polygon shapes are studied.

The convex2D ADT has many possible applications. It may be used to have area-estimate of an intricately-shaped region, study extent of intersection of two or more regions. It may be used to generate points for mesh generation for CFD simulations, especially for complex geometries, for which structured grid generation is not possible.
