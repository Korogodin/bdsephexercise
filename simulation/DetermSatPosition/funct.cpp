
#include <armadillo>
#include "funct.h"
#include "ephemerids.h"
#include <iostream>
#include <math.h>

using namespace std;


void simul(double *X,double *Y,double *Z)
{

  long double  tstart = (24*2 + 18 - 3)*60*60;
  long double tstop = (24*3 + 6 - 3)*60*60;
  double a=pow(5.28261434555053711e+03,2);
  double toe = 223200000.000e-3; //ms
  double  M0 =1.40953592060026917e-01 ;
  double dn = (4.35125286496473862e-12)/(pow(10,-3)); //rad/ms
  double w= 5.72152208390331540e-01;
  double Cuc =5.78071922063827515e-06;
  double Crc =2.34390625000000000e+02;
  double Crs = 6.56093750000000000e+01;
  double Cic =2.32830643653869629e-09;
  double Cis =-6.56582415103912354e-08;
  double Cus =5.78071922063827515e-06;
  double i0 = 9.49918991207442720e-01;
  double IDOT =1.51077721564943834e-13;
  double Omega0 =1.82433512285772315e+00;
  double OmegaDot = -7.16708425211283236e-12;
  double e= 7.20643904060125351e-04;
  double n = 3.986004418e+14;
  double OMEGA_e = 7.2921151467*pow(10,-5);
  double omegaE=OMEGA_e;
  ofstream f;
  f.open("testCoord.txt");
  f<<"tstart"<<tstart<<endl;

  int k=0;
  for ( long double i = tstart; i<=tstop; i+=0.1)
  {
// printf("i%12.12lf \n  ",i);
    Coordinates coord = CoordGPS( i,
                                  toe,
                                  M0,
                                  e,
                                  n,
                                  a,
                                  dn,
                                  w,
                                  Cuc,
                                  Cus,
                                  Crc,
                                  Crs,
                                  Cic,
                                  Cis,
                                  i0,
                                  IDOT,
                                  Omega0,
                                  OmegaDot,
                                  omegaE );

    X[k] = coord.X;
    Y[k] = coord.Y;
    Z[k] = coord.Z;
    k++;
    f<<"tstart+i"<<i<<"\t" <<"X="<< coord.X<< "\t";
    f<< "Y="<< coord.Y<<"\t";
    f<< "Z="<< coord.Z<<endl;

  }
  f.close();

}
void parser(double *Xmatlab,double *Ymatlab,double *Zmatlab )
{
// cout<< "parser"<<endl;
  FILE *fd;
  fd = fopen("cord.txt", "r");

  int i=0;
  while ( !feof(fd) )
  {
    fscanf(fd, "%lf", &( Xmatlab[i]));
    fscanf(fd, "%lf", &( Ymatlab[i]));
    fscanf(fd, "%lf", &( Zmatlab[i]));
    i++;
  }

}
void comparr(double* X, double* Y, double* Z,double* X2, double* Y2, double* Z2, double nnn, double *srdx, double *srdy, double *srdz,
             double *dxmax, double *dymax,double *dzmax)
{
  // cout<< "comparr"<<endl;
  double sumdx = 0;
  double sumdy = 0;
  double sumdz = 0;
  int n = nnn;
  double* dx= new double[n];
  double* dy= new double[n];
  double* dz= new double[n];
  //int* wcompar;
  // wcompar = new int[nn];

  for (int i = 0; i < nnn; i++)
  {
    dx[i] = (fabs(X[i]-X2[i]));
    dy[i] = (fabs(X[i]-X2[i]));
    dz[i] = (fabs(X[i]-X2[i]));
    sumdx +=dx[i];
    sumdy +=dy[i];
    sumdz +=dz[i];
    //найдем макс значение
    if (dx[i] > dx[i-1])
    {
      *dxmax = dx[i];
    }
    if (dy[i] > dy[i-1])
    {
      *dymax = dy[i];
    }
    if (dz[i] > dz[i-1])
    {
      *dzmax = dz[i];
    }
  }
  *srdx = sumdx/nnn;
  *srdy = sumdy/nnn;
  *srdz = sumdz/nnn;
  delete[] dx;
  delete[] dy;
  delete[] dz;

}

