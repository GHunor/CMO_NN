function [L] = CMO_HitboxOverlap(hitB1,hitB2)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
if hitB1.dim ~= hitB2.dim
    display('not equal dimensions');
end
NPoint = hitB1.cp./hitB2.lens-hitB2.mins;
L = hitB2.IsIn(Npoint);

end