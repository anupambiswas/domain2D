#include "../headers/convex2D.h"

convex2D::convex2D(){}

convex2D::convex2D(double *xPnts,double *yPnts,int numPnts){solveRegion(xPnts,yPnts,numPnts);}

void convex2D::solveRegion(double *xPnts,double *yPnts,int numPnts)
{
  bdryOrig=new bdry;
  bdry *prev=NULL,*cur=bdryOrig;
  int i;
  for(i=0;i<numPnts;i++)
    {
      cur->x=xPnts[i];
      cur->y=yPnts[i];
      cur->next=new bdry;
      cur->prev=prev;
      prev=cur;
      cur=cur->next;
    }
  delete cur;
  cur=prev;
  cur->next=bdryOrig;
  cur=cur->next;
  cur->prev=prev;

  domn=new domain;
  bdry *dup;
  dup=new bdry;
  makeCopy(bdryOrig,dup);
  //generate(&dup,dom);

  //The rest is verification. May be deleted later on after complete development.
  cur=bdryOrig;
  bdry *copy;
  std::ofstream F("actbor",std::ios::out);
  std::ofstream G("newbor",std::ios::out);
  std::ofstream H("point",std::ios::out);
  std::ofstream I("cover",std::ios::out);
  copy=new bdry;
  makeCopy(cur,copy);
  do
    {
      F<<cur->x<<" "<<cur->y<<std::endl;
      cur=cur->prev;
    }
  while(cur!=bdryOrig);
  std::cout<<"First\n";
  bdry *temp=copy;
  do
    {
      G<<temp->x<<" "<<temp->y<<std::endl;
      temp=temp->next;
    }
  while(temp!=copy);
  std::cout<<"Second\n";
  findHead(&copy);
  std::cout<<"Third\n";
  H<<copy->x<<" "<<copy->y<<std::endl;
  domain *dd;
  generate(&copy,domn);
  temp=copy;
  do
    {
      I<<temp->x<<" "<<temp->y<<std::endl;
      temp=temp->next;
    }
  while(temp!=copy);
  I<<temp->x<<" "<<temp->y<<std::endl;
  F.close();
  G.close();
  H.close();
  I.close();
}

void convex2D::findHead(bdry **orig)
{
  bdry *cur=*orig,*resetPoint;
  double minX=1.0e40;
  do
    {
      if(minX>cur->x){minX=cur->x;resetPoint=cur;}
      cur=cur->next;
    }
  while(cur!=*orig);
  *orig=resetPoint;
}

void convex2D::makeCopy(bdry *orig,bdry *copy)
{
  bdry *b=orig,*prev=NULL,*cur=copy;
  do
    {
      cur->x=b->x;
      cur->y=b->y;
      cur->prev=prev;
      prev=cur;
      if(b->next!=orig){cur->next=new bdry;cur=cur->next;}
      b=b->next;
    }
  while(b!=orig);
  cur->next=copy;
  copy->prev=prev;
}

void convex2D::generate(bdry **boun,convex2D::domain *dom)
{
  int cnt=0;
  bdry *pos0,*pos1,*pos2;
  double xp[2],yp[2];
  //cout<<"level 0\n";
  findHead(boun);
  pos0=*boun;
  pos1=pos0->next;
  pos2=pos1->next;
  do
    {
      xp[0]=pos1->x-pos0->x;
      yp[0]=pos1->y-pos0->y;
      xp[1]=pos2->x-pos1->x;
      yp[1]=pos2->y-pos1->y;
      if(isValidVertex(xp,yp))
	{
	  pos0=pos0->next;
	  pos1=pos0->next;
	  pos2=pos1->next;
	}
      else
	{
	  if(pos0==*boun)
	    {
	      pos0->next=pos2;
	      pos1->next=NULL;
	      pos1=pos2;
	      pos2=pos2->next;
	    }
	  else
	    {
	      pos1->next=NULL;
	      pos1=pos0;
	      pos1->next=pos2;
	      pos0=rewind(pos0);
	    }
	}
    }
  while(pos1!=*boun);
  dom->wrap=*boun;

  bdry *cur,*curprev,*temp,*prev,*start;
  domain *tmp;
  int count=0;

  //cout<<"level 1\n";
  cur=*boun;
  do
    {
      curprev=cur->prev;
      if(cur->next!=NULL && curprev->next==NULL)count++;
      cur=cur->prev;
    }
  while(cur!=*boun);
  dom->numDaug=count;
  dom->daughters=new domain[count];
  bdry **bList=new bdry*[count];
  //cout<<"count = "<<count<<endl;

  //return 0;

  //cout<<"level 2\n";
  bdry *toBeDel;
  int i;
  i=0;
  cur=*boun;
  do
    {
      curprev=cur->prev;
      if(cur->next!=NULL && curprev->next==NULL)
	{
	  //cout<<"kuku "<<i<<" "<<cur->x<<" "<<cur->y<<endl;
	  bList[i]=new bdry;
	  temp=bList[i++];
	  start=temp;
	  temp->x=cur->x;
	  temp->y=cur->y;
	  temp->prev=NULL;
	  temp->next=new bdry;
	  prev=temp;
	  temp=temp->next;
	  do
	    {
	      temp->prev=prev;
	      temp->x=curprev->x;
	      temp->y=curprev->y;
	      prev=temp;
	      temp->next=new bdry;
	      temp=temp->next;
	      toBeDel=curprev;
	      curprev=curprev->prev;
	      delete toBeDel;
	    }
	  while(curprev->next==NULL);
	  temp->prev=prev;
	  temp->x=curprev->x;
	  temp->y=curprev->y;
	  prev=temp;
	  temp->next=start;
	  start->prev=prev;
	  cur=curprev;
	  //cout<<"kuku "<<i<<" "<<cur->x<<" "<<cur->y<<endl;
	}
      else
	{
	  //cout<<"hiho "<<i<<" "<<cur->x<<" "<<cur->y<<endl;
	  cur=cur->prev;
	}
      //cout<<"gola\n";
    }
  while(cur!=*boun);

  // copy(bList[0],"first");
  // copy(bList[1],"secon");
  // copy(bList[2],"third");
  // copy(bList[3],"fourt");
  // copy(bList[4],"fifth");

  //return 0;

  //cout<<"level 3\n";
  for(i=0;i<count;i++)
    {
      // temp=bList[i];
      // do
      // 	{
      // 	  (temp->next)->prev=temp;
      // 	  temp=temp->next;
      // 	}
      // while(temp!=bList[i]);
      generate(bList+i,dom->daughters+i);
      //cout<<"vivivi "<<i<<"\n";
    }
  //generate(bList);
  makeSegments(dom);
}

bool convex2D::isValidVertex(double *xp,double *yp)
{
  double val=xp[0]*yp[1]-xp[1]*yp[0];
  if(val>-1.0e-14)//0.0) // add a tolerance later
    return(true);
  else
    return(false);
}

convex2D::bdry* convex2D::rewind(bdry *ver)
{
  bdry *cur=ver->prev;
  while(cur->next!=ver)
    {
      cur=cur->prev;
    }
  return(cur);
}

void convex2D::copy(bdry *b,std::string fil)
{
  std::fstream F(fil.c_str(),std::ios::out);
  bdry *cur=b;
  do
    {
      F<<cur->x<<" "<<cur->y<<std::endl;
      cur=cur->next;
    }
  while(cur!=b);
  F.close();
}

void convex2D::makeSegments(convex2D::domain *dom)
{
  bdry *cur=dom->wrap,*nxt;
  segChain *curSeg,*temp;
  double xp[2],yp[2];
  int count;

  std::cout<<"Making\n";

  dom->xcen=dom->ycen=0.0;
  count=0;
  dom->segm=new segChain;
  curSeg=dom->segm;
  do
    {
      count++;
      dom->xcen+=cur->x;
      dom->ycen+=cur->y;
      nxt=cur->next;
      xp[0]=cur->x;
      yp[0]=cur->y;
      xp[1]=nxt->x;
      yp[1]=nxt->y;
      curSeg->a=yp[0]-yp[1];
      curSeg->b=xp[1]-xp[0];
      curSeg->c=xp[0]*yp[1]-xp[1]*yp[0];
      curSeg->next=new segChain;
      temp=curSeg;
      curSeg=curSeg->next;
      cur=cur->next;
    }
  while(cur!=dom->wrap);
  dom->xcen/=count;
  dom->ycen/=count;
  delete curSeg;
  curSeg=temp;
  curSeg->next=NULL;

  curSeg=dom->segm;
  do
    {
      curSeg->val=curSeg->a*dom->xcen+curSeg->b*dom->ycen+curSeg->c;
      curSeg=curSeg->next;
    }
  while(curSeg!=NULL);
}

bool convex2D::contains(double x,double y,domain *dom)
{
  if(dom==NULL)dom=domn;
  double val;
  bdry *cur=dom->wrap;
  segChain *curSeg=dom->segm;
  do
    {
      val=curSeg->a*x+curSeg->b*y+curSeg->c;
      if(val*curSeg->val<=0)
	return(false);
      curSeg=curSeg->next;
    }
  while(curSeg!=NULL);
  if(dom->numDaug==0)return(true);
  int i;
  bool inDaugs=false;
  for(i=0;i<dom->numDaug;i++)
    inDaugs=inDaugs||contains(x,y,dom->daughters+i);
  return(!inDaugs);
}
