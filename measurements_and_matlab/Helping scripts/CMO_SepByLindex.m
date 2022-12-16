function [List] = CMO_SepByLindex(Data, LI)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
pI = 0;
List = {[]};
Listi = 1;
for i = 1:size(Data, 1)
    I = LI(i);
    if I
        List{Listi} = [List{Listi};Data(i, :)];
        pI = I;
        continue;
    end
    if xor(pI, I)
        if pI
            Listi = Listi+1;
            List{Listi} = [];
        end
    end
    pI = I;
end
if size(List{end}) == [0 0]
    List = List(1:end-1);
end
end