function [List] = CMO_WindowCombSearch(row1, row2, row3, l)
%UNTITLED5 Summary of this function goes here
%   Detailed explanation goes here
List = [];
len =  min([size(row1, 1), size(row2, 1), size(row3, 1)]);
for i = 1:len-l+1
    T1 = i:l+i-1;
    M1 = max(row1(T1, 1));
    if length(M1)~=1
        if length(M1)<1
            display('what')
            row1(T1, 1)
            continue
        else
            M1 = max(M1,[],'all')
        end
    end
    P1 = min(T1(row1(T1, 1)==M1));
    if length(P1)~=1
        if length(P1)<1
            display('what')
            T1(row1(T1, 1)==M1)
            continue
        else
            T1 = min(T1,[],'all')
        end
    end
    M2 = max(row2(T1, 1));
    if length(M2)~=1
        if length(M2)<1
            display('what')
            row2(T1, 1)
            continue
        else
            M2 = max(M2,[],'all')
        end
    end
    P2 = min(T1(row2(T1, 1)==M2));
    if length(P2)~=1
        if length(P2)<1
            display('what')
            T1(row2(T1, 1)==M1)
            continue
        else
            T1 = min(T1,[],'all')
        end
    end
    M3 = max(row3(T1, 1));
    if length(M3)~=1
        if length(M3)<1
            display('what')
            row3(T1, 1)
            continue
        else
            M3 = max(M3,[],'all')
        end
    end
    P3 = min(T1(row3(T1, 1)==M3));
    if length(P3)~=1
        if length(P3)<1
            display('what')
            row3(T1, 1)
            continue
        else
            P3 = min(P3,[],'all')
        end
    end
    List(i, :) = [i, l+i-1, P1, P2, P3, mean([M1, M2, M3])];
end


end