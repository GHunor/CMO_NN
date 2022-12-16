function [value] = CMO_upperTriangleMean(mat)
%Calculates the mean of the upper triangle
fmat = triu(mat);
fmat(fmat == 0) = nan;
value = mean(fmat, 'all', 'omitnan'); 
end