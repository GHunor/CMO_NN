function [data,fileNames] = CMO_READ_IN(directory)
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


data = cell(numel(fileNames),2);
data(:,1) = regexprep(fileNames, '.txt','');

%maybe needs to have a limit to not step over the memory

for ii = 1:numel(fileNames)    
   data{ii,2} = readmatrix(join([directory,fileNames{ii}]));
end

end

