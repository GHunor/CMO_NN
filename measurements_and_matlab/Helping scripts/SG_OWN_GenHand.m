function [newHand, dhpars, base] = SG_OWN_GenHand(dhpars, base, T)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
for i = 1:length(dhpars)
    % number of joints for each finger
    joints = size(dhpars{i},2);
    % initialize joint variables
    q = zeros(joints,1);
    % make the finger
     if (nargin == 3)
        F{i} = SGmakeFinger(dhpars{i},T*base{i},q);
    else
        F{i} = SGmakeFinger(dhpars{i},base{i},q);
    end
end

newHand = SGmakeHand(F);
newHand.type = 'Paradigmatic';
end