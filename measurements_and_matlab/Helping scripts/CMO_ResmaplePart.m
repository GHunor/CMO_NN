function [RSdata, RStime] = CMO_ResmaplePart(data, dataT, fs,  Ldata, LdataT)
%CMO_ResmaplePart Resamaples a data row part into uniform samplerate
%   Detailed explanation goes here
 if nargin < 4
     Ldata = data(1, :);
     data = data(2:end, :);
     LdataT = dataT(1);
     dataT = dataT(2:end);
 end
 RSdata = resample([Ldata;data], [LdataT;dataT], fs);
 T = 1/fs;
 RStime = 0:size(RSdata, 1)-1;
 RStime = RStime';
 RStime = RStime.*T+LdataT;

end