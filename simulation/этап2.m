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
t_start = (24*2 + 8 - 3)*60*60; % время старта 8:00 МСК 16 февраля
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
    coordX(k) = x * cos(lambda(k)) - y * cos(i(k)) * sin(lambda(k));
    coordY(k) = x * sin(lambda(k)) + y * cos(i(k)) * cos(lambda(k));
    coordZ(k) = y * sin(i(k));
end

%% построение графиков
R_Earth = 6371e3;
[XE,YE,ZE] = sphere(30);

figure
surf(XE*R_Earth,YE*R_Earth,ZE*R_Earth)
hold on
grid on
plot3(coordX, coordY, coordZ)
xlabel('X, m')
ylabel('Y, m')
zlabel('Z, m')


