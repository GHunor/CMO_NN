function [Data] = CMO_Metric_Man(dataC)
%CMO_Metric_Man Manhatten distance metric on the rows
%   Detailed explanation goes here
Data = abs(dataC);
Data = sum(Data, 1);
end