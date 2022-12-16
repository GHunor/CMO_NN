function [logic_index_vect] = CMO_time_skip_detect(time_col,step, tolerance)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
if sum(time_col<0) >0
    display('CMO_time_skip_detect:time_col negative value was given')
    time_col
end
if step<0
    display('CMO_time_skip_detect:step negative value was given')
    step
end
if tolerance<0
    display('CMO_time_skip_detect:tolerance negative value was given')
end
    DTC = diff(time_col);
    Neg = DTC<step-step*tolerance;
    Pos = DTC>step+step*tolerance;
    Neg = -1*Neg;
    logic_index_vect = Pos+Neg;
    %logic_index_vect(:,2) = Neg;
    logic_index_vect = [0;logic_index_vect];
end