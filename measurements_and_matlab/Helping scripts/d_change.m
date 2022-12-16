function [output1, output2] = d_change(inputArg, n)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here
mms2 = zeros(2,size(inputArg,2));
mms2(1,:) = min(inputArg);
mms2(2,:) = max(inputArg);
diffd = (inputArg-mms2(1,:))./(mms2(2,:)-mms2(1,:));
output1 = diff(diffd);
output2 = abs(output1)>n;
end

