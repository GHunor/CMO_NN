function [value] = CMO_upperTriangleMeanWD(mat)
%Calculates the mean of the upper triangle (without the diagonal)
Tmat = triu(mat);
dmat = diag(diag(triu(mat)));
fmat = Tmat - dmat;
fmat(fmat == 0) = nan;
value = mean(fmat, 'all', 'omitnan'); 

end