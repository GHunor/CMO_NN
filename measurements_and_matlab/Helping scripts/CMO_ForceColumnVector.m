function [outputArg] = CMO_ForceColumnVector(inputArg)
%CMO_ForceColumnVector Forces an array (or matrix) to be longer in the first dimension
%   Only looks at the first two dimension, and tranlocate if the second is longer.
% TODO: Make sure it's not effecting complex numbers
if length(inputArg) == size(inputArg, 1)
    outputArg = inputArg;
    return
end
if length(inputArg) == size(inputArg, 2)
    outputArg = inputArg';
    return
end
FT = [size(inputArg, 1), size(inputArg, 2)];
if min(FT) == FT(2)
    outputArg = inputArg;
    return
end
outputArg = inputArg';
end