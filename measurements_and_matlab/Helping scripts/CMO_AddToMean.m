function [Mean] = CMO_AddToMean(Mean, N, New)
%UNTITLED18 Summary of this function goes here
%   Detailed explanation goes here
Mean = (Mean*N+New)/(N+1);
end