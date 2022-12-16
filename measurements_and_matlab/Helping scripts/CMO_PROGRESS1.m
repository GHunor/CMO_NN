function [progdata,names] = CMO_PROGRESS1(data, fileNames)
%CMO_PROGRESS1 Splits the name of the recordings into data point

names = split(data(:,1),'__');
k = strfind(names(:,1),'_');

progdata = {};
last = {};
for i = 1:size(names, 1)
    k2(i) = k{i}(end);
    progdata{i,1} = names{i,1}(1:k2(i)-1);
    progdata{i,2} = str2num(names{i,1}(k2(i)+1:end));
    progdata{i,3} = names{i,2};
    progdata{i,4} = ~isempty(strfind(names{i,2},'_reped'));
    if progdata{i,4}
        progdata{i,3} = names{i,2}(1:strfind(names{i,2},'_reped')-1);
    end
    progdata{i,5} = data{i,2};
    progdata{i,6} = min(progdata{i,5});
    progdata{i,7} = max(progdata{i,5});
end

end

