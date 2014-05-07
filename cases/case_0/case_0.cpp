#include"../../headers/convex2D.h"

using namespace std;

int main(int argc,char *argv[])
{
  srand(time(NULL));
  double *x,*y;
  convex2D dom;
  int N,NBoundary,i;

  if(argc>1)
    NBoundary=atoi(argv[1]);
  else
    NBoundary=10;

  double pi=4.0*atan(1.0),rMin,rMax,r,rDif;
  rMin=0.5;
  rMax=1.0;
  rDif=rMax-rMin;
  x=new double [NBoundary];
  y=new double [NBoundary];

  double tht;
  fstream B("domain_boundary",ios::out);
  for(i=0;i<NBoundary;i++)
    {
      tht=i*2*pi/NBoundary;
      r=rMin+(rand()/(RAND_MAX+1.0))*rDif;
      x[i]=r*cos(tht);
      y[i]=r*sin(tht);
      B<<x[i]<<" "<<y[i]<<endl;
    }
  B<<x[0]<<" "<<y[0]<<endl;
  B.close();

  dom.solveRegion(x,y,NBoundary);
  double xp,yp,L=1.5;
  fstream F("points_i",ios::out),G("points_o",ios::out);
  N=5000;
  for(i=0;i<N;i++)
    {
      xp=-L+(rand()/(RAND_MAX+1.0))*2*L;
      yp=-L+(rand()/(RAND_MAX+1.0))*2*L;
      if(dom.contains(xp,yp))
	F<<xp<<" "<<yp<<endl;
      else
	G<<xp<<" "<<yp<<endl;
    }
  F.close();
  G.close();

  remove("actbor");
  remove("cover");
  remove("border");
  remove("newbor");
  remove("point");
  return(0);
}
