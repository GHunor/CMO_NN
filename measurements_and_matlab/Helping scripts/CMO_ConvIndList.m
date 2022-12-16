function [mat] = CMO_ConvIndList(num1, num2)
%CMO_ConvIndList Index list generation convolution
%   Detailed explanation goes here
mat = zeros((num1-num2+1), num2);
for i = 1:(num1-num2+1)
    mat(i, :) = i:(i+num2-1);
end
end