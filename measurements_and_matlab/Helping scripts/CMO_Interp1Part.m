function [ndata, ntime] = CMO_Interp1Part(data, time, fs, Ldata, Ltime,  method)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
if nargin < 6
     method = "linear";
 end
if nargin < 4
     Ldata = data(1, :);
     data = data(2:end, :);
     LdataT = dataT(1);
     dataT = dataT(2:end);
end
DS = [Ldata;data];
TS = [Ltime;time];
Min = min(TS);
Max = max(TS);
T = 1/fs;%*1000; %in milisecond
%N = round((Max-Min)/T)
TSN = Min:T:Max;
%TSN = TSN'/N * (Max-Min) + Min
%TSN
if unique(TSN)~=TSN
    display('TSN recurring character')
    TSN
end
if sort(TSN)~=TSN
    display('TSN not sorted')
    TSN
end

if length(unique(TS))~=length(TS)
    display('TS recurring character')
    TS
end
if sort(TS)~=TS
    display('TS not sorted')
    TS
end
for i = 1:size(DS,2)
    RSdata(:,i) = interp1(TS, DS(:,i),  TSN, method);
end
ntime = TSN;
ndata = RSdata;
end