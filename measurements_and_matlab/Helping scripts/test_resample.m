clear;
close all;

avgSTB = 70;
avgSTS = 7

amount = 400;

base = 1:amount;
Sbase = base*avgSTS;
Bbase = base*avgSTB;
offset1 = 0.8*(rand(1,amount)-0.5);
offset2 = 0.8*(rand(1,amount)-0.5);

Sseq = Sbase+(offset1.*avgSTS)
Bseq = Bbase+(offset2.*avgSTB)

%resample()
%interp1
%spline

%synchronize
a = datetime(2022, 5, 21, 17, 39, 40, Sseq)
b = datetime(2022, 5, 21, 17, 39, 40, Bseq)
Time = milliseconds(Sseq)
%CTime = 
Values = rand(amount,1)*10;
TT1 = timetable(Values, 'RowTimes', Time);
TT1n = retime(TT1, 'regular','linear','SampleRate', 142.86);
TT1p1 = timetable(Values(1:56), 'RowTimes', milliseconds(Sseq(1:56)));
TT1p2 = timetable(Values(57:234), 'RowTimes', milliseconds(Sseq(57:234)));
TT1p3 = timetable(Values(235:amount), 'RowTimes', milliseconds(Sseq(235:amount)));

TT1p1n = retime(TT1p1, 'regular','linear','SampleRate', 142.86);
TT1p2 = append(getsamples(TT1p1n, end), TT1p2)
TT1p2n = retime


Time = milliseconds(Bseq);
Values = rand(amount,1)*13;
TT2 = timetable(Values, 'RowTimes', Time);

TT = synchronize(TT1, TT2, 'union','linear');

figure(1)
stackedplot(TT1)
figure(2)
stackedplot(TT1n)
figure(3)
stackedplot(TT2)
%figure(3)
%stackedplot(TT)
