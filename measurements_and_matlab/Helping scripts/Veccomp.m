function [c] = Veccomp(A, B, t)
%UNTITLED10 Summary of this function goes here
%   Detailed explanation goes here
tmp2 = abs(A-B)<=t
sum(tmp2)
size(A,2)
if sum(tmp2) == size(A,2)
    c = 1;
else
    c = 0;
end

end

