function [shift] = CMO_ShiftedCORRCheckWI(eucL1, eucL2, maxD)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
L1 = size(eucL1, 1)
L2 = size(eucL2, 1)

R = (0:maxD);

Shifts = {};

Shifts = {[0,0]};
B1M = max([L1, L2]);
Big = zeros(B1M, 3);
Big(1:L1, 1) = eucL1(:,2);
Big(1:L2, 2) = eucL2(:,2);
T1 = Big(:, 3);
T1(1:L1) = eucL1(:,3);
T2 = Big(:, 3);
T2(1:L2) = eucL2(:,3);
Big(:, 3) = (T1)' & (T2)';
Bigs{1} = Big;
for i = 1:maxD
    Shifts{i+1} = [i, 0];
    B1M = max([L1+i, L2]);
    Big = zeros(B1M, 3);
    Big(1+i:L1+i, 1) = eucL1(:,2);
    Big(1:L2, 2) = eucL2(:,2);
    T1 = Big(:, 3);
    T1(1+i:L1+i) = eucL1(:,3);
    T2 = Big(:, 3);
    T2(1:L2) = eucL2(:,3);
    Big(:, 3) = (T1)' & (T2)';
    Bigs{i+1} = Big;
end
for i = 1:maxD
    Shifts{maxD+i+1} = [0, i];
    B1M = max([L1, L2+i]);
    Big = zeros(B1M, 3);
    Big(1:L1, 1) = eucL1(:,2);
    Big(1+i:L2+i, 2) = eucL2(:,2);
    T1 = Big(:, 3);
    T1(1:L1) = eucL1(:,3);
    T2 = Big(:, 3);
    T2(1+i:L2+i) = eucL2(:,3);
    Big(:, 3) = (T1)' & (T2)';
    Bigs{maxD+i+1} = Big;
end
M = 1;
for i = 1: length(Shifts )
    %Big = zeros(max(L1+i(1), L2+i(2)), 3);
    L = CMO_SepByLindex(Bigs{i}(:, 1:2), Bigs{i}(:, 3));
    if size(L{end}, 1) == 0
        L = L(1:end-1);
    end
    Shifts{i}(3) = CMO_ListCORRCheck(L);
    if Shifts{i}(3)>Shifts{M}(3)
        M=i;
    end
end

shift = Shifts%{M}(1:2);

end