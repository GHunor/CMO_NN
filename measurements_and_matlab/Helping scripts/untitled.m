clear;
close all;

directory = 'test2';

if strcmp(directory,'')==0
    directory = join([directory, '/']);
end
join([directory,'*.txt'])
dd = dir(join([directory,'*.txt']));

fileNames = {dd.name};
%fileNames = natsortfiles(fileNames);
[~,idx] = sort({dd.date})
fileNames = fileNames(idx)
names = split(fileNames,'__')
k = strfind(names(:,:,1),'_')
l = split(names(:,:,1), '_')
names = [l(:,:,1); l(:,:,2);names(:,:,2); fileNames ]'
meas = unique(names(:,1),'stable')
meas2 = meas
for l = 1:size(meas, 1)
    meas{l, 2} = {}
end
for i = 1:size(names(:,1), 1)
    for l = 1:size(meas, 1)
        if names{i, 1} == meas{l}
            meas{l,2}{size(meas{l,2}, 1)+1, 1} = names{i, 1}
            meas{l,2}{size(meas{l,2}, 1), 2} = names{i, 2}
            meas{l,2}{size(meas{l,2}, 1), 3} = names{i, 3}
            meas{l,2}{size(meas{l,2}, 1), 4} = names{i, 4}
            names{i, :}
        end
    end
end

