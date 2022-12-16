function [compressed_data] = CMO_ProcessOnMatrix(matrix, filter)
%UNTITLED30 Summary of this function goes here
%   Detailed explanation goes here
compressed_data = cell(size(filter,1), 3)
min_max = filter{1,1};
times = filter{1,2};
for i = 2:size(filter, 1)
    min_max = cat(2, min_max, filter{i,1});
    times = cat(2, times, filter{i,2});
end
all_data = zeros(3, size(filter{1}, 2))
for i = 1:size(filter, 1)
    compressed_data{i, 1} = min(matrix(:, filter{1,1}))
    compressed_data{i, 2} = max(matrix(:, filter{1,1}))
    compressed_data{i, 3} = mean(diff(matrix(:, filter{1,2})))
    %begin and end comparetion
    
end