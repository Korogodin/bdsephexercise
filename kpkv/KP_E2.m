close all;
clear all;
format long;
 
Toe = 284400;
Crs = 1.16406250000000000e+01;
mu = 3.986004418e+14;
dn = 1.98079681996976564e-12;
Cuc = 2.35158950090408325e-07;
e = 8.14774842001497746e-03;
Cus = -2.74321064352989197e-06;
A = 6.49292568778991699e+03^2;
Cic = -2.70549207925796509e-07;
Wo = 2.63970155955976082e+00;
Cis = -1.37835741043090820E-07;
Io = 8.91248838651520714e-01;
Crc = 3.05328125000000000e+02;
Mo = -2.45617118216572505e+00;
We = 7.2921150e-5;
W = -2.52291283308052350e+00;
Wdot = -2.82868925483299065e-12;
idot = -2.30009580822278564e-13;
T = ((24*2+15)*3600:1:(24*3+3)*3600);

wur = 55.45235679;
dl = 37.42120145;
H = 200;
no = sqrt(mu/(A^3));
n=no+dn;
 
for j=1:length(T);
Tk(j)=T(j)-Toe;
if Tk(j)>302400
    Tk(j) = Tk(j)-604800;
end
if Tk(j)<-302400
    Tk(j) = Tk(j)+604800;
end
M(j) = Mo+n*Tk(j);
E(j)=M(j);
Epre(j) = M(j)+1;
Ost = 1e-7;
while abs(E(j)-Epre(j))>Ost
Epre(j) = E(j);
E(j)=M(j)+e*sin(Epre(j));
end
nu(j) = atan2(sqrt(1-e^2)*sin(E(j)),cos(E(j))-e);
% C_c(j) = cos(2*(omega+nu(j)));
% C_s(j) = sin(2*(omega+nu(j)));
F1(j) = nu(j)+W;
du(j) = Cus*sin(2*F1(j))+Cuc*cos(2*F1(j));
dr(j) = Crs*sin(2*F1(j))+Crc*cos(2*F1(j));
di(j) = Cis*sin(2*F1(j))+Cic*cos(2*F1(j));
F2(j) = F1(j)+du(j);
r(j) = A*(1-e*cos(E(j)))+dr(j);
i(j) = Io+di(j)+idot*Tk(j);
poX(j) = r(j)*cos(F2(j));
poY(j) = r(j)*sin(F2(j));
Omega(j) = Wo+(Wdot-We)*(Tk(j))-We*Toe;
x(j) = poX(j)*cos(Omega(j))-poY(j)*cos(i(j))*sin(Omega(j));
y(j) = poX(j)*sin(Omega(j))+poY(j)*cos(i(j))*cos(Omega(j));
z(j) = poY(j)*sin(i(j)); 
Resfix(j,:) = [x(j) y(j) z(j)];
phi(j) = We*Tk(j); 
xc(j) = x(j)*cos(phi(j))-y(j)*sin(phi(j));
yc(j) = x(j)*sin(phi(j))+y(j)*cos(phi(j));
zc(j) = z(j); 
ResECI(j,:)=[xc(j) yc(j) zc(j)]; 
% T=T+1;
end

% [X, Y, Z] = sphere(10);
% figure;plot3(Resfix(:,1),Resfix(:,2),Resfix(:,3));
% hold on;
% surf(X*6.371*10^6, Y*6.371*10^6, Z*6.371*10^6);
% grid on;
% xlabel('X,ì');
% ylabel('Y,ì');
% zlabel('Z,ì');
% figure; plot3(ResECI(:,1),ResECI(:,2),ResECI(:,3));
% hold on;
% surf(X*6.371*10^6, Y*6.371*10^6, Z*6.371*10^6);
% grid on;
% xlabel('X,ì');
% ylabel('Y,ì');
% zlabel('Z,ì');
% s = 1;
%  
% for y = 1:length(el);
%  if el(y) <= 90;
%     Cel(s) = el(y);
%     Caz(s) = az(y);
%     s = s+1;
%  end
% end
%  
% figure;
% polar(2*pi-Caz, Cel); 
% camroll(90);

fid = fopen('matlab.txt', 'w+'); 
for i = 1:length(Resfix(:,1)) 
fprintf(fid,'%.6f\t%.7f\t%.6f\n',Resfix(i,1), Resfix(i,2), Resfix(i,3)); 
end 
fclose(fid);