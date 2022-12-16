function [ReadRow] = CMO_Test_SerialPortSim(ComRate, ReadRate, BuffSiz, ComRow, ReadAm)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here


ComRate = 10
ReadRate = 75
BuffSiz = 1000

Parts = 0:BuffSiz:size(ComRow, 1);
Parts = [Parts, size(ComRow, 1)];
Parts = Parts+1;
BuffSizs = diff(Parts);
BuffTimes = BuffSizs*ComRate;

Buffers = {};

for i = 2:size(Parts, 2)
    Buffers{i-1} = [ComRow( Parts(i-1):Parts(i)-1, : )];
end

RRes = 0;
ReadRow = [];
for i = 1:size(BuffTimes, 2)
    RA = floor((RRes+BuffTimes(i))/ReadRate);
    ReadRow = [ReadRow; Buffers{i}(1:RA, :)];
    RRes = mod((RRes+BuffTimes(i)),ReadRate);
end
if nargin < 5
    return
end
ReadRow = ReadRow(1:ReadAm, :);
end