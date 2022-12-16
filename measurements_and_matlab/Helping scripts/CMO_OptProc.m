function [OUopt, EUopt, PreT1, PreT3, PreT4, PreV, Bias] = CMO_OptProc(opt, optMM, Bias, T, PreT1, PreT3, PreT4, PreV, Starter, TypeSize )
%CMO_OptProc Goes trough optoforce data and process it
%   normalizes data and make the time steps uniform (also detects too big time jumps)
if nargin < 9
    Starter = 0;
end
if nargin < 10
    TypeSize = 65535;
end
%PreT1 absolute original
%PreT2 after overflow correction before -starter
%PreT3 after -starter before inter
%PreT4 after interp
if Bias<0
    display('CMO_OptProc:Bias negative value was given')
end
if PreT1<0
    display('CMO_OptProc:PreT1 negative value was given')
end
if PreT3<0
    display('CMO_OptProc:PreT3 negative value was given')
end
if PreT4<0
    display('CMO_OptProc:PreT4 negative value was given')
end
if Starter<0
    display('CMO_OptProc:Starter negative value was given')
end
if TypeSize<0
    display('CMO_OptProc:TypeSize negative value was given')
end
Ot = opt(:,1);

Od = opt(:,2:end);
Od = (Od-optMM(1,:))./(optMM(2,:)-optMM(1,:));
[Ot, Bias, NPreT2] = CMO_Time_overflow_corrector(Ot, TypeSize, Bias, PreT1);
PreT1 = opt(end,1);
if sort(Ot)~=Ot
    display('Ot not sorted')
    Ot
    figure
    plot(1:size(Ot,1), Ot)
end
Ot = Ot - Starter;

LI = CMO_time_skip_detect([PreT3;Ot],10, 0.1);
Interval = CMO_IntervalFromDetect(Ot, LI(2:end), PreT3, Ot(end,1));
PreT3 = NPreT2- Starter;

[RS_D1, RS_T1] = CMO_Interp1Part(Od, Ot, 1/T, PreV, PreT4);
[LV] = CMO_IntervalToInclude(RS_T1, Interval);
RS_T1 = RS_T1';
LV = LV.';
PreT4 = RS_T1(end,1);
PreV = RS_D1(end,:);

OUopt = [RS_T1, RS_D1, LV];
EUopt = [RS_T1, CMO_Metric_Euc(RS_D1), LV];

end