function [L] = CMO_SimplePInHBCheck(point, Mins, Maxs)
%UNTITLED7 Summary of this function goes here
%   Detailed explanation goes here
if sum(Mins<=point & point<=Maxs) == length(point)
    L = true;
    return;
end
L = false;
return;
end