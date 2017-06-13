function [xl, yl, zl] = cartToLocal (x,y,z,lambda0,phi0)
    a=6378137;
    b=6356752.314245179497563967;
    f=1/298.257223563;
    e=sqrt(2*f-f^2);
    N0=a/(sqrt(1-(e^2)*(sin(phi0)^2)));
    Mat1=[-sin(lambda0), cos(lambda0), 0;
          -sin(phi0)*cos(lambda0), -sin(phi0)*sin(lambda0), cos(phi0);
          cos(phi0)*cos(lambda0), cos(phi0)*sin(lambda0), sin(phi0)];
	Mat2=[x - N0 * cos(phi0)*cos(lambda0);
        y - N0 * cos(phi0)*sin(lambda0);
        z - N0*(1-e^2)*sin(phi0)];
    result = Mat1*Mat2;
    xl=result(1);
    yl=result(2);
    zl=result(3);
end