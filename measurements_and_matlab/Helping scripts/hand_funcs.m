function [hand,q] = CreateHand()
    hand = SGparadigmatic;
    [q, S] = SGsantelloSynergies;
    hand = SGdefineSynergies(hand,S,1:15);
end

function hand = MoveHand(hand,qdeg)
    q = deg2rad(qdeg);
    hand = SGmoveHand(hand,q)
end

function hand = MoveHandRad(hand,qdeg)
    q = deg2rad(qdeg);
    hand = SGmoveHand(hand,q)
end

function HandPlot(hand, t, Look, Limits)
    figure(t)
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