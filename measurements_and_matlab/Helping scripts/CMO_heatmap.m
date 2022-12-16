function [heat_map] = CMO_heatmap(data_list, num1, num2)
%UNTITLED16 Summary of this function goes here
%   Detailed explanation goes here

heat_map = zeros(size(data_list, 1), size(data_list{1,num1}, 2));
for i = 1:size(data_list, 1)
    heat_map(i, :) = data_list{i,num1}(num2, :);
end
end