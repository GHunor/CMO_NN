function [ListOfValues] = CMO_Domain_Shift_Corr(data_list1, data_list2)
%WIP Summary of this function goes here
%WOP WOP WOP
[pks1,locs1] = findpeaks(data_list1);
[pks2,locs2] = findpeaks(data_list1);
[R2, P2] = corrcoef(pks1, pks2);
spks1 = size(pks1,2)
ListOfValues{1} = spks1;
spks2 = size(pks2,2)
ListOfValues{2} = spks2;
diffmat1 = zeros(size(pks1,2));
for i = size(pks1,2)
    for j = size(pks1,2)
        diffmat(i,j) = pks1(i)-pks1(j);
    end
end
diffmat2 = zeros(size(pks2,2));
for i = size(pks2,2)
    for j = size(pks2,2)
        diffmat2(i,j) = pks2(i)-pks2(j);
    end
end


%corrcoef x
%get a and b
%corr to y
end