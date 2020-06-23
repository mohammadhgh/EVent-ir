plotCount = 1;
%for a=0:0.22:0.66;
a=0;
resolution = 20;
deltaDegree = 20;
easeInFactor  = a;
easeOutFactor = a;

x0=0;

x1=deltaDegree*(easeInFactor);
x2=deltaDegree*(1-easeOutFactor);
x3=x0+deltaDegree;

cx = 3  * (x1 - x0);
bx = 3  * (x2 - x1) - cx;
ax = x3 -  x0 - cx  - bx;

t=0:1/resolution:1;

x = ax*t.^3 + bx*t.^2 + cx*t + x0;
% x = (1 - t).^3 .* x0 + 3 .* (1 - t).^2 .* t .* x1 + 3 .* (1 - t) .* t.^2 .* x2 + t.^3 .*x3;
subplot(2,2,plotCount);
plotCount= plotCount+1;
plot(t,x)
%end
