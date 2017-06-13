function [lambda,phi,h] = cartToEllip(x,y,z)
    a=6378137;
    b=6356752.314245179497563967;
    f=1/298.257223563;
    e=sqrt(2*f-f^2);
    lambda = atan(y/x);
    h=0;
    N=a;
    p=sqrt(x^2+y^2);
    stop=0;
    while(stop==0)
        sinphi=z/(N*(1-e^2)+h);
        phi=atan((z+(e^2)*N*sinphi)/p);
        N=a/(sqrt(1-(e^2)*(sin(phi)^2)));
        hbis=(p/cos(phi)) -N;
        if(norm(hbis-h) <= 10^-7)
            stop=1;
        else
            h=hbis;
        end
    end
end