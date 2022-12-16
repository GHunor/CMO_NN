function [C] = Values_and_repeats(A, t)
%UNTITLED9 Summary of this function goes here
%   Detailed explanation goes here
i = 1;
k = 1:
p = 1;
C = {}
List = {}
for i = 1:size(A,1)
    List{i} = A(i,:);
end
C{1,1} = List{1}
for i = 1:size(A,1)
    List{i} = A(i,:);
end
while i~=size(A,1)
   if Veccomp(A(k,:),A(i,:),0.2)
       C{p,1} = cat
   end

end
end

