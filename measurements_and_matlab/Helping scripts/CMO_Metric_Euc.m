function [Data] = CMO_Metric_Euc(dataC)
%CMO_Metric_Euc Euchlidian distance metric on the rows
%   Detailed explanation goes here
Data = dataC.*dataC;
Data = sum(Data, 2);
Data = sqrt(Data);
end