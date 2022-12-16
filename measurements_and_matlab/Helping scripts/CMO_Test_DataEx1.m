function [time_row] = CMO_Test_DataEx1(Length, Base, Step)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
time_row = 0:Length;
time_row = time_row * Step;
time_row = time_row+Base;
end
