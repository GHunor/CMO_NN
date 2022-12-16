function [Time_Row] = CMO_Test_DataEx3W(Time_Row, Type_Size)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here
for  i = 1:length(Time_Row)
    if Time_Row(i) > Type_Size
        Time_Row(i:end) = Time_Row(i:end)-Type_Size;
    end
end
end