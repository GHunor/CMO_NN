function [mat] = CMO_PaddMat(mat, n, m)
%CMO_PaddMat Resizes a matrix by padding with zeros
%   Detailed explanation goes here
[s1,s2] = size(mat);
ds1 = n-s1;
ds2 = m-s2;
P1 = zeros(s1, ds2);
P2 = zeros(ds1, s2);
P3 = zeros(ds1,ds2);
mat = [mat,P1;P2,P3];
end