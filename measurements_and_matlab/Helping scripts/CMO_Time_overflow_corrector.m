function [corr_time_row, nbias, prev_TS] = CMO_Time_overflow_corrector(time_row, type_max, Tbias, prev_TS)
%CMO_Time_overflow_corretor it makes the the timestamp into always ascending 
%   Detailed explanation goes here

% UI8 MI: 0  MA:255
% UI16 MI: 0  MA:65535
% UI32 MI: 0  MA:4294967295
% UI64 MI: 0  MA:18446744073709551615
% I8 MI: -128  MA:127   127->-128->-127->-126 etc
% I16 MI: -32768  MA:32767
% I32 MI: -21474836648  MA:21474836647
% I64 MI: -9223372036854775808  MA: 9223372036854775807
% FP8
if nargin < 4
    prev_TS = 0;
end

if Tbias<0
    display('CMO_Time_overflow_corrector:Tbias negative value was given')
end
if prev_TS<0
    display('CMO_Time_overflow_corrector:prev_TS negative value was given')
end
if sum(time_row<0)>0
    display('CMO_Time_overflow_corrector:time_row negative value was given')
end
T = [prev_TS; time_row];
prev_TS = time_row(end);
T = T + Tbias;

for j = 1:size(T,1)-1

    if T(j) > T(j+1)
        T(j+1:end) = T(j+1:end) + type_max;
        Tbias = Tbias + type_max;
    end
end
corr_time_row = T(2:end);
nbias = Tbias;
%Prev = T(end);

%{
corr_time_row = time_row + Tbias;
nbias = Tbias;

if nargin < 4
    prev_TS = 0;
else
    if prev_TS>corr_time_row(1)
        nbias = nbias + type_max;
        %corr_time_row = corr_time_row + nbias;
    end
end

for i = 1:size(squeeze(time_row))-1
    corr_time_row(i) = corr_time_row(i) + nbias;
    if time_row(i)>time_row(i+1)
        %corr_time_row(i+1:end) = time_row(i+1:end) + nbias;
        nbias = nbias + type_max;
    end
end
corr_time_row(end) = corr_time_row(end) + nbias;
%}
end