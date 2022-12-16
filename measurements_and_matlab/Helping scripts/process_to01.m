clear;
close all;

dd = dir('*.txt');

fileNames = {dd.name};
fileNames = natsortfiles(fileNames);

data = cell(numel(fileNames),2);
data(:,1) = regexprep(fileNames, '.txt','');

for ii = 1:numel(fileNames)    
   data{ii,2} = readmatrix(fileNames{ii});
end
dataB = natsort(data(:,1));
datacont = data{1,2};
size(data, 1)
size(data{1,2})
size(data{2,2})
%datacont = cat(1, data{1,2}, data{2,2});
for i = 2:size(data, 1)    
   datacont = cat(1, datacont, data{i,2});
end
mms = zeros(2,49);
mms(1,:) = min(datacont);
mms(2,:) = max(datacont);

datapart1 = datacont(:, 3:12);
datapart2 = datacont(:, 13:36);
datapart3 = datacont(:, 37:40);
datapart4 = datacont(:, 41:44);
datapart5 = datacont(:, 45:48);

dx = mean(diff(datapart1(:,1)));  %miliseconds
dxo1 = mean(diff(datapart3(:,1))); %1kHz count
dxo2 = mean(diff(datapart4(:,1)));
dxo3 = mean(diff(datapart5(:,1)));
x = datapart1(:,1) - mms(1,3);

diffd = datapart2(:, 2:24);
mms2 = zeros(2,23);
mms2(1,:) = min(diffd);
mms2(2,:) = max(diffd);
diffd = (diffd-mms2(1,:))./(mms2(2,:)-mms2(1,:));
diffd2 = diff(diffd);
logicout = abs(diffd2)>0;
[glovediff, glovedifflog] = d_change(datapart2(:, 2:24),0);
[myodiff, myodifflog] = d_change(datapart1(:, 3:10),0.035);
[optdiff1(:,:), optdifflog1(:,:)] = d_change(datapart3(:, 2:4),0.02);
[optdiff2(:,:), optdifflog2(:,:)] = d_change(datapart4(:, 2:4),0.02);
[optdiff3(:,:), optdifflog3(:,:)] = d_change(datapart5(:, 2:4),0.01);

movements(:,1) = sum(glovediff,2);
movements(:,2) = mean(glovediff,2);
movements(:,3) = sum(glovedifflog,2);
movements(:,4) = mean(glovedifflog,2);
movements(:,5) = sum(glovediff.*glovedifflog,2);
movements(:,6) = sum(glovediff.*glovedifflog,2)./sum(glovedifflog,2);

movements(:,7) = sum(optdiff1,2);
movements(:,8) = mean(optdiff1,2);
movements(:,9) = sum(optdifflog1,2);
movements(:,10) = mean(optdifflog1,2);
movements(:,11) = sum(optdiff1.*optdifflog1,2);
movements(:,12) = sum(optdiff1.*optdifflog1,2)./sum(optdifflog1,2);

st =  1:round(size(movements,1)*dxo1/dx);
xq = st.*dxo1;
tmp = interp1(datapart3(1:size(movements,1),1)-min(datapart3(:,1)),optdiff1,xq);
Newopt1diff = zeros(size(movements,1),3);
Newopt1diff(st,:) = tmp;
Newopt1difflog = abs(Newopt1diff)>0.04;

movements(:,13) = sum(Newopt1diff,2);
movements(:,14) = mean(Newopt1diff,2);
movements(:,15) = sum(Newopt1difflog,2);
movements(:,16) = mean(Newopt1difflog,2);
movements(:,17) = sum(Newopt1diff.*Newopt1difflog,2);
movements(:,18) = sum(Newopt1diff.*Newopt1difflog,2)./sum(Newopt1difflog,2);

movements(:,19) = zeros(size(movements, 1),1);
for i = 2:size(movements, 1)-1
    movements(i,19) =  movements(i,3)>0 && (movements(i-1,3)>0 || movements(i+1,3)>0);
end
movements(:,20) = datacont(1:size(movements, 1), 2).*movements(:,19);

%xq = (1:
%s = spline(x,y,xq)


%traindata2 = zeros(shape(datacont(:, 1)),37);
%traindata2(:,1
% kell valahogy visszakapni az eredeti mozgasokat
% for every data geting the biggest and the smallest

% recognising movement?



%dataB = sortrows(data, 1);

%for ii = 1:numel(fileNames)    
%   data{ii,2} = dlmread(fileNames{ii});
%end


%A = readmatrix(filename)




%s = spline(x,y,xq)