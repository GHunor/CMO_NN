function [data_list] = CMO_SelfCon(data_list)
%CMO_SelfCon Correlation beetween each data in the list
%   Detailed explanation goes here
if size(data_list,1) == 1
    data_list = data_list';
end
new_data_place = size(data_list,2)+1;
for i = 1:size(data_list,1)
    lengths(i) = size(data_list{i,1},1);
end
%com = mode(lengths);
data_list(:,new_data_place) = data_list(:,1);
for i = 1:size(data_list,1)
    data_list{i,new_data_place} = [];
    for j = 1:size(data_list,1)
        %size(data_list{i,1}( 1:min( lengths(i), lengths(j) ), :))
        [R,P] =  corrcoef( data_list{i,1}( 1:min( lengths(i), lengths(j) ), ...
                                           :), ...
                           data_list{j,1}(1:min( lengths(i), lengths(j) ), ...
                                           :) );
        data_list{i,new_data_place}(1,j) = CMO_upperTriangleMeanWD( R);
        data_list{i,new_data_place}(2,j) = CMO_upperTriangleMeanWD( P);
    end
end
end