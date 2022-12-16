function [composdata] = CMO_MINS_AND_MAXS(progdata)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
mes_names = unique(progdata(:,1))
%mov_names = unique(progdata(:,3));
[rds] = CMO_rawdataseperator()
composdata = zeros(1,1,2,size(rds,2));
tmp_mes_num = 0;
tmp_sec_num = 0;
size(mes_names)
progdata{1,1}
for i = 1:size(progdata, 1)
    tmp_sec_num = progdata{i,2}+1;
    for ii = 1:size(mes_names, 1)
        if strcmp(progdata{i,1},mes_names{ii})
            tmp_mes_num=ii;
        end
    end
    composdata(tmp_mes_num,tmp_sec_num,1,:) = progdata{i,7}(rds);
    composdata(tmp_mes_num,tmp_sec_num,2,:) = progdata{i,8}(rds);
end
end

