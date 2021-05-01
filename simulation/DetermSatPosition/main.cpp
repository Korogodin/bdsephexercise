#include "UnitTest++.h"
#include "funct.h"
#include "ephemerids.h"
#include <iostream>
#include <math.h>

using namespace std;
const int nn =432001; //задаем n для массив
int main()
{

double* X = new double[nn];
double* Y = new double[nn];
double* Z = new double[nn];
double* Xmatlab = new double[nn];
double* Ymatlab = new double[nn];
double* Zmatlab = new double[nn];

parser(Xmatlab,Ymatlab,Zmatlab);
simul(X,Y,Z);


//cout <<Xmatlab[nn-1]<<endl;


//cout << X[1]<<endl;
double srdx=0;
double srdy=0;
double srdz=0;
double dxmax = 0;
double dymax = 0;
double dzmax = 0;
//cout<<X[0]<<"\t"<<Xmatlab[0]<<endl;
//cout<<X[nn]<<"\t"<<X[nn-1]<<"\t"<<X[nn-2]<<endl;
//cout<<X[nn-10]<<"\t"<<Xmatlab[nn-10]<<endl;
//printf("X=%12.12f , Xmatl =%12.12f ",X[nn-10],Xmatlab[nn-10]);
comparr(X,Y,Z, Xmatlab,Ymatlab,Zmatlab,nn-10, &srdx,&srdy,&srdz, &dxmax,&dymax,&dzmax );
delete[] X;
delete[] Y;
delete[] Z;
delete[] Xmatlab;
delete[] Ymatlab;
delete[] Zmatlab;

cout << "srdx="<<srdx<<endl;
cout << "srdy="<<srdy<<endl;
cout << "srdz="<<srdz<<endl;
cout << "dxmax="<<dxmax<<endl;
cout << "dymax="<<dymax<<endl;
cout << "dzmax="<<dzmax<<endl;


    return UnitTest::RunAllTests();
    }





