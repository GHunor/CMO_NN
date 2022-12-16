function [] = SG_OWN_HandAnim(hand, posS, framerate, look, limits, res, directory, name)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here
mkdir(directory);

outputVideo = VideoWriter(fullfile(directory,name));
outputVideo.FrameRate = framerate;
open(outputVideo);
Width = res(1);
Height = res(2);
for i = 1:size(posS,1)
    hand = MoveHand(hand,posS(i, :));
    h = HandPlot(hand, 1, look, limits, Width, Height);
    F=getframe(h);
    img = F.cdata;
    figure(2);
    imagesc(img);
    writeVideo(outputVideo,img)
end
close(outputVideo);
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

function hand = MoveHand(hand,qdeg)
    q = deg2rad(qdeg);
    hand = SGmoveHand(hand,q)
end