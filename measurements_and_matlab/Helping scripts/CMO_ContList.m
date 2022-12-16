function [continous_list] = CMO_ContList(progdata)
%CMO_ContList Concats progdatas into one continous array and a second array for sizes
% WIP WIP
continous_list = cell(1,2);
continous_list{1} = zeros(size(progdata{1,3}));
continous_list{2} = [];
temp = 0;
for i = 1:size(progdata, 1)
    continous_list{1}(temp+1:temp+size(progdata{i,3}, 1), :) = progdata{i,3};
    continous_list{2}(i) = size(progdata{i,3}, 1);
end
end