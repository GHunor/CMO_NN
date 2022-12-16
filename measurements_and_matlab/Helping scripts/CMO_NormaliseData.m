function [data] = CMO_NormaliseData(data,MinMax)
%UNFINISHED Columns of data with time stamps in the first coloumn, using the MinMax it normalises the remaining columns between 0-1
%   Detailed explanation goes here
data(:, 2:end) = (data(:, 2:end)-MinMax(1,:))./(MinMax(2,:)-MinMax(1,:));
end

function [data] = CMO_NormaliseDataMult(data,MinMax)
%UNFINISHED 3D Columns of data with time stamps in the first coloumn, using the MinMax it normalises the remaining columns between 0-1
%   Detailed explanation goes here
for i = 1;size(data, 1)
    data(i, :, 2:end) = (data(i, :, 2:end)-MinMax(i, 1,:))./(MinMax(i, 2,:)-MinMax(i, 1,:));
end