function [] = CMO_WriteMatrix(data, access ,filename, guide)
%UNFINISHED Writes files (can do multiple)
%   Detailed explanation goes here
if argin<4
    writematrix(data,join([access, filename]) );
    return
end
if guide == 'seperate'
    for i = 1:size(filename, 1)
        writematrix(data(i, :),join([access,filename(i)]) )
    end
end