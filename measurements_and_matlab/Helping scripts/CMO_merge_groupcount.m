function [uGN] = CMO_merge_groupcount(G1,G2)
%CMO_merge_groupcount merges two groupcount where (the type of data | amount
%   Detailed explanation goes here

G1n = G1(:,1);
G2n= G2(:,1);
GN = [G1n;G2n];
uGN = unique(GN);
for i = 1:size(uGN,1)
    V1 = sum(G1(G1n==uGN(i),2));
    V2 = sum(G2(G2n==uGN(i),2));
    uGN(i,2) = V1 + V2;
end
end