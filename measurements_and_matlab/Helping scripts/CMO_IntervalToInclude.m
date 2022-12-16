function [IncMat] = CMO_IntervalToInclude(Time_Row, IntervalMat)
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
IncMat = zeros(size(Time_Row,1),1);
    for j = 1:size(IntervalMat,1)
        LI = Time_Row>=IntervalMat(j,1);
        LI2 = Time_Row<=IntervalMat(j,2);
        LI = LI & LI2;
        IncMat = IncMat + LI;
    end
end