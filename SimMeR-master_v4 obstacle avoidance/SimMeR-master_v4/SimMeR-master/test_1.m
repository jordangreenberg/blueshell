% Copyright (c) 2020, Ian G. Bennett
% All rights reserved.
% Development funded by the University of Toronto, Department of Mechanical
% and Industrial Engineering.
% Distributed under GNU AGPLv3 license.

clear
close all
clc

sim = 1;

if sim
    % Initialize tcp server to read and respond to algorithm commands
    [s_cmd, s_rply] = tcp_setup();
    fopen(s_cmd);
    %fopen(s_rply);
else
    % connect to Bluetooth
    btInfo = instrhwinfo('Bluetooth','ROB6')
    s_cmd = Bluetooth(btInfo.RemoteID, 1);
    fopen(s_cmd);
    s_rply = s_cmd;
end

% Robot Sensor Measurements
u = [0,0,0,0];  % Ultrasonic measurements
pos = [0,0,0];  % Position (x,y,rotation)
speed = 2;
rot_stuck = 90;
stepcount = 0;
step = 0;




while 1
    
    % Take Measurements
    %for ct = 1:6
    %    cmdstring = [strcat('u',num2str(ct)) newline];
    %    u(ct) = tcpclient_write(cmdstring, s_cmd, s_rply);
    %end
    
    cmdstring = ['ua' newline];
    u = tcpclient_write(cmdstring, s_cmd, s_rply);
    
    %ir = tcpclient_write(['i1' newline], s_cmd, s_rply);
    
    %comp = tcpclient_write(['c1' newline], s_cmd, s_rply);
    
    % Display Values
    disp('Ultrasonic')
    disp(u)
    
    if  (u(1) > 2.5) && (u(2) > 2.5) && (u(3) > 2.5) && (u(4) > 2.5)
        % If the way ahead is clear, go forward
        if pos(3) == 0
            %we are moving in the right direction
            [pos] = move_forward(pos, speed, s_cmd, s_rply);
            step = step + 1;
            disp("1")
            [pos(3), step] = check_peripherals(u, pos(3), step);
        
        elseif pos(3) == 90
            [pos] = move_forward(pos, speed, s_cmd, s_rply);
            step = step + 1;
            disp("11")
            [pos(3), step] = check_peripherals(u, pos(3), step);
        
        elseif pos(3) == 180
            [pos] = move_forward(pos, speed, s_cmd, s_rply);
            step = step + 1;
            disp("111")
            [pos(3), step] = check_peripherals(u, pos(3), step);
        
        elseif pos(3) == 270
            [pos] = move_forward(pos, speed, s_cmd, s_rply);
            step = step + 1;
            disp("1111")
            [pos(3), step] = check_peripherals(u, pos(3), step);
        end
        
        
    elseif (u(2) < 2.5)

        % If robot is close to the forward wall
        cmdstring = [strcat('s1-0.5',num2str(speed)) newline];  % Build command string to move bot
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        disp("2")
        
    elseif (u(4) < 2.5)
        % If robot is close to the back wall
        cmdstring = [strcat('w1-0.5',num2str(speed)) newline];  % Build command string to move bot
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        disp("3")
        
    elseif (u(3) < 2.5)
        % If robot is close to the left wall
        cmdstring = [strcat('d1-0.5',num2str(speed)) newline];  % Build command string to move bot
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        disp("4")
    
    elseif (u(1) < 2.5)
        % If robot is close to the right wall
        cmdstring = [strcat('a1-0.5',num2str(speed)) newline];  % Build command string to move bot
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        disp("5")
        
        
    % stuck at a 3 wall corner condition %% 
        
    end
    
    stepcount = stepcount+1;
end