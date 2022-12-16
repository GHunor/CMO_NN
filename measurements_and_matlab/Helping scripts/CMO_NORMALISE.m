function [progdata] = CMO_NORMALISE(progdata, minvs, maxvs)
%CMO_NORMALISE Normalises the data by given mins and maxes

rds = CMO_rawdataseperator()

for i = 1:size(progdata, 1)
    %for j = 1:size(progdata{i,6}, 1)
        progdata{i,6}(:,rds) = (progdata{i,6}(:,rds)-minvs)./(maxvs-minvs);
    %end
end
end