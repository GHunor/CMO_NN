function [mms] = Create_MinMaxArray(inar)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here
mms = zeros(2,size(inar, 2));
mms(1,:) = min(inar,2);
mms(2,:) = max(inar,2);
end
