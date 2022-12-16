function [OP] = CMO_only_change_timestamp(data, Cind, Tind, Prev)
%CMO_only_change_timestamp Summary of this function goes here
%   Detailed explanation goes here
if nargin > 3
    OP = Prev;
    if sum(data(1, Cind)==OP(end, Cind))>0
        OP = [OP;data(1,:)];
    end
else
    OP = [data(1,:)];
end




for i = 2:size(data, 1)-1
    if sum(data(i, Cind)==data(i+1, Cind))>0
        OP = [OP;data(i+1,:)];
        OP(end-1, Tind) = data(i,Tind);
    end
end
OP(end-1, Tind) = data(end, Tind);
end