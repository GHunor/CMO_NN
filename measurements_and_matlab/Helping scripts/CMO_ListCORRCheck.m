function [ret] = CMO_ListCORRCheck(List, method)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
if nargin < 2
    method = 'mean';
end
if strcmp(method,'mean')
    Mean = @(x, l) (mean(x,'all'));
end
if strcmp(method,'weightedmean')
    Mean = @(x, l) ( ...
                    sum(x.*l, 'all') / (sum( ones(length(x), 1).*l, 'all') ) ...
                    );
end
if strcmp(method,'minWmean')
    Mean = @(x, l) ( ...
                    sum( x.*(l/min(l)), 'all') / (sum( ones(length(x), 1).*(l/min(l)), 'all') ) ...
                    );
end
x = [];
l = [];
for i = 1: length(List)
    T = corrcoef(List{i}(:,1), List{i}(:,2));
    
    if size(T) == [1,1]
        %display('===============')
        %display('T is 1x1')
        %display('===============')
        continue
    end
    if isnan(T(1,2))
        %display('===============')
        %display('T is nan')
        %display('===============')
        continue
    end
    x = [x; T(1,2)];
    l = size(List{i}, 1);
end
ret = Mean(x, l);
if isnan(ret)
    %display('===============')
    display('ret is nan')
    %ret = 0;

    %display('===============')
end
end