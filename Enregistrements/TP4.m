clear all, clc, close all;
%tests
M=[degDectoRad(4);degDectoRad(20);200]; %ellip
phi0=degDectoRad(degSexaToDegDec(4, 20, 20));
lambda0=degDectoRad(degSexaToDegDec(4, 20, 20));
M0=[lambda0; phi0; 0]; %ellip
[m1,m2,m3]=ellipToCart(M(1),M(2),M(3));
M1=[m1; m2; m3];
[m1,m2,m3]=cartToLocal(M1(1), M1(2), M1(3), lambda0, phi0);
M2=[m1,m2,m3];

[m1,m2,m3]=cartToEllip(M1(1),M1(2),M1(3));
Mverif1 = [m1,m2,m3]; %equal to M
[m1,m2,m3]=localToCart(M2(1), M2(2), M2(3), lambda0, phi0);
Mverif2=[m1,m2,m3]; % equal to M1