function [IntervalMat] = CMO_IntervalFromDetect(Time_Row, LogIndexes, PreT, Bigst)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here

%should be cut?
%LogIndexes =  LogIndexes(2:end);
LogIndexes = LogIndexes ==1;
R1 = Time_Row(LogIndexes);
R2 = Time_Row([LogIndexes(2:end);false], 1);
if size(R2,1)==0 || size(R1, 1)==0
    if size(R1, 1)==0
        IntervalMat = [Time_Row(1), Bigst];
    else
        IntervalMat = [R1(1), Bigst];
    end
elseif size(R1, 1) == 1 || size(R2, 1) == 1
    if R1(1)>R2(1)
        IntervalMat = [PreT, R2(1)];
        IntervalMat = [IntervalMat;[R1(1), Bigst]];
    else
        R1
        R2
        IntervalMat = [R1(1:end-1),R2];
        IntervalMat = [IntervalMat;[R1(end), Bigst]];
    end
elseif R1(1)>R2(1)
    IntervalMat = [PreT, R2(1)];
    IntervalMat = [IntervalMat;[R1(1:end-1),R2(2:end)]];
    IntervalMat = [IntervalMat;[R1(end), Bigst]];
else
    IntervalMat = [R1(1:end-1),R2];
    IntervalMat = [IntervalMat;[R1(end), Bigst]];
end
end