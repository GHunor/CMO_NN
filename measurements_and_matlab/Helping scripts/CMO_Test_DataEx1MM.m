function [time_row] = CMO_Test_DataEx1MM(Min, Max, Amount)
%CMO_Test_DataEx1MM Gives a monoton growing series between two numbers
%   Detailed explanation goes here
time_row = 0:Amount-1;
time_row = time_row/(Amount-1)*(Max-Min) + Min;
end