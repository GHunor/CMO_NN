function [measurements] = CMO_READ_IN_BY_MES(directory)
%data,fileNames
%CMO_READ_IN Reads in CMO data from a choosen directory (must be only data from that, no config files)

%NEEDS TO SEPERATE THE MESUREMENTS
%AND ORDER IT BY TIME 
    %FileInfo = dir('YourFileWithExtention');
    %TimeStamp = FileInfo.date;

if strcmp(directory,'')==0
    directory = join([directory, '/']);
end
join([directory,'*.txt'])
dd = dir(join([directory,'*.txt']));

fileNames = {dd.name};
fileNames = natsortfiles(fileNames);
names = squeeze(split(fileNames,'__'))
k = strfind(names(:,1),'_')
size(names)
measurements = {};
k(1)
names{1,1}(1:k{1}-1)
measurements{1, 1} = names{1,1}(1:k{1}-1);
measurements{1, 2} = {};
newmes = 1;
for i = 1:size(names, 1)
    for j = 1:size(measurements, 1)
        if strcomp(measurements{j,1}, names{i,1}(1:k{i}-1));
           newmes = 0;
           measurements{j,2}{end+1} = fileNames{i};
        end
    end
    if newmes == 1
        measurements{end+1,1} = names{i,1}(1:k{i}-1);
        measurements{end+1, 2} = {};
    end
end
%for i = 1;size(names, 1)

%data = cell(numel(fileNames),2);
%data(:,1) = regexprep(fileNames, '.txt','');

%maybe needs to have a limit to not step over the memory

%for ii = 1:numel(fileNames)    
%   data{ii,2} = readmatrix(join([directory,fileNames{ii}]));
%end

end
