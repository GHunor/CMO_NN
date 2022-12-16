clear;
close all;

%load('data.mat')
%READ IN
dd = dir('*.txt');

fileNames = {dd.name};
fileNames = natsortfiles(fileNames);

data = cell(numel(fileNames),2);
data(:,1) = regexprep(fileNames, '.txt','');

for ii = 1:numel(fileNames)    
   data{ii,2} = readmatrix(fileNames{ii});
end

%BOUNDARIES
glove_min = [];
glove_max = []; 
opt_min = [];
opt_max = [];
    

%SEPERATE NAME

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
    glove_min(i,:) = progdata{i,6}(1,14:36);
    opt_min(i,:) = progdata{i,6}(1,14:36);
    progdata{i,7} = max(progdata{i,5});
end

%EMPTY REMOVE

tmp = {};
j = 1;
for i = 1:size(progdata, 1)
    if isempty(progdata{i,5})
        continue;
    end
    tmp(j, :) = progdata(i,:);
    j = j + 1;
end
progdata = tmp;

progdata{1,5} = progdata{1,5}(2:end,:);



%CLOSE TO REPED
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


progdata2 = {};
mes_names = unique(progdata(:,1));
mov_names = unique(progdata(:,3));
progdata2 = {};
for i = 1:size(mes_names, 1)
    progdata2{i,1} = mes_names{i};
    tmp = zeros(0,size(progdata{i,5},2));
    for j = 1:size(progdata, 1)
        if strcmp(progdata{j,1}, progdata2{i,1})
            tmp = cat(1, tmp, progdata{j,5});
        end
    end
    progdata2{i,2} = tmp;
end

%BREAK UP TO MOVEMENTS - MINS and MAXES
progdata3 = {};
for i = 1:size(mov_names, 1)
    progdata3{i,1} = mov_names{i};
    tmp = {};
    index = 1;
    %tmp2 = zeros(1,1,size(n3data{i,5},2));
    tmp2 = [];
    for j = 1:size(progdata, 1)
        if strcmp(progdata{j,3}, progdata3{i,1})
            tmp{index} = progdata(j,:);
            if size(progdata{j,6},1) ~= 0
                tmp2(index,1,:) = progdata{j,7};
                tmp2(index,2,:) = progdata{j,8};
            end
            index = index + 1;
            
        end
    end
    progdata3{i,2} = tmp;
    progdata3{i,3} = tmp2;
end

for i = 1:size(progdata,1)
    mer = progdata{i,6}(:,14:33);
    ind = zeros(size(mer,1),1);
    dmer = diff(mer);
    lmer = abs(dmer)>0;
    ind(1:end-1,1) = sum(lmer,2) > 3;
    progdata{i,9} = ind;
    
    start_ind = 1;
    end_ind = 1;
    prev_j =0;
    sections = {};
    for j = 1:size( progdata{i,9},1)
        if ind(j) && ~prev_j
            end_ind = j;
            sections = cat(1, sections, {(start_ind:end_ind)});
        end
        if ~ind(j) && prev_j
            start_ind = j;
        end
        %save 0 places until change
        %also count the 1 sections
        prev_j = ind(j);
    end
    sections = cat(1, sections, {(start_ind:size( progdata{i,9},1))});
    progdata{i,10} = sections;
end

neutral(1,:) = [-0.615479000000000,-0.466928000000000,-0.328529000000000,-0.0460768000000000,-0.819218000000000,-0.479698000000000,-0.00791343000000000,0.0976796000000000,-0.988779000000000,-0.414129000000000,-0.0155211000000000,-0.0122223000000000,-0.890087000000000,-0.506506000000000,-0.00401062000000000,-0.0728408000000000,-0.802638000000000,-0.542631000000000,-0.00197613000000000,-0.329508000000000]
neutral(2,:) = [-0.870988000000000,-0.614768000000000,-0.427583000000000,0.0574112000000000,-1.09149000000000,-0.678299000000000,-0.0319178000000000,0.0822078000000000,-1.06763000000000,-0.733456000000000,-0.0474591000000000,-0.0188221000000000,-1.02019000000000,-0.861326000000000,-0.0909768000000000,-0.0439566000000000,-0.956148000000000,-0.786077000000000,-0.0641005000000000,-0.306538000000000];
%[-0.961169000000000,-0.269808000000000,-0.245984000000000,-0.0115808000000000,-1.04344000000000,-0.265820000000000,-0.0225781000000000,0.106422000000000,-1.08340000000000,-0.374213000000000,-0.0188049000000000,-0.0190061000000000,-0.998502000000000,-0.506506000000000,-0.00401062000000000,-0.0677966000000000,-0.868428000000000,-0.568256000000000,-0.00672934000000000,-0.312636000000000,-0.327600000000000,0.629990000000000,-0.0627200000000000,49087,128,-54,-174,49097,71,-58,-358,49097,-195,42,-553,NaN]

viable_moves = {'1_oppositio';'1_outwards';'2_MCP_flexio';'2_PIP_flexio';'2_extensio';'3-4-5_extensio';'3_MCP_flexio';'3_PIP_flexio';'4_MCP_flexio';'4_PIP_flexio';'5_MCP_flexio';'5_PIP_flexio';'fist';'spear';'spread_fingers'};

%{'1_oppositio';'1_outwards';'2_MCP_flexio';'2_PIP_flexio';'2_extensio';'3-4-5_extensio';'3_MCP_flexio';'3_PIP_flexio';'4_MCP_flexio';'4_PIP_flexio';'5_MCP_flexio';'5_PIP_flexio';'TOTAL_STILL';'fist';'init';'spear';'spread_fingers'}

moves_states = [];
k = 1;
temp = {};
for p = 1:size(viable_moves,1)
    viable_moves{p,2} = [];
end
for i = 1:size(progdata, 1)
    for p = 1:size(viable_moves,1)
         if strcmp(viable_moves{p,1}, progdata{i,3})
             for j = 1:size(progdata{i,10},1)
                 temp = progdata{i,10};
                 viable_moves{p,2}(size(viable_moves{p,2},1)+1,:) = mean(progdata{i,6}(temp{j},14:33),1);
             end
         end
    end
end
for p = 1:size(viable_moves,1)
    viable_moves{p,3} = viable_moves{p,2}-mean(viable_moves{p,2});
    %viable_moves{p,4} = viable_moves{p,2}-
end

%BREAK UP TO MEASUREMENTS - CONTINIOUS
%{
mes_names = unique(n3data_c(:,1));
mov_names = unique(n3data_c(:,3));
n4data = {};
for i = 1:size(mes_names, 1)
    n4data{i,1} = mes_names{i};
    tmp = zeros(0,size(n3data_c{i,5},2));
    for j = 1:size(n3data_c, 1)
        if strcmp(n3data_c{j,1}, n4data{i,1})
            tmp = cat(1, tmp, n3data_c{j,5});
        end
    end
    n4data{i,2} = tmp;
end
%}
% BREAK AT WRIST MOVEMENTS
% GET MORE FREE MOVEMENTS
% 

%BREAK UP TO MOVEMENTS - MINS and MAXES
%{
n5data = {};
for i = 1:size(mov_names, 1)
    n5data{i,1} = mov_names{i};
    tmp = {};
    index = 1;
    %tmp2 = zeros(1,1,size(n3data{i,5},2));
    tmp2 = [];
    for j = 1:size(n3data_c, 1)
        if strcmp(n3data_c{j,3}, n5data{i,1})
            tmp{index} = n3data_c(j,:);
            if size(n3data_c{j,6},1) ~= 0
                tmp2(index,1,:) = n3data_c{j,6};
                tmp2(index,2,:) = n3data_c{j,7};
            end
            index = index + 1;
            
        end
    end
    n5data{i,2} = tmp;
    n5data{i,3} = tmp2;
end
%}


%flag close to reped
%{
tmp = {};
for i = 1:size(n3data_c, 1)
    tmp{i,1} = 0;
end
for i = 1:size(n3data_c, 1)
    if n3data_c{i,4} == 1
        tmp{i,1} = 1;
        if i>=2 && strcmp(n3data_c{i,3},n3data_c{i-1,3})
            tmp{i-1,1} = 1;
        end
        if i>=3 && strcmp(n3data_c{i,3},n3data_c{i-2,3})
            tmp{i-2,1} = 1;
        end
        if i<size(n3data_c, 1) && strcmp(n3data_c{i,3},n3data_c{i+1,3})
            tmp{i+1,1} = 1;
        end
        if i<size(n3data_c, 1)-1 && strcmp(n3data_c{i,3},n3data_c{i+2,3})
            tmp{i+2,1} = 1;
        end
    end
end
n3data_c2 = n3data_c;
n3data_c2(:,6:8) = n3data_c(:,5:7);
n3data_c2(:,5) = tmp;
%}

% GLOVE GLOBAL BOUNDARIES

glove_min = [];
glove_max = []; 
opt_min = [];
opt_max = [];
tmp_m = [];
tmp_m = squeeze( progdata3{1,3}(:,1,:) );
glove_min = min( tmp_m(:,14:36));
opt_min =  min( tmp_m(:,[38:40, 42:44, 46:48]));
tmp_m = squeeze( progdata3{1,3}(:,2,:) );
glove_max = max( tmp_m(:,14:36));
opt_max = max(tmp_m(:,[38:40, 42:44, 46:48]));
for i = 2:size(progdata3(:,3),1)
    tmp_m = squeeze( progdata3{i,3}(:,1,:) );
    if size(tmp_m) == [49,1]
        tmp_m = tmp_m';
        glove_min = min( [tmp_m(:,14:36);glove_min]);
        opt_min =  min( [tmp_m(:,[38:40, 42:44, 46:48]);opt_min]);
    else
        glove_min = min( [min( tmp_m(:,14:36));glove_min]);
        opt_min =  min( [min( tmp_m(:,[38:40, 42:44, 46:48]));opt_min]);
    end
    tmp_m = squeeze( progdata3{i,3}(:,2,:) );
    if size(tmp_m) == [49,1]
        tmp_m = tmp_m';
        glove_max = max( [tmp_m(:,14:36);glove_max]);
        opt_max =  max( [tmp_m(:,[38:40, 42:44, 46:48]);opt_max]);
    else
        glove_max = max( [max( tmp_m(:,14:36));glove_max]);
        opt_max =  max( [max( tmp_m(:,[38:40, 42:44, 46:48]));opt_max]);
    end
end


%NORMALISED DATA

progdata(:,11) = progdata(:,6);
%[2,5:12,14:36, 38:40, 42:44, 46:48]
for i = 1:size(progdata, 1)
    progdata{i,11} = progdata{i,11}(:,[3,5:12,14:36, 37:40, 41:44, 45:48]);
    progdata{i,11}(:,2:9) = (progdata{i,11}(:,2:9)+128)/256;
    progdata{i,11}(:,10:32) = (progdata{i,11}(:,10:32)-glove_min)./(glove_max-glove_min);
    progdata{i,11}(:,[34:36,38:40,42:44]) = (progdata{i,11}(:,[34:36,38:40,42:44])-opt_min)./(opt_max-opt_min);
end

All = progdata{1,11};
for i = 2:size(progdata, 1)
    All = cat(1,All,progdata{i,11});
end

myo = All(:,2:9);
glove = All(:,10:32);
o1n = All(:,34:36);
o2n = All(:,38:40);
o3n = All(:,42:44);


dmyo = diff(myo,1,1);
dglove = diff(glove,1,1);
do1n = diff(o1n,1,1);
do2n = diff(o2n,1,1);
do3n = diff(o3n,1,1);
d2myo  = diff(myo,2,1);
d2glove  = diff(glove,2,1);
d2o1n = diff(o1n,2,1);
d2o2n = diff(o2n,2,1);
d2o3n = diff(o3n,2,1);

mit_p = 2;

syms x
f(x) = sum(x.^mit_p,2).^(1/mit_p);

D_myo = sum(myo.^mit_p,2).^(1/mit_p);
D_glove = sum(glove.^mit_p,2).^(1/mit_p);
D_o1n = sum(o1n.^mit_p,2).^(1/mit_p);
D_o2n = sum(o2n.^mit_p,2).^(1/mit_p);
D_o3n = sum(o3n.^mit_p,2).^(1/mit_p);


D_dmyo = sum(dmyo.^mit_p,2).^(1/mit_p);
D_dglove = sum(dglove.^mit_p,2).^(1/mit_p);
D_do1n = sum(do1n.^mit_p,2).^(1/mit_p);
D_do2n = sum(do2n.^mit_p,2).^(1/mit_p);
D_do3n = sum(do3n.^mit_p,2).^(1/mit_p);
D_d2myo  = sum(d2myo.^mit_p,2).^(1/mit_p);
D_d2glove  = sum(d2glove.^mit_p,2).^(1/mit_p);
D_d2o1n = sum(d2o1n.^mit_p,2).^(1/mit_p);
D_d2o2n = sum(d2o2n.^mit_p,2).^(1/mit_p);
D_d2o3n = sum(d2o3n.^mit_p,2).^(1/mit_p);

%break up
BRKDATA = progdata(:,1);
prev_i = 1;
    BRKDATA{1,1} = 'counters';
    BRKDATA{1,2} = 'myo';
    BRKDATA{1,3} = 'glove';
    BRKDATA{1,4} = 'o1n';
    BRKDATA{1,5} = 'o2n';
    BRKDATA{1,6} = 'o3n';
    BRKDATA{1,7} = 'dmyo';
    BRKDATA{1,8} = 'dglove';
    BRKDATA{1,9} = 'do1n';
    BRKDATA{1,10} = 'do2n';
    BRKDATA{1,11} = 'do3n';
    BRKDATA{1,12} = 'd2myo';
    BRKDATA{1,13} = 'd2glove';
    BRKDATA{1,14} = 'd2o1n';
    BRKDATA{1,15} = 'd2o2n';
    BRKDATA{1,16} = 'd2o3n';

    BRKDATA{1,17} = 'D_myo';
    BRKDATA{1,18} = 'D_glove';
    BRKDATA{1,19} = 'D_o1n';
    BRKDATA{1,20} = 'D_o2n';
    BRKDATA{1,21} = 'D_o3n';
    BRKDATA{1,22} = 'D_dmyo';
    BRKDATA{1,23} = 'D_dglove';
    BRKDATA{1,24} = 'D_do1n';
    BRKDATA{1,25} = 'D_do2n';
    BRKDATA{1,26} = 'D_do3n';
    BRKDATA{1,27} = 'D_d2myo';
    BRKDATA{1,28} = 'D_d2glove';
    BRKDATA{1,29} = 'D_d2o1n';
    BRKDATA{1,30} = 'D_d2o2n';
    BRKDATA{1,31} = 'D_d2o3n';
for i = 1:size(progdata, 1)-1
    BRKDATA{i+1,1} = progdata{i,11}(:,[1, 33, 37, 41]);
    BRKDATA{i+1,2} = myo(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,3} = glove(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,4} = o1n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,5} = o2n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,6} = o3n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,7} = dmyo(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,8} = dglove(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,9} = do1n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,10} = do2n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,11} = do3n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,12} = d2myo(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,13} = d2glove(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,14} = d2o1n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,15} = d2o2n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,16} = d2o3n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,17} = D_myo(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1);
    BRKDATA{i+1,18} = D_glove(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1);
    BRKDATA{i+1,19} = D_o1n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1);
    BRKDATA{i+1,20} = D_o2n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1);
    BRKDATA{i+1,21} = D_o3n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1);
    BRKDATA{i+1,22} = D_dmyo(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,23} = D_dglove(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,24} = D_do1n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,25} = D_do2n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,26} = D_do3n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1,:);
    BRKDATA{i+1,27} = D_d2myo(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1);
    BRKDATA{i+1,28} = D_d2glove(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1);
    BRKDATA{i+1,29} = D_d2o1n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1);
    BRKDATA{i+1,30} = D_d2o2n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1);
    BRKDATA{i+1,31} = D_d2o3n(prev_i:prev_i+size(BRKDATA{i+1,1},1)-1);
    prev_i = prev_i+size(BRKDATA{i+1,1},1)+1;
end
    BRKDATA{size(progdata, 1),1} = progdata{size(progdata, 1),11}(:,[1, 33, 37, 41]);
    BRKDATA{size(progdata, 1),2} = myo(prev_i:end,:);
    BRKDATA{size(progdata, 1),3} = glove(prev_i:end,:);
    BRKDATA{size(progdata, 1),4} = o1n(prev_i:end,:);
    BRKDATA{size(progdata, 1),5} = o2n(prev_i:end,:);
    BRKDATA{size(progdata, 1),6} = o3n(prev_i:end,:);
    BRKDATA{size(progdata, 1),7} = dmyo(prev_i:end,:);
    BRKDATA{size(progdata, 1),8} = dglove(prev_i:end,:);
    BRKDATA{size(progdata, 1),9} = do1n(prev_i:end,:);
    BRKDATA{size(progdata, 1),10} = do2n(prev_i:end,:);
    BRKDATA{size(progdata, 1),11} = do3n(prev_i:end,:);
    BRKDATA{size(progdata, 1),12} = d2myo(prev_i:end,:);
    BRKDATA{size(progdata, 1),13} = d2glove(prev_i:end,:);
    BRKDATA{size(progdata, 1),14} = d2o1n(prev_i:end,:);
    BRKDATA{size(progdata, 1),15} = d2o2n(prev_i:end,:);
    BRKDATA{size(progdata, 1),16} = d2o3n(prev_i:end,:);

    BRKDATA{size(progdata, 1),17} = D_myo(prev_i:end);
    BRKDATA{size(progdata, 1),18} = D_glove(prev_i:end);
    BRKDATA{size(progdata, 1),19} = D_o1n(prev_i:end);
    BRKDATA{size(progdata, 1),20} = D_o2n(prev_i:end);
    BRKDATA{size(progdata, 1),21} = D_o3n(prev_i:end);
    BRKDATA{size(progdata, 1),22} = D_dmyo(prev_i:end,:);
    BRKDATA{size(progdata, 1),23} = D_dglove(prev_i:end,:);
    BRKDATA{size(progdata, 1),24} = D_do1n(prev_i:end,:);
    BRKDATA{size(progdata, 1),25} = D_do2n(prev_i:end,:);
    BRKDATA{size(progdata, 1),26} = D_do3n(prev_i:end,:);
    BRKDATA{size(progdata, 1),27} = D_d2myo(prev_i:end);
    BRKDATA{size(progdata, 1),28} = D_d2glove(prev_i:end);
    BRKDATA{size(progdata, 1),29} = D_d2o1n(prev_i:end);
    BRKDATA{size(progdata, 1),30} = D_d2o2n(prev_i:end);
    BRKDATA{size(progdata, 1),31} = D_d2o3n(prev_i:end);
    
    %correlation?
    myo_indexes = [17,22,27];
    glov_indexes = [18, 23, 28];
    opt_indexes = [19:21;24:26;29:31];
    opt_indexes = opt_indexes';
    CORR_LIST = progdata(:,1);
    [rho,pval] = corr(BRKDATA{2,17},BRKDATA{2,18})
for i = 2:size(BRKDATA, 1)
    CORR_LIST{i,2} = i;
    CORR_LIST{i,3} = (1:9)';
    for j1 = 1:3
        for j2 = 1:3
            [~,CORR_LIST{i,3}((j1-1)*3+j2)] = corr(BRKDATA{i,glov_indexes(j1)}(1:min(size(BRKDATA{i,glov_indexes(j1)},1),size(BRKDATA{i, myo_indexes(j2)},1))),BRKDATA{i, myo_indexes(j2)}(1:min(size(BRKDATA{i,glov_indexes(j1)},1),size(BRKDATA{i, myo_indexes(j2)},1))));
        end
    end
    CORR_LIST{i,4} = (1:9)';
    for k = 2:size(BRKDATA, 1)
        if i == k
            CORR_LIST{i,4}(:,k) = zeros(9,1);
            continue;
        end
        for j1 = 1:3
            for j2 = 1:3
                [~,CORR_LIST{i,4}((j1-1)*3+j2,k)] = corr(BRKDATA{i,glov_indexes(j1)}(1:min(size(BRKDATA{i,glov_indexes(j1)},1),size(BRKDATA{k, myo_indexes(j2)},1)),:),BRKDATA{k, myo_indexes(j2)}(1:min(size(BRKDATA{i,glov_indexes(j1)},1),size(BRKDATA{k, myo_indexes(j2)},1)),:));
            end
        end
    end
    [~,CORR_LIST{i,5}] = max(CORR_LIST{i,3});
    [~,CORR_LIST{i,6}] = max(CORR_LIST{i,4}(:,2:end),[], 'all', 'linear');
    [~,CORR_LIST{i,7}] = max([max(CORR_LIST{i,3}),max(CORR_LIST{i,4}(:,2:end),[], 'all')]);
    CORR_LIST{i,8} = CORR_LIST{i,3}(1);
    
    CORR_LIST{i,10} = (1:9)';
    for j1 = 1:3
        for j2 = 1:3
            [~,CORR_LIST{i,10}((j1-1)*3+j2, 1)] = corr(BRKDATA{i,glov_indexes(j1)}(1:min(size(BRKDATA{i,glov_indexes(j1)},1),size(BRKDATA{i, opt_indexes(j2,1)},1))),BRKDATA{i, opt_indexes(j2,1)}(1:min(size(BRKDATA{i,glov_indexes(j1)},1),size(BRKDATA{i, opt_indexes(j2,1)},1))));
            [~,CORR_LIST{i,10}((j1-1)*3+j2, 2)] = corr(BRKDATA{i,glov_indexes(j1)}(1:min(size(BRKDATA{i,glov_indexes(j1)},1),size(BRKDATA{i, opt_indexes(j2,2)},1))),BRKDATA{i, opt_indexes(j2,2)}(1:min(size(BRKDATA{i,glov_indexes(j1)},1),size(BRKDATA{i, opt_indexes(j2,2)},1))));
            [~,CORR_LIST{i,10}((j1-1)*3+j2, 3)] = corr(BRKDATA{i,glov_indexes(j1)}(1:min(size(BRKDATA{i,glov_indexes(j1)},1),size(BRKDATA{i, opt_indexes(j2,3)},1))),BRKDATA{i, opt_indexes(j2,3)}(1:min(size(BRKDATA{i,glov_indexes(j1)},1),size(BRKDATA{i, opt_indexes(j2,3)},1))));
        end
    end
    CORR_LIST{i,11} = (1:9)';
    for k = 2:size(BRKDATA, 1)
        if i == k
            CORR_LIST{i,11}(:,k) = zeros(9,1);
            continue;
        end
        for j1 = 1:3
            for j2 = 1:3
                [~,CORR_LIST{i,11}((j1-1)*3+j2, 1,k)] = corr(BRKDATA{i,glov_indexes(j1)}(1:min(size(BRKDATA{i,glov_indexes(j1)},1),size(BRKDATA{k, opt_indexes(j2,1)},1)),:),BRKDATA{k,opt_indexes(j2,1)}(1:min(size(BRKDATA{i,glov_indexes(j1)},1),size(BRKDATA{k, opt_indexes(j2,1)},1)),:));
                [~,CORR_LIST{i,11}((j1-1)*3+j2, 2,k)] = corr(BRKDATA{i,glov_indexes(j1)}(1:min(size(BRKDATA{i,glov_indexes(j1)},1),size(BRKDATA{k, opt_indexes(j2,2)},1)),:),BRKDATA{k,opt_indexes(j2,2)}(1:min(size(BRKDATA{i,glov_indexes(j1)},1),size(BRKDATA{k, opt_indexes(j2,2)},1)),:));
                [~,CORR_LIST{i,11}((j1-1)*3+j2, 3,k)] = corr(BRKDATA{i,glov_indexes(j1)}(1:min(size(BRKDATA{i,glov_indexes(j1)},1),size(BRKDATA{k, opt_indexes(j2,3)},1)),:),BRKDATA{k,opt_indexes(j2,3)}(1:min(size(BRKDATA{i,glov_indexes(j1)},1),size(BRKDATA{k, opt_indexes(j2,3)},1)),:));
            end
        end
    end
    [~,CORR_LIST{i,12}] = max(CORR_LIST{i,3},[],1,'linear');
    [~,CORR_LIST{i,13}] = max(CORR_LIST{i,4}(:,2:end),[],[1,3], 'linear');
    [~,CORR_LIST{i,14}] = max([max(CORR_LIST{i,3}),max(CORR_LIST{i,4}(:,2:end),[],[1,3])]);
    CORR_LIST{i,15} = CORR_LIST{i,10}(1);
end

%sort by euc dist
%unique(sort(glove))

%plot
figure(6)
size(BRKDATA{9,1},1);
u = [1,1,1,1,1]
w = conv(u,BRKDATA{10,17}');
plot((1:size(BRKDATA{10,18},1)),BRKDATA{10,23}',(1:size(BRKDATA{10,17},1)), w(3:end-2))



%o1r = [];
%o2r = [];
%o3r = [];


%{
All = n3data_mc{1,5};
for i = 2:size(n3data_mc, 1)
    All = cat(1,All,n3data_mc{i,5});
end
%}

% TYPES OF GLOVE POSITIONS
%{
tol = 0.2;
Types = {};
Types{1,1} = All(1,1);
Types{1,2} = All(1,10:32);
Types{1,3} = All(1,:);

sig = 0;
for i = 2:size(All(1:1000,:), 1)
    for j = 1:size(Types, 1)
        if Veccomp(All(i,10:32),Types{j,2},tol)
            sig = 1;
            size(Types{j,3})
            size(All(i,10:32))
            Types{j,3} = cat(1,Types{j,3},All(i,:));
            Types{j,1} = mean(Types{j,3}(:,1));
            Types{j,2} = mean(Types{j,3}(:,10:32));
        end
    end
    if ~sig
        Types{size(Types, 1)+1,1} = All(i,1);
        Types{size(Types, 1),2} = All(i,10:32);
        Types{size(Types, 1),3} = All(i,:);
    end
    sig = 0;
end
%}

%for i = 1:size(n5data(:,3),1)
%end

%RECOGNITION
%{
mov_recog = {};
for i = 1:size(n5data(:,3),1)
    mov_recog{i,1} = squeeze(n5data{i,3}(:,1,:));
    mov_recog{i,1} = mean(mov_recog{i,1});
    mov_recog{i,2} = squeeze(n5data{i,3}(:,2,:));
    mov_recog{i,2} = mean(mov_recog{i,2});
    
    mov_recog{i,3} = squeeze(n5data{i,3}(:,1,:));
    mov_recog{i,3} = mode(mov_recog{i,3});
    mov_recog{i,4} = squeeze(n5data{i,3}(:,2,:));
    mov_recog{i,4} = mode(mov_recog{i,4});
    
    mov_recog{i,5} = squeeze(n5data{i,3}(:,1,:))-mov_recog{i,1};
    mov_recog{i,6} = squeeze(n5data{i,3}(:,1,:))-mov_recog{i,3};
    mov_recog{i,7} = squeeze(n5data{i,3}(:,2,:))-mov_recog{i,2};
    mov_recog{i,8} = squeeze(n5data{i,3}(:,2,:))-mov_recog{i,4};
    % somehwo recognise movement?
    % read into syngrasp?
    
end
%}


workingDir = 'dir';
vid_name = 'shuttle_out.avi';
frame_rate = 14;
mkdir(workingDir);

outputVideo = VideoWriter(fullfile(workingDir,vid_name));
outputVideo.FrameRate = frame_rate;
open(outputVideo)

qdeg = progdata{2, 6}(:,14:33);
% 1 2 3 4 5
% abductio, MCP, DIP, PIP

spear = [0.07, 0.15 ,0.16 ,0.34 ,   -0.03 ,-0.01 ,-0.0016 ,-0.167 ,   -0.02 ,0.015 ,-0.02 ,-0.002 ,         0.05 ,-0.08 ,-0.015 ,0.17,    0.15 ,-0.1 ,-0.02 ,0.3];
fist = [0.2,1.2,0.1,0.0116,    0.1, 1.5, 1.5, 1.5,   0.1, 1.5, 1.5, 1.5    0.2, 1.5, 1.5, 1.5   0.3, 1.5, 1.5, 1.5];
natural = [0.1,0.96,0.246,0.0116,    0.1,0.9,0.3,0.3,   0.1,0.9,0.3,0.3,    0.1,0.7,0.3,0.3,   0.3,0.7,0.3,0.3];

base = [0.1,0.961169,0.245984,0.0115808,    0.1,0.9,0.3,0.3,   0.1,0.9,0.3,0.3,    0.2,0.7,0.3,0.3,   0.3,0.7,0.3,0.3];
base_Om = [0.269808,0.961169,0.245984,0.0115808,    0.2174017,1.04344,0.0225781,-0.106422,   0.485104,1.203179,0.0188049,0.0190061,    0.447007,0.998502,0.00401062,0.0677966,   0.420008,0.868428,0.00672934,0.107995];
%base_O2 = [-0.961169,-0.269808,-0.245984,-0.0115808,    -1.04344,-0.26582,-0.0225781,0.106422,   -1.0834,-0.374213,-0.0188049,-0.0190061,     -0.998502,-0.506506,-0.00401062,-0.0677966,    -0.868428,-0.568256,-0.00672934,-0.312636];
%[-0.901049000000000,-0.737968000000000,-1.03842000000000,0.126403000000000,-1.58799000000000,-1.57964000000000,-0.529947000000000,0.105760000000000,-1.76151000000000,-1.49186000000000,-0.458591000000000,-0.0285397000000000,-1.84414000000000,-1.67741000000000,-0.615227000000000,-0.0477602000000000,-1.89914000000000,-1.34985000000000,-0.353596000000000,-0.310342000000000]

%fist
%[-0.810869000000000,-0.713328000000000,-1.13747000000000,0.111619000000000,-1.60400000000000,-1.54909000000000,-0.504550000000000,0.100756000000000,-1.76151000000000,-1.53178000000000,-0.490427000000000,-0.0268895000000000,-1.77909000000000,-1.71289000000000,-0.647690000000000,-0.0461100000000000,-2.07458000000000,-1.34985000000000,-0.353596000000000,-0.255466000000000]
%base = base.*multA-biasB;
base_m1 = [0.0743985, 0.15 ,0.163439 ,0.341757 ,   -0.03 ,-0.00916617 ,-0.00158513 ,-0.167245 ,   -0.02 ,0.015 ,-0.0213257 ,-0.00189288 ,         0.05 ,-0.0789474 ,-0.0154155 ,0.171092 ,    0.15 ,-0.0980195 ,-0.0197378 ,0.3];
base_O = [-0.0743985, -0.319088 ,-0.163439 ,-0.341757, -0.0184183 ,0.00916617 ,0.00158513 ,0.167245 ,  0.130891 ,0.104779 ,0.0213257 ,0.00189288,  -0.109499 ,0.0789474 ,0.0154155 ,-0.171092 , -0.298248 ,0.0980195 ,0.0197378 ,-0.504641];
multA = [-1 -1 -1 -1   -1 -1 -1 -1   -1 -1 -1 -1   -1 -1 -1 -1   -1 -1 -1 -1];
%biasB = [0 0 0 0   0 0 0 0   0 0 0 0   0 0 0 0   0 0 0 0];
%biasB = [0,0.169088,0,0,0.0484183,0,0,0,-0.110891,-0.119779,0,0,0.059499,0,0,0,0.148248,0,0,0.204641];
biasB = [0,0.169088,0,0,0.0484183,0,0,0,-0.110891,-0.119779,0,0,0.059499,0,0,0,0.148248,0,0,0.204641];
%biasB = base_O.*multA-base;
orderO = [ 2, 1, 3, 4,   6, 5, 7, 8,   10, 9,11,12,  14,13,15,16,  18,17,19,20];
revOrder = [ 2, 1, 3, 4,   6, 5, 7, 8,   10, 9,11,12,  14,13,15,16,  18,17,19,20];

TryA(orderO) = (base-base_m1)./(-base_Om(orderO) - base_O);
TryB(orderO) = base_m1-base_O;



Look = [-45 45]; %from the left
Limits = [-90,90,-10,170,-90,90];
width = 800;
height = 800;

hand = CreateHand();
hand = MoveHandRad(hand,spear);
HandPlot(hand, 1, Look, Limits, width, height);
hand = MoveHandRad(hand,fist);
HandPlot(hand, 2, Look, Limits, width, height);
hand = MoveHandRad(hand,natural);
HandPlot(hand, 3, Look, Limits, width, height);


dif_qdeg = diff(qdeg,[],1);
%[trash ,info_qdeg] = max(abs(dif_qdeg),[],1);
%mode(
%qdeg = seperated_data{27,:}{1,1}(:,14:36);

%A = (Y1-Y2)./(X1 - X2);

%{
hand = CreateHand();
for i = 1:size(qdeg,1)
    hand = MoveHandRad(hand,qdeg(i,orderO).*TryA(orderO)-TryB(orderO));
    h = HandPlot(hand, 1, Look, Limits, width, height);
    F=getframe;
    img = F.cdata;
    figure(2);
    imagesc(img);
    writeVideo(outputVideo,img)
end
close(outputVideo);
%}
%Loop through the image sequence, load each image, and then write it to the video.


%xwidth = 300;
%ywidth = 300;
%set(gcf,'PaperPositionMode','auto')
%set(h, 'Position', [0 0 xwidth ywidth])
%plot(x,y)
%saveas(gcf,'someFigure.png')


%{
mms = zeros(1,2,size(seperated_data{1,2}{1}, 2));
for i = 2:size(names, 1)
    for j = 1:size(seperated_data{i,2},2)
        tmp = seperated_data{j,2};
        mms(j,1,:) = min(tmp{j});
        mms(j,2,:) = max(tmp{j});
    end
end
%}

% for repped k = strfind(str,'_reped')
% for number : k = strfind(str,'_'); number = str2num(str(k(end):end))

function [hand,q] = CreateHand()
    hand = SGparadigmatic;
    [q, S] = SGsantelloSynergies;
    hand = SGdefineSynergies(hand,S,1:15);
end

function hand = MoveHand(hand,qdeg)
    q = deg2rad(qdeg);
    hand = SGmoveHand(hand,q)
end
function hand = MoveHandRad(hand,rad)
    hand = SGmoveHand(hand,rad)
end

function [h] = HandPlot1(hand, t, Look, Limits)
    figure(t)
    SGplotHand(hand);
    %axis('equal')
    axis on
    grid on 
    view(Look);
    axis(Limits)
    h = figure(t);
end

function [h] = HandPlot(hand, t, Look, Limits, width, height)
    h = figure(t)
    %'Name', 'fucky','Position', [x y width height]);
    h.Position = [0 0 width height];
    SGplotHand(hand);
    %axis('equal')
    axis on
    grid on 
    view(Look);
    axis(Limits)
end


function HandAnim(hand, Qhand, t, Look, Limits, jointplot, restplot, name)
    %kell 6 frame
    frame = 0;
    [~,Ijm]=max(jointplot);
    [~,Irm]=max(restplot);
    lastsmall=1;
    step = true;
    for i = 1:size(Qhand,2)
        
         hand = MoveHand(hand,Qhand(:,i));
         fig = figure(t);
         SGplotHand(hand);
         axis on
         grid on 
         view(Look);
         axis(Limits);
         drawnow;
         
         
         if ~(i==size(Qhand,2))
             if (jointplot(lastsmall+1)==0) & step
                 lastsmall = lastsmall+1;
             else
                 step = false;
                 if (i == lastsmall) | (i==Ijm)| (i==Irm)| (i==round((Ijm-Irm)/2)+Irm)| (i==round((Irm-lastsmall)/2)+lastsmall)
                       frame = frame+1;
                        print(fig,[name,'_handanim_',num2str(frame)],'-dpng');
            
                 end
             end
         end
         
           
    end
    img(1,:,:,:,:,:) = imread([name,'_handanim_',num2str(1), '.png']);
    for i = 1:frame
        img(i+1,:,:,:,:,:) = imread([name,'_handanim_',num2str(i), '.png']);
        delete( [name,'_handanim_',num2str(i), '.png']);
    end
    img(frame+2,:,:,:,:,:) = img(frame+1,:,:,:,:,:);
    %img = -img+256;
    
    for i = 1:frame+1
        %a1*q1(1-q2)+a2*q2 = a3
        img(i+1,:,:,:,:,:) = img(i,:,:,:,:,:)*0.5 + 0.5*img(i+1,:,:,:,:,:);
    end
    %img(8:14,:,:,:,:,:) = img(1:7,:,:,:,:,:);
    %img = mean(img,1);
    %img = -img+256;
    fig = figure(t+1);
    imagesc(squeeze(img(end,:,:,:,:,:)));
    print(fig,[name,'_handanim_reprent'],'-dpng');
end