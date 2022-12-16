function [dataline] = CMO_OneSensorData(data, time, channels)
%CMO_OneSensorData Cuts the data of a sensor out
%   Detailed explanation goes here
    dataline = data(:, [time, channels])
end