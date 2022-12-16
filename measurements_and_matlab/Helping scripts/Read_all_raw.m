function [data] = Read_all_raw()
%UNTITLED6 Summary of this function goes here
%   Detailed explanation goes here
dd = dir('*.txt');

fileNames = {dd.name};
fileNames = natsortfiles(fileNames);

data = cell(numel(fileNames),2);
data(:,1) = regexprep(fileNames, '.txt','');

for ii = 1:numel(fileNames)    
   data{ii,2} = readmatrix(fileNames{ii});
end

end

