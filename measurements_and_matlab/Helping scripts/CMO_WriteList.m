function [] = CMO_WriteList(list, direc, name, init)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
for i = 1:length(list)
    txt = join([direc, '/', name, '_', '%d.csv']);
    txt = sprintf(txt, init+i);
    writematrix(list{i}, txt);
end
end