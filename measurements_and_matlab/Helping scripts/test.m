clear;
close all;

A = [12,23,21];
B = [-23,32,13];
C = [A;B];
pdist(C);

%normalise the glove
%euclidean distance
%normalise the myo
%correlation  - glove euc with myo euc
%

directory = 'test';
[data,fileNames] = CMO_READ_IN(directory)
