function [TSN] = CMO_FixPointTSNGen(point, Min, Max, T)
%UNTITLED8 Summary of this function goes here
%   Detailed explanation goes here
TSN = point:T:Max;
H1 = point:-T:Min;
TSN = [flip(H1),TSN(2:end)];
end