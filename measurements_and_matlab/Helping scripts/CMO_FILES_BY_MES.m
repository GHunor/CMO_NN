function [meas, fileNames, names] = CMO_FILES_BY_MES(directory)
%CMO_FILES_BY_MES files are sorted
%    Collects the names of files from a specified directory and groups them by the measurements (specifed in the naming convention of the file)

if strcmp(directory,'')==0
    directory = join([directory, '/']);
end
dd = dir(join([directory,'*.txt']));

fileNames = {dd.name};
%fileNames = natsortfiles(fileNames);
[~,idx] = sort({dd.date});
fileNames = fileNames(idx);
names = split(fileNames,'__')
names2 = split(names(:,:,2) , '.')
names(:,:,2) = names2(:,:,1);
l = split(names(:,:,1), '_');
names = [l(:,:,1); l(:,:,2);names(:,:,2); fileNames ]'
meas = unique(names(:,1),'stable')
for l = 1:size(meas, 1)
    meas{l, 2} = {};
end
for i = 1:size(names(:,1), 1)
    for l = 1:size(meas, 1)
        if strcmp(names{i, 1}, meas{l})
            meas{l,2}{size(meas{l,2}, 1)+1, 1} = names{i, 1};
            meas{l,2}{size(meas{l,2}, 1), 2} = names{i, 2};
            meas{l,2}{size(meas{l,2}, 1), 3} = names{i, 3};
            meas{l,2}{size(meas{l,2}, 1), 4} = names{i, 4};
        end
    end
end
end