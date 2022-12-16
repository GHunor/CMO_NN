function [data_list, data_list2] = CMO_CROSS_con(data_list, data_list2)
%CMO_CROSS_con Correlation beetween each data in the OTHER list
%   Takes the lowest amount of channels from the bigger, does corrcoef with
%   that then means all of them (there is interference with the own
%   channels
if size(data_list,1) == 1
    data_list = data_list';
end
if size(data_list2,1) == 1
    data_list2 = data_list2';
end
new_data_place = size(data_list,2)+1;
new_data_place2 = size(data_list2,2)+1;

for i = 1:size(data_list,1)
    lengths(i) = size(data_list{i,1},1);
end

                                                    %com = mode(lengths);
data_list(:,new_data_place) = data_list(:,1);
data_list2(:,new_data_place2) = data_list2(:,1);

chanN = max(size(data_list{1,1},2),size(data_list2{1,1},2));
indexes = CMO_ConvIndList(size(data_list{1,1},2),size(data_list2{1,1},2));
                                                    %Rme = zeros(1,size(indexes,1))
                                                    %P_list = zeros(1,size(indexes,1))
for i = 1:size(data_list,1)
    data_list{i,new_data_place} = [];
    for j = 1:size(data_list2,1)
        if i == 1
            data_list2{j,new_data_place2} = [];
        end
                                                        %Temp = zeros(min( lengths(i), lengths(j) ), chanN)
                                                        %size(data_list{i,1}( 1:min( lengths(i), lengths(j) ), :))
        % !!should it be (N+M)x(N+M)
        for k = 1:size(indexes, 1)
            A = [data_list{i,1}( 1:min( lengths(i), lengths(j) ), indexes(k,:)), data_list2{j,1}(1:min( lengths(i), lengths(j) ), :)];
            [R,P] = corrcoef(A);
            if k == 1
                Rmean = CMO_upperTriangleMeanWD(R(size(data_list2{1,1},2)+1:2*size(data_list2{1,1},2),1:size(data_list2{1,1},2)));
                Pmean = CMO_upperTriangleMeanWD(P(size(data_list2{1,1},2)+1:2*size(data_list2{1,1},2),1:size(data_list2{1,1},2)));
            else
                Rmean = CMO_AddToMean(Rmean, k-1, CMO_upperTriangleMeanWD(R(size(data_list2{1,1},2)+1:2*size(data_list2{1,1},2),1:size(data_list2{1,1},2))));
                Pmean = CMO_AddToMean(Pmean, k-1, CMO_upperTriangleMeanWD(P(size(data_list2{1,1},2)+1:2*size(data_list2{1,1},2),1:size(data_list2{1,1},2))));
            end
        end
                                                        %A = [data_list{i,1}( 1:min( lengths(i), lengths(j) ), :), data_list2{j,1}(1:min( lengths(i), lengths(j) ), :)];
                                                        %B = CMO_PaddMat( data_list2{j,1}(1:min( lengths(i), lengths(j) ), :) , min( lengths(i), lengths(j)), chanN);
        [R,P] = corrcoef(A);
        data_list{i,new_data_place}(1,j) = CMO_upperTriangleMeanWD( R );
        data_list{i,new_data_place}(2,j) = CMO_upperTriangleMeanWD( P );
        data_list2{j,new_data_place2}(1,i) = data_list{i,new_data_place}(1,j);
        data_list2{j,new_data_place2}(2,i) = data_list{i,new_data_place}(2,j);
    end
end
end