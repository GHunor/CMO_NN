function [newHand, DHpars, base] = OWN_human20DOF()
%Try to make the included version work

%%% Pre-allocation
DHpars{5} = [];
base{5} = [];
F{5} = [];

% uIM, uMR, uRL: distances between two consecutive carpus joints:
uIM=3;
uMR=3;
uRL=4;

% Vector u[]: distances between the fingers and the wrist
% Order: T I M R L
u=[15 15 12.5 15 17.5];

% Vector fingers_angles: angles between the y axis of the wrist reference 
% frame and each finger.
fingers_angles = [pi/6 asin(uIM/u(2)) 0 -asin(uMR/u(4)) -(atan(uRL/u(5))+atan(uMR/u(4)))];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Thumb
% Links' lengths:
Ltm=45;
Ltp=15;
Ltd=10;
Lt=[Ltm, Ltp, Ltd];

DHpars{1}=[
     -pi/2 0 0 0 ;           % TM joint (abduction/adduction)
       0 Ltm 0 0 ;           % TM joint (flexion/extension)
      pi/2 Ltp 0 0 ;         % MCP joint (flexion/extension)
       0 Ltd 0 0 ];          % IP joint (flexion/extension)

base{1}=[SGrotz(pi/2+fingers_angles(1)) [0 0 0]';0 0 0 1 ]*[SGrotx(0) [u(1) 0 0]'; 0 0 0 1]

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% Index
DHpars{2}=[
    -pi/2 0 0 0 ;             % MCP joint (abduction/adduction)
     0 37 0 0 ;             % MCP joint (flexion/extention)
     0 30 0 0 ;             % PIP joint (flexion/extention)
     0 15 0 0];             % DIP joint (flexion/extention)
base{2} = [0 -1 0 -24;
    1 0 0 73;
    0 0 1 0
    0 0 0 1];

%%%%%%%%%%%%%%%%%%%%%%%%%%%% Middle
DHpars{3}=[
    -pi/2 0 0 0;        % MCP joint (abduction/adduction)
    0 40 0 0;         % MCP joint (flexion/extention)
    0 35 0 0;         % PIP joint (flexion/extention)
    0 17 0 0];        % DIP joint (flexion/extention)
base{3} = [0 -1 0 -8;
    1 0 0 73;
    0 0 1 0
    0 0 0 1];

%%%%%%%%%%%%%%%%%%%%%%%%%%% Ring
DHpars{4}=[
    -pi/2 0 0 0;        % MCP joint (abduction/adduction)
    0 37 0 0;         % MCP joint (flexion/extention)
    0 30 0 0;         % PIP joint (flexion/extention)
    0 15 0 0];        % DIP joint (flexion/extention)

base{4} = [0 -1 0 8;
    1 0 0 73;
    0 0 1 0
    0 0 0 1];

%%%%%%%%%%%%%%%%%%%%%%%%%%% Little
DHpars{5}=[
    -pi/2 0 0 0;        % MCP joint (abduction/adduction)
    0 27 0 0;         % MCP joint (flexion/extention)
    0 25 0 0;         % PIP joint (flexion/extention)
    0 10 0 0];        % DIP joint (flexion/extention)

base{5} = [0 -1 0 24;
    1 0 0 73;
    0 0 1 0
    0 0 0 1];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

for i = 1:length(DHpars)
    % number of joints for each finger
    joints = size(DHpars{i},2);
    % initialize joint variables
    q = zeros(joints,1);
    % make the finger
     if (nargin == 1)
        F{i} = SGmakeFinger(DHpars{i},T*base{i},q);
    else
        F{i} = SGmakeFinger(DHpars{i},base{i},q);
    end
end

newHand = SGmakeHand(F);
newHand.type = 'Custom';
end