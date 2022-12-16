function [dist_map] = CMO_DistMapBasic(data_list_cont, filt)
%CMO_DistMapBasic( Summary of this function goes here creates a matrix with the distances between each dataline

L = size(data_list_cont, 1);
dist_map = zeros(L)

for i = 1:L
    dist_map(i,:) = sqrt(sum((data_list_cont(:, filt) - data_list_cont(ones(1,L)*i, filt)).^2, 2));
end
end