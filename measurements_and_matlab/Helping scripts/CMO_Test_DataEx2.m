function [time_row] = CMO_Test_DataEx2(Length, Base, Step, SkipNumber, SkipClimb)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
time_row = 0:Length;
time_row = time_row * Step;
time_row = time_row+Base;
StepN = round(rand()*SkipNumber);
Steps = zeros(1, StepN);
for i = 1:StepN
    Steps(i) = round(rand()*Length);
end
Steps = sort(unique(Steps));
for i = Steps
    time_row(i:end) = time_row(i:end)+(rand()*SkipClimb*0.2)+SkipClimb;
end

end