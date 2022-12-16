function [progdata] = CMO_DELETE_EMPTY(progdata)
%Reconstructs ProdData without empty records
tmp = {};
j = 1;
for i = 1:size(progdata, 1)
    if isempty(progdata{i,5})
        continue;
    end
    tmp(j, :) = progdata(i,:);
    j = j + 1;
end
progdata = tmp;

%progdata{1,5} = progdata{1,5}(2:end,:);

end

