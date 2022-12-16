function [mes_ordered_list] = CMO_MES_ORDER(progdata)
%UNTITLED3 Summary of this function goes here
mes_names = unique(progdata(:,1))
order_base = zeros(2,40);
begin_t = 0;
end_t = 0;
setted = 0;
prev_name = ""

subdata = {}

rds = CMO_rawdataseperator()
for i = 1:size(progdata, 1)

    subdata{i,1} = progdata{i,1};
    subdata{i,2} = progdata{i,2}+1;
    subdata{i,3} = progdata{i,6}(1,3)+bias;
    subdata{i,4} = progdata{i,6}(end,3);
    subdata{i,5} = 0;
    if subdata{i,3} > subdata{i,4}
        subdata{i,5} = 1;
    end
end
for i = 1:size(progdata, 1)
    tmp_sec_num = progdata{i,2}+1;
    if ~strcmp(progdata{i,1},prev_name)
        if i > 1
                end_t = progdata{i-1,6}(end,3);
        end
        for ii = 1:size(mes_names, 1)
            if strcmp(progdata{i,1},mes_names{ii})
                begin_t = progdata{i,6}(1,3);
                prev_name = progdata{i,1};
            end 
        end
    end
    
    
    subdata{}
end

end

