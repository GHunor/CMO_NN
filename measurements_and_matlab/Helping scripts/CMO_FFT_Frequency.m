function [freq_data] = CMO_FFT_Frequency(data, Fs)
%CMO_FFT_Frequency Creates a frequency domain representation (Matlab example based)
%   Detailed explanation goes here
L = max(size(data));
Y = fft(X);
P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);
f = Fs*(0:(L/2))/L;
freq_data = [f, P1];

end