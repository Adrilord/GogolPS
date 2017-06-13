function [x,y,z] = ellipToCart(lambda,phi,h)
    a=6378137;
    b=6356752.314245179497563967;
    f=1/298.257223563;
    e=sqrt(2*f-f^2);
    N=a/(sqrt(1-(e^2)*(sin(phi)^2)));
    x = (N+h)* cos(phi) * cos(lambda);
    y = (N+h) * cos(phi) * sin(lambda);
    z = (N*(1-e^2)+h)*sin(phi);
end