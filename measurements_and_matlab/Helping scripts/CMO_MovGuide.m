function [guideC] = CMO_MovGuide(FullLenght, Wait, Dur,  When, Speed1, Speed2)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

Mat = zeros(FullLenght, 1);

Here = Wait+When;
for i = 1:Speed1
Mat(Here+i) = SmoothStep(Here+i, Here, Here+Speed1, 0, 1)
end
Here = Here+Speed1;
Mat(Here+1:Here+Dur, :) = 1;
Here = Here+Dur;
for i = 1:Speed2
Mat(Here+i) = SmoothStep(Here+i, Here, Here+Speed2, 1, 0)
end


end