function [TRP] = CMO_Test_BreakerE(Time_Row, Data, Part_Length)
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
L = length(Time_Row);
if size(Time_Row, 2) == L
    Time_Row = Time_Row';
end
if size(Data, 2) == L
    Data = Data';
end
Parts = 1:Part_Length:L;
Parts = [Parts,L];
TRP = {};
for i = 2:size(Parts, 2)

    TRP{i-1} = [Time_Row(Parts(i-1):Parts(i)-1), ...
        Data(Parts(i-1):Parts(i)-1, :)];
end
end