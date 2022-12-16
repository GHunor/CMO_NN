function [] = CMO_PRESENT_1D1R(data, figureName )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

if nargin < 2
    figureName =   "fig"
  end

figure('Name',figureName);
plot(data)
end