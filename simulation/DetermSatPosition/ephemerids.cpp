#include "ephemerids.h"
#include "Kepler.h"
#include <armadillo>

using namespace arma;

Coordinates CoordGPS(double t,
                     double toe,
                     double M0,
                    double  e,
                     double n,
                    double  a,
                    double  dn,
                    double  w,
                    double Cuc,
                   double Cus,
                   double Crc,
                   double Crs,
                   double Cic,
                   double Cis,
                   double i0,
                   double IDOT,
                  double  Omega0,
                  double  OmegaDot,
                   double omegaE )

{
 Coordinates CoordinatesGps;
double tk = t-toe;
 if (tk > 302400)
 {
 tk = 604800-tk;
 }
 else if (tk<-302400)
 {
 tk = 604800+tk;
 }

double  Mk = M0+( (sqrt(n/(pow(a,3)))) + dn)*tk;



double Ek = kepler(e,Mk);




double vk = atan2(sqrt(1-(pow(e,2)))*sin(Ek), (cos(Ek)-e) );
double uk = w+ vk + Cuc*cos(2*(w+vk))+Cus*sin(2*(w+vk));
double rk = (a*(1-e*cos(Ek)))+Crc*cos(2*(w+vk))+Crs*sin(2*(w+vk));
double ik = i0 + IDOT*tk+ Cic*cos(2*(w+vk))+Cis*sin(2*(w+vk));
double lymbdak_ECEF = Omega0 + (OmegaDot - omegaE)*tk-omegaE*toe;
dmat R1(3,3);
R1(0,0) = 1;
R1(0,1) = 0;
R1(0,2) = 0;
R1(1,0) = 0;
R1(1,1) =  cos(-ik);
R1(1,2) = sin(-ik);
R1(2,0) = 0;
R1(2,1)=-sin(-ik);
R1(2,2) = cos(-ik);
//R1 =[1 0 0;
 //   0 cos(-ik) sin(-ik);
 //   0 -sin(-ik) cos(-ik)];
dmat R3l_ECEF(3,3);
R3l_ECEF(0,0) = cos(-lymbdak_ECEF);
R3l_ECEF(0,1) = sin(-lymbdak_ECEF);
R3l_ECEF(0,2) = 0;
R3l_ECEF(1,0) = -sin(-lymbdak_ECEF);
R3l_ECEF(1,1) =  cos(-lymbdak_ECEF);
R3l_ECEF(1,2) = 0;
R3l_ECEF(2,0) = 0;
R3l_ECEF(2,1) = 0;
R3l_ECEF(2,2) = 1;
 //[cos(-lymbdak_ECEF) sin(-lymbdak_ECEF) 0;
 //   -sin(-lymbdak_ECEF) cos(-lymbdak_ECEF) 0;
  // 0 0 1];

dmat R3uk(3,3) ;
//[cos(-uk) sin(-uk) 0;
  //  -sin(-uk) cos(-uk) 0;
  //  0 0 1];
R3uk(0,0) = cos(-uk);
R3uk(0,1) = sin(-uk);
R3uk(0,2) = 0;
R3uk(1,0) = -sin(-uk);
R3uk(1,1) =  cos(-uk);
R3uk(1,2) = 0;
R3uk(2,0) = 0;
R3uk(2,1)=0;
R3uk(2,2) = 1;

dmat rkk(3,1);
rkk(0,0) = rk;
rkk(1,0) = 0;
rkk(2,0) = 0;

dmat coord = R3l_ECEF*R1*R3uk*rkk;
CoordinatesGps.X =  coord(0,0);
CoordinatesGps.Y = coord(1,0);
CoordinatesGps.Z = coord(2,0);
return CoordinatesGps;
}





















