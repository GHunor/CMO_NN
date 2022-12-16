function [new_data] = Continous_measurements(data)
%UNTITLED7 Summary of this function goes here
%   Detailed explanation goes here
n2data = split(data(:,1),'__');
k = strfind(n2data(:,1),'_'); 
number = str2num(n2data{:,1}(k(:,end):end));
ndata = split(ndata(:,1),'_');
names = unique(ndata(:,1));
end

