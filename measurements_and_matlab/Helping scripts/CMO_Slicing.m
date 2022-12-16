function [list] = CMO_Slicing(data, dataT, Intervals)
%UNFINISHED This function slices out part of the data where the time was in one of the intervals
%   Detailed explanation goes here
list = {};
for i = 1:size(Intervals,1)
    LI = dataT>=Intervals(i,1);
    LI2 = dataT<=Intervals(i,2);
    LI = LI & LI2;
    list{i} = [dataT(LI),data(LI, :)];
end
end