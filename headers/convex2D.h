#ifndef CONVEX2D_H
#define CONVEX2D_H

#include<iostream>
#include<cstdlib>
#include<fstream>
#include<ctime>
#include<cmath>
#include<string>

class convex2D
{
private:
  typedef struct boundary
  {
    double x,y;
    struct boundary *next;
    struct boundary *prev;
  }bdry;

  typedef struct boundarySegmentChain
  {
    double a,b,c,val;
    struct boundarySegmentChain *next;
    boundarySegmentChain(){val=0.0;}
  }segChain;

  typedef struct convexDomainLayers
  {
    bdry *wrap;
    segChain *segm;
    double xcen,ycen;
    int numDaug;
    struct convexDomainLayers *daughters;
    convexDomainLayers(){daughters=NULL;numDaug=0;}
  }domain;

private:

  bdry *bdryOrig;

  domain *domn;

public:

  convex2D();
  convex2D(double *xPnts,double *yPnts,int numPnts);
  void solveRegion(double *xPnts,double *yPnts,int numPnts);
  bool contains(double x,double y,domain *dom=NULL);
  void copy(bdry *b,std::string fil);
private:

  void findHead(bdry **orig);
  void makeCopy(bdry *orig,bdry *copy);
  void generate(bdry **boun,domain *dom);
  bool isValidVertex(double *xp,double *yp);
  bdry* rewind(bdry *ver);
  void makeSegments(domain *dom);
};

#endif
