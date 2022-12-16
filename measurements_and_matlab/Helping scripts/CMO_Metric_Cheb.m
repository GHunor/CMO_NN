function [Data] = CMO_Metric_Cheb(dataC)
%CMO_Metric_Cheb Chebishev distance metric on the rows
%   Detailed explanation goes here
Data = abs(dataC);
Data = max(Data, [], 2);
end