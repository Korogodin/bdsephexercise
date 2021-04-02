close all; clear all; clc;
format long

%% Эфемериды
SatNum = 20;
toe = 226800000.000 * 10^-3;
Crs = -7.39218750000000000e+01;
Dn = 3.97195124013371981e-12;
M0 = 8.71704768059675339e-01;
Cuc = -3.64007428288459778e-06;
e = 6.97147799655795097e-04;
Cus = 5.95534220337867737e-06;
sqrtA = 5.28262682533264160e+03;
Cic = -7.49714672565460205e-08;
Omega0 = -2.82333800290329728e-01;
Cis = -6.84522092342376709e-08;
i0 = 9.65664043486355039e-01;
Crc = 2.44500000000000000e+02;
omega = -7.73836711576575076e-01;
OmegaDot = -7.00779190266137795e-12;
iDot = -1.97151069276238744e-13;
Tgd = 2.30000000000000000e+05;
toc = 2.26800000000000000e+08;
af2 = 0.00000000000000000e+00;
af1 = -4.24460466774689849e-12;
af0 = -9.16242361068725586e-01;
URA = 0;
IODE = 257;
IODC = 1;
codeL2 = 0;
L2P = 0;
WN = 789;

%% Константы
mu = 3.986004418e14;    % гравитационная постоянная
OmegaE = 7.2921151467e-5;   % скорость вращения

%% Расчет
t_start = (24*2 + 18 - 3)*60*60; % время старта 18:00 МСК 16 февраля
t_stop = (24*3 + 6 - 3)*60*60; % время окончания 6:00 МСК 17 февраля

% Массив времени
t_arr = t_start:1:t_stop;

% Большая полуось
A = sqrtA^2;

% Среднее движение
n0 = sqrt(mu/A^3);
n = n0 + Dn;

for k = 1:length(t_arr)
    % Время
    t(k) = t_arr(k) - toe;
    
    if t(k) > 302400
        t(k) = t(k) - 604800;
    end
    if t(k) < -302400
        t(k) = t(k) + 604800;
    end
    
    % Средняя аномалия
    M(k) = M0 + n*t(k);
    
    % Решение уравнения Кеплера
    E(k) = M(k);
    E_old(k) = M(k)+1;
    epsilon = 1e-6;
    
    while abs(E(k) - E_old(k)) > epsilon
        E_old(k) = E(k);
        E(k) = M(k) + e*sin(E(k));
    end
    
    % Истинная аномалия
    nu(k) = atan2( sqrt(1 - e^2) * sin(E(k)) , cos(E(k)) - e );
    
    % Коэффициенты коррекции
    cor_cos(k) = cos(2*(omega + nu(k)));
    cor_sin(k) = sin(2*(omega + nu(k)));
    
    % Аргумент широты
    u(k) = omega + nu(k) + Cuc*cor_cos(k) + Cus*cor_sin(k);
    
    % Радиус
    r(k) = A * (1 - e * cos(E(k))) + Crc*cor_cos(k) + Crs*cor_sin(k);
    
    % Наклон
    i(k) = i0 + iDot * t(k) + Cic*cor_cos(k) + Cis*cor_sin(k);
    
    % Долгота восходящего угла
    lambda(k) = Omega0 + (OmegaDot - OmegaE) * t(k) - OmegaE*toe;
    
    % Положение на орбите
    x = r(k) * cos(u(k));
    y = r(k) * sin(u(k));
    
    % Координаты
    X0(k) = x * cos(lambda(k)) - y * cos(i(k)) * sin(lambda(k));
    Y0(k) = x * sin(lambda(k)) + y * cos(i(k)) * cos(lambda(k));
    Z0(k) = y * sin(i(k));
    
    % Пересчет в инерциальную СК
    X(k) = X0(k) * cos(lambda(k)) + Y0(k) * sin(lambda(k));
    Y(k) = -X0(k) * sin(lambda(k)) + Y0(k) * cos(lambda(k));
    Z(k) = Z0(k);
end

%% Пересчет координат центра масс НКА в систему координат WGS-84
ppb = 1e-9;
mas = 1e-3/206264.8; % [рад]

MATRIX_WGS_84 = [-3*ppb -353*mas -4*mas;
    353*mas -3*ppb 19*mas;
    4*mas -19*mas -3*ppb];

crd_WGS_84 = [X0; Y0; Z0];

for i = 1:length(crd_WGS_84(1,:))
    crd_WGS_84(:,i) =  crd_WGS_84(:,i) + MATRIX_WGS_84 * crd_WGS_84(:,i) + [0.07; -0; -0.77];
end

crd_WGS_84 = crd_WGS_84.'; % Переход к вектору-строки

%% построение графиков
R_Earth = 6371e3;
[XE,YE,ZE] = sphere(30);

figure
surf(XE*R_Earth,YE*R_Earth,ZE*R_Earth)
hold on
grid on
plot3(crd_WGS_84(:,1), crd_WGS_84(:,2), crd_WGS_84(:,3))
plot3(X, Y, Z)
title('Траектория движения спутника', 'FontName', 'Arial')
xlabel('X, м', 'FontName', 'Arial')
ylabel('Y, м', 'FontName', 'Arial')
zlabel('Z, м', 'FontName', 'Arial')
hold off
lgd = legend('Земля','СК ECEF WGS84','Инерциальная СК');
lgd.FontName = 'Arial';


%% Географические координаты корпуса Е и их перевод в систему WGS-84
% Lantitude
N_gr = 55;
N_min = 45;
N_sec = 23.8178;
N = N_gr*pi/180 + N_min/3437.747 + N_sec/206264.8; % широта [рад]

% Longtitude
E_gr = 37;
E_min = 42;
E_sec = 12.2608;
E = E_gr*pi/180 + E_min/3437.747 + E_sec/206264.8; % долгота [рад]

H = 500; % высота [м]

llh = [N E H];
crd_PRM = llh2xyz(llh)';


%% Постороение SkyPlot
for i = 1:length(crd_WGS_84(:,1))
    
    [X(i) Y(i) Z(i)] = ecef2enu(crd_WGS_84(i,1),crd_WGS_84(i,2),crd_WGS_84(i,3),N,E,H,wgs84Ellipsoid,'radians');
    if Z(i) > 0
        r(i) = sqrt(X(i)^2 + Y(i)^2 + Z(i)^2);
        teta(i) = acos(Z(i)/r(i));
        if X(i) > 0
            phi(i) = -atan(Y(i)/X(i))+pi/2;
        elseif (X(i)<0)&&(Y(i)>0)
            phi(i) = -atan(Y(i)/X(i))+3*pi/2;
        elseif (X(i)<0)&&(Y(i)<0)
            phi(i) = -atan(Y(i)/X(i))-pi/2;
        end
    else teta(i) = NaN;
        r(i) = NaN;
        phi(i) = NaN;
    end
end

% Скайплот
figure
ax = polaraxes;
polarplot(ax,phi,teta*180/pi)
ax.ThetaDir = 'clockwise';
ax.ThetaZeroLocation = 'top';
title('SkyView')

% Угол места
th = hours(t_arr/60/60 - 2*24); % Перевод временной оси в формат hh:mm:ss
figure
grid on
hold on
plot(th,(-teta)*180/pi+90,'DurationTickFormat','hh:mm:ss')
xlim([th(1) th(end)])
title('Угол места', 'FontName', 'Arial')
xlabel('Время в UTC', 'FontName', 'Arial')
ylabel('Угол места, град', 'FontName', 'Arial')


%% Функции
function ret = R1(teta)
ret = [1 0 0;
    0 cos(teta) sin(teta);
    0 -sin(teta) cos(teta)];
end

function ret = R2(teta)
ret = [cos(teta) 0 -sin(teta);
    0 1 0;
    sin(teta) 0 cos(teta)];
end

function ret = R3(teta)
ret = [cos(teta) sin(teta) 0;
    -sin(teta) cos(teta) 0;
    0 0 1];
end
