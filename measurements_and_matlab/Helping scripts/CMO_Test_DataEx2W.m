function [Time_Row] = CMO_Test_DataEx2W(Time_Row, SkipNumber, SkipClimb)
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here
Length = length(Time_Row);
StepN = round(rand()*SkipNumber);
Steps = zeros(1, StepN);
for i = 1:StepN
    Steps(i) = round(rand()*Length);
end
Steps = sort(unique(Steps));
for i = Steps
    Time_Row(i:end) = Time_Row(i:end)+(rand()*SkipClimb*0.2)+SkipClimb;
end
end