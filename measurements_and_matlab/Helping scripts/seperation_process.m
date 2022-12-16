%clear;
%close all;

%load('data.mat')
%READ IN
%{
dd = dir('*.txt');

fileNames = {dd.name};
fileNames = natsortfiles(fileNames);

data = cell(numel(fileNames),2);
data(:,1) = regexprep(fileNames, '.txt','');

for ii = 1:numel(fileNames)    
   data{ii,2} = readmatrix(fileNames{ii});
end
%}
    %ndata = split(data(:,1),'__');
    %names = unique(ndata(:,2));
    %{
    logic_list = zeros(size(ndata,1),size(names, 1));
    for i = 1:size(names, 1)
        for j = 1:size(ndata,1)
            logic_list(j,i) = strcmp(ndata{j,2},names{i, 1});
        end
    end
    logic_list = logic_list == 1;
    tmp = data{logic_list(:,1),2};
    seperated_data = {names{1}, {data{logic_list(:,1),2}}};
    for i = 2:size(names, 1)
        seperated_data(i,:) = {names{i}, {data{logic_list(:,i),2}}};
    end
    %}


%SEPERATE NAME
%{
n2data = split(data(:,1),'__');
k = strfind(n2data(:,1),'_');

n3data = {};
last = {};
for i = 1:size(n2data, 1)
    k2(i) = k{i}(end);
    n3data{i,1} = n2data{i,1}(1:k2(i)-1);
    n3data{i,2} = str2num(n2data{i,1}(k2(i)+1:end));
    n3data{i,3} = n2data{i,2};
    n3data{i,4} = ~isempty(strfind(n2data{i,2},'_reped'));
    if n3data{i,4}
        n3data{i,3} = n2data{i,2}(1:strfind(n2data{i,2},'_reped')-1);
    end
    n3data{i,5} = data{i,2};
    n3data{i,6} = min(n3data{i,5});
    n3data{i,7} = max(n3data{i,5});
end
%}



%EMPTY REMOVE
%{
n3data_c = {};
j = 1;
for i = 1:size(n3data, 1)
    if isempty(n3data{i,5})
        continue;
    end
    n3data_c(j, :) = n3data(i,:);
    j = j + 1;
end
%}



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

flag = {};
for i = 1:size(n3data_c, 1)
    flag{i,1} = 0;
end
for i = 1:size(n3data_c, 1)
    if n3data_c{i,4} == 1
        flag{i,1} = 1;
        if i>=2 && strcmp(n3data_c{i,3},n3data_c{i-1,3})
            flag{i-1,1} = 1;
        end
        if i>=3 && strcmp(n3data_c{i,3},n3data_c{i-2,3})
            flag{i-2,1} = 1;
        end
        if i<size(n3data_c, 1) && strcmp(n3data_c{i,3},n3data_c{i+1,3})
            flag{i+1,1} = 1;
        end
        if i<size(n3data_c, 1)-1 && strcmp(n3data_c{i,3},n3data_c{i+2,3})
            flag{i+2,1} = 1;
        end
    end
end
n3data_c2 = n3data_c;
n3data_c2(:,6:8) = n3data_c(:,5:7);
n3data_c2(:,5) = flag;


% GLOVE GLOBAL BOUNDARIES
%{
glove_min = [];
glove_max = []; 
opt_min = [];
opt_max = [];
tmp_m = [];
tmp_m = squeeze( n5data{1,3}(:,1,:) );
glove_min = min( tmp_m(:,14:36));
opt_min =  min( tmp_m(:,[38:40, 42:44, 46:48]));
tmp_m = squeeze( n5data{1,3}(:,2,:) );
glove_max = max( tmp_m(:,14:36));
opt_max = max(tmp_m(:,[38:40, 42:44, 46:48]));
for i = 2:size(n5data(:,3),1)
    tmp_m = squeeze( n5data{i,3}(:,1,:) );
    size(tmp_m)
    size(tmp_m(:,14:36))
    size(min( tmp_m(:,14:36)))
    size([min( tmp_m(:,14:36));[]])
    size(min( tmp_m(:,[38:40, 42:44, 46:48])))
    glove_min = min( [min( tmp_m(:,14:36));glove_min]);
    opt_min =  min( [min( tmp_m(:,[38:40, 42:44, 46:48]));opt_min]);
    tmp_m = squeeze( n5data{i,3}(:,2,:) );
    glove_max = max([max(tmp_m(:,14:36));glove_max]);
    opt_max = max([max(tmp_m(:,[38:40, 42:44, 46:48]));opt_max]);
end
%}

%NORMALISED DATA
%{
n3data_mc = n3data_c(:,1:4);
[2,5:12,14:36, 38:40, 42:44, 46:48]
for i = 1:size(n3data_c, 1)
    n3data_mc{i,5} = n3data_c{i,5}(:,[2,5:12,14:36, 38:40, 42:44, 46:48]);
    n3data_mc{i,5}(:,2:9) = (n3data_mc{i,5}(:,2:9)+128)/256;
    n3data_mc{i,5}(:,10:32) = (n3data_mc{i,5}(:,10:32)-glove_min)./(glove_max-glove_min);
    n3data_mc{i,5}(:,33:41) = (n3data_mc{i,5}(:,33:41)-opt_min)./(opt_max-opt_min);
end
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
frame_rate = 10;
mkdir(workingDir);

outputVideo = VideoWriter(fullfile(workingDir,vid_name));
outputVideo.FrameRate = frame_rate;
open(outputVideo)

qdeg = seperated_data{27, 2}{1, 1}(:,14:33);
% 1 2 3 4 5
% abductio, MCP, DIP, PIP
base = [0.10072,0.961169,0.245984,0.0115808,    0.1,0.9,0.3,0.3,   0.1,0.9,0.3,0.3,    0.2,0.7,0.3,0.3,   0.3,0.7,0.3,0.3];
%base = [0.10072,0.961169,0.245984,0.0115808,    0.2174017,1.04344,0.0225781,-0.106422,   0.485104,1.203179,0.0188049,0.0190061,    0.447007,0.998502,0.00401062,0.0677966,   0.420008,0.868428,0.00672934,0.107995];
%base_O2 = [-0.961169,-0.269808,-0.245984,-0.0115808,    -1.04344,-0.26582,-0.0225781,0.106422,   -1.0834,-0.374213,-0.0188049,-0.0190061,     -0.998502,-0.506506,-0.00401062,-0.0677966,    -0.868428,-0.568256,-0.00672934,-0.312636];

%base = base.*multA-biasB;
%base_m1 = [0.0743985, 0.15 ,0.163439 ,0.341757 ,   -0.03 ,-0.00916617 ,-0.00158513 ,-0.167245 ,   -0.02 ,0.015 ,-0.0213257 ,-0.00189288 ,         0.05 ,-0.0789474 ,-0.0154155 ,0.171092 ,    0.15 ,-0.0980195 ,-0.0197378 ,0.3];
%base_O = [-0.0743985, -0.319088 ,-0.163439 ,-0.341757, -0.0184183 ,0.00916617 ,0.00158513 ,0.167245 ,  0.130891 ,0.104779 ,0.0213257 ,0.00189288,  -0.109499 ,0.0789474 ,0.0154155 ,-0.171092 , -0.298248 ,0.0980195 ,0.0197378 ,-0.504641];
multA = [-1 -1 -1 -1   -1 -1 -1 -1   -1 -1 -1 -1   -1 -1 -1 -1   -1 -1 -1 -1];
%biasB = [0 0 0 0   0 0 0 0   0 0 0 0   0 0 0 0   0 0 0 0];
%biasB = [0,0.169088,0,0,0.0484183,0,0,0,-0.110891,-0.119779,0,0,0.059499,0,0,0,0.148248,0,0,0.204641];
biasB = [0,0.169088,0,0,0.0484183,0,0,0,-0.110891,-0.119779,0,0,0.059499,0,0,0,0.148248,0,0,0.204641];
%biasB = base_O.*multA-base;
orderO = [ 2, 1, 3, 4,   6, 5, 7, 8,   10, 9,11,12,  14,13,15,16,  18,17,19,20];

Look = [-45 45]; %from the left
Limits = [-90,90,-10,170,-90,90];
width = 800;
height = 800;

hand = CreateHand();
hand = MoveHandRad(hand,base);
HandPlot(hand, 1, Look, Limits, width, height);

%dif_qdeg = diff(qdeg,[],1);
%[trash ,info_qdeg] = max(abs(dif_qdeg),[],1);
%mode(
%qdeg = seperated_data{27,:}{1,1}(:,14:36);


%{
hand = CreateHand();
for i = 1:size(qdeg,1)
    hand = MoveHandRad(hand,qdeg(i,:).*multA-biasB);
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