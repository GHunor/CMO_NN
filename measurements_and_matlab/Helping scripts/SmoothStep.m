function [y] = SmoothStep(x, x1, x2, y1, y2)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
x = (x-x1)/(x2-x1);
y = (3-2*x)*x*x;
if y1>y2
    y = -y+1;
    y = y*(y1-y2)+y2;
    return
end
y = y*(y2-y1)+y1;
end