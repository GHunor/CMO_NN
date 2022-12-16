function [progdata, list] = CMO_CLOSE_TO_REPED(progdata)
%Reconstructs ProdData with all repeated section marked

mes_names = unique(progdata(:,1));
mov_names = unique(progdata(:,3));

tmp = {};
for i = 1:size(progdata, 1)
    tmp{i,1} = 0;
end
for i = 1:size(progdata, 1)
    if progdata{i,4} == 1
        tmp{i,1} = 1;
        if i>=2 && strcmp(progdata{i,3},progdata{i-1,3})
            tmp{i-1,1} = 1;
        end
        if i>=3 && strcmp(progdata{i,3},progdata{i-2,3})
            tmp{i-2,1} = 1;
        end
        if i<size(progdata, 1) && strcmp(progdata{i,3},progdata{i+1,3})
            tmp{i+1,1} = 1;
        end
        if i<size(progdata, 1)-1 && strcmp(progdata{i,3},progdata{i+2,3})
            tmp{i+2,1} = 1;
        end
    end
end
progdata(:,6:8) = progdata(:,5:7);
progdata(:,5) = tmp;

list = {};
for i = 1:size(mes_names, 1)
    list{i,1} = mes_names{i};
    tmp = zeros(0,size(progdata{i,5},2));
    for j = 1:size(progdata, 1)
        if strcmp(progdata{j,1}, list{i,1})
            tmp = cat(1, tmp, progdata{j,5});
        end
    end
    list{i,2} = tmp;
end
end

