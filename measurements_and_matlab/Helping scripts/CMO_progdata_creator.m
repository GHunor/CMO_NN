function [measurements] = CMO_progdata_creator(directory, measurements, filter)
%UNTITLED29 Summary of this function goes here
%   Detailed explanation goes here

%needs to run through all the files, get mins and maxes, average time difference, sort files into chunks that can be read two at the time and resceduled
measurements_new = cell(size(measurements));
progdatas = {};
for i = 1:size(measurements, 1)
    fill = cell(1,2);
    fillsize = 0
    for j = 1:size(measurements{i,2},1)
        %measurements_new{i,3}{j} = measurements{i,2}{j};
        temp = readmatrix(join([directory,measurements{i,2}{j}]));
        for k = 1:size(filter,1)
            measurements{i,2}{j,2}{k,1} = min(temp(filter{1,1}));
            measurements{i,2}{j,2}{k,2} = max(temp(filter{1,1}));
            measurements{i,2}{j,2}{k,3} = min(temp(filter{1,2}));
            measurements{i,2}{j,2}{k,4} = mode(diff(temp(filter{1,2})));
            %
        end

        end
    end
end
end