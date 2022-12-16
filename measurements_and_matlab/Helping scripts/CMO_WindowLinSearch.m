function [OMAT,OLIST] = CMO_WindowLinSearch(mat1,mat2)
%CMO_WindowLinSearch By two matrix, it moves the two to cover eachother and
%divides the elements with eachother. Gives back a cell aray with the new
%matrixes, and a tensor with mean and standart diviation
%   Detailed explanation goes here
N = max(size(mat1, 1), size(mat2, 1));
n = min(size(mat1, 1), size(mat2, 1));
M = max(size(mat1, 2), size(mat2, 2));
m = min(size(mat1, 2), size(mat2, 2));
Dn1 = size(mat1, 1)-n;
Dn2 = size(mat2, 1)-n;
Dm1 = size(mat1, 2)-m;
Dm2 = size(mat2, 2)-m;
if Dn1 ~= 0
    Dn1=Dn1/Dn1;
elseif Dn2 ~= 0
    Dn2=Dn2/Dn2;
end
if Dm1 ~= 0
    Dm1=Dm1/Dm1;
elseif Dm2 ~= 0
    Dm2=Dm2/Dm2;
end
OMAT = zeros(N-n+1, M-m+1, 2);
OLIST = cell(N-n+1, M-m+1);
for i = 0:(N-n)
    for j = 0:(M-m)
        M = mat1((1+i*Dn1):(n+i*Dn1), (1+i*Dm1):(m+i*Dm1))./mat2((1+i*Dn2):(n+i*Dn2), (1+i*Dm2):(m+i*Dm2));
        Me = mean(M, 'all');
        Md = std(M, 1, 'all');
        OMAT(i+1, j+1, 1) = Me;
        OMAT(i+1, j+1, 2) = Md;
        OLIST{i+1, j+1} = M;

    end
end
end