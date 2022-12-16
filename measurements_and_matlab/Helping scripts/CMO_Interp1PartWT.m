function [ndata] = CMO_Interp1PartWT(data, time, TSN, Ldata, Ltime,  method)
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