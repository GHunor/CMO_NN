function [hitbox] = CMO_MakeHitbox(Mins, Maxs)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here
hitbox.cp = (Maxs-Mins)./2 + Mins;
hitbox.bp = ()
%length(Mins) == length(Max)
hitbox.dim =  length(Mins);
hitbox.lens = Maxs-Mins;
hitbox.mins = Mins;
hitbox.maxs = Maxs;
Comp = @(point)(if sum(hitbox.mins<=point & point<=hitbox.maxs) == hitbox.dim
    return 1;
else
    return 0;
end)
hitbox.IsIn = Comp;

end