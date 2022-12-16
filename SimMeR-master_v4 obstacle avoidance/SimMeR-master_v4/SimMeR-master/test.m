% Copyright (c) 2020, Ian G. Bennett
% All rights reserved.
% Development funded by the University of Toronto, Department of Mechanical
% and Industrial Engineering.
% Distributed under GNU AGPLv3 license.

delete(instrfind({'Port'},{'COM6'}));

clear
close all
clc

sim = 0; %% CHANGE THIS TO 0 TO USE REAL LIFE

if sim
    % Initialize tcp server to read and respond to algorithm commands
    [s_cmd, s_rply] = tcp_setup();
    fopen(s_cmd);
    %fopen(s_rply);
else
    % connect to Bluetooth
    %btInfo = instrhwinfo('Bluetooth','ROB6') % or usb com port
    %%hc06 = bluetooth("HC-06-blueshell", 1); %%first = device name or address, second = SPP channel #
    %s_cmd = Bluetooth(btInfo.RemoteID, 1);
    %fopen(s_cmd);
    %s_rply = s_cmd;
    
    s_cmd=serial('COM6','BAUD', 9600);
    set(s_cmd,'BaudRate', 9600);
    
    s_rply = s_cmd;
    set(s_rply, 'BaudRate', 9600);
    
    fopen(s_cmd);
    s_cmd.ReadAsyncMode='continuous';
    
    s_cmd.BytesAvailable;
    %%speed = 2;
    u_prev = zeros(1,5);
end

% Robot Sensor Measurements
u = [0,0,0,0,0];  % Ultrasonic measurements
pos = [0,0,0];  % Position (x,y,rotation)
%%curr_pos = [2 7];    %%%%%%% for testing to loading zone, take this out
curr_pos = [1 2];
speed = 2;
rot_stuck = 90;
stepcount = 0;
step = 0;
state = 0;
oriented_state = 0;
next_move = pos(3);
is_correction = 0;
is_localized = 1; %%% SHOULD BE 0 %%%%%%%%%%%%%%%%%%%%%
set_drop_zone = 1;   % SET BASED ON TA INPUT
to_loading_zone = 0;  % SHOULD BE 1
to_drop_zone = 1;   % SHOULD BE 0
blocking = 0;  %% SHOULD BE 0
cw = 0;

disp("set paramters");

% Path Planning
% to loading zone
LZ_path = [0 0 1 2 1000 6 1000 8; 0 0 1000 3 4 5 6 7; 1 10000 5 1000 1000 6 1000 9; 2 3 4 5 6 7 1000 10];
if set_drop_zone == 1
    % maze path 1
    mazepath_dropzone = [8 7 1000 1000 1000 1000 1000 1000; 5 6 1000 1000 1000 1000 1000 1000; 4 1000 0 1000 1000 1000 1000 1000; 3 2 1 1000 1000 1000 1000 1000];
elseif set_drop_zone == 2
    %maze path 2 a & b
    mazepath_dropzone = [11 6 5 4 1000 0 1000 1000; 10 11 1000 3 2 1 1000 1000; 9 1000 1000 1000 1000 2 1000 1000; 8 7 6 5 4 3 1000 1000];
elseif set_drop_zone == 3
    %maze path 3 a & b
    mazepath_dropzone = [13 8 7 6 1000 1000 1000 0; 12 13 1000 5 4 3 2 1; 11 1000 1000 1000 1000 4 1000 1000; 10 9 8 7 6 5 1000 1000];
elseif set_drop_zone == 4
    %maze path 4 a & b
    mazepath_dropzone = [14 9 8 7 1000 1000 1000 1000; 13 14 1000 6 5 4 3 2; 12 1000 1000 1000 1000 5 1000 1; 11 10 9 8 7 6 1000 0];
end

disp("set zone paths")

%initalization of the world
dim1 = 32; dim2 = 16; 
locationindex = reshape(1:dim1*dim2,dim1,dim2)'; 
n = numel(locationindex);
rand('twister',5489);
bw = reshape(randi([0 1],n,1),dim2,dim1); %0 = black, 1 = white

%make blocks
M = zeros(size(bw));
Blocks = [2, 3; 3, 2; 4, 3; 5, 1; 5, 3; 7, 1; 7, 3; 7, 4;];
for xx = 1:size(Blocks,1)
	x = Blocks(xx,1); y = Blocks(xx,2);
	M(1+(y-1)*4:(y-1)*4+4, 1+(x-1)*4:(x-1)*4+4) = 1;
end
M = [ones(dim2,1) M ones(dim2,1)];
M = [ones(1, dim1+2); M; ones(1, dim1+2)];

%generate ultrasonic world
ultra = zeros(size(bw));
for sec_row = 1:4:dim2
    for sec_col = 1:4:dim1
        segRow = M(sec_row+2, sec_col:sec_col+5);
        segCol = M(sec_row:sec_row+5, sec_col+2);
        val = sum(segRow)+sum(segCol);
        if val == 2 && sum(segRow)~=1
            val = 5;
        end
        ultra(sec_row:sec_row+3, sec_col:sec_col+3) = val;
    end
end

%create mask for blocks
M = abs(M-1);
M = M(2:end-1, 2:end-1);

figure(2); imagesc((bw+1).*M); colormap(gray);

%initialize probability
p = ones(dim2,dim1)*(1/n); 

disp("set localization things");

while 1
    disp("enters while loop");
    % Take Measurements
    %for ct = 1:6
    %    cmdstring = [strcat('u',num2str(ct)) newline];
    %    u(ct) = tcpclient_write(cmdstring, s_cmd, s_rply);
    %end
    u_prev = u;
    heading = pos(3);
    [u, s_cmd, s_rply, len, u_prev] = comm_testing(s_cmd, s_rply, u_prev);
    disp("asks for u vals");
    %cmdstring = ['ua' newline]; %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    %u = tcpclient_write(cmdstring, s_cmd, s_rply);%%%%%%%%%%%%%%%%%%%%%%%%
    %u = collectData(s_cmd)
    
    %ir = tcpclient_write(['i1' newline], s_cmd, s_rply);
    
    %comp = tcpclient_write(['c1' newline], s_cmd, s_rply);
    
    % Display Values
    disp('Ultrasonic')
    disp(u)
    
%     while oriented_state == 0
%         cmdstring = ['ua' newline];
%         u = tcpclient_write(cmdstring, s_cmd, s_rply)
%         [pos, oriented_state] = orient(pos, u, s_cmd, s_rply, cw);
%         disp('uhh')
%     end
    
    
    if is_localized == 1 && to_loading_zone == 1
        %% if we are localized and we are heading to the loading zone
        while to_loading_zone
            disp('heading to the loading zone')
            
            [pos(3), to_loading_zone] = pathfind_toLZ(curr_pos, LZ_path);
            if pos(3) == 0
                %we are moving in the right direction
                %%u_prev = u;
                %%disp(curr_pos)
                %%disp(pos(3))
                heading = pos(3)
                %%disp(heading)
                for i = 1:2
                    is_correction = 0;
                    [pos] = move_forward(pos, speed, s_cmd, s_rply);
                    [pos] = move_forward(pos, speed, s_cmd, s_rply);
                    step = step + 1;
                    %%disp("1 but localized")
                    next_move = pos(3);
                    %%pause(2)
                    
                    hold = tcpserver_read(s_cmd);
                    hold_num = str2double(hold);
                    while hold_num == 69
                        hold = tcpserver_read(s_cmd);
                        hold_num = str2double(hold);
                    end
                    
                end
                curr_x = curr_pos(1);
                curr_y = curr_pos(2);
                curr_pos = [curr_x, curr_y+1];
                
            elseif pos(3) == 90
                for i = 1:2
                    heading = pos(3)
                    [pos] = move_forward(pos, speed, s_cmd, s_rply);
                    is_correction = 0;
                    step = step + 1;
                    %%disp("11 but localized")
                    next_move = pos(3);
                    %pause(2)
                    hold = tcpserver_read(s_cmd);
                    hold_num = str2double(hold);
                    while hold_num == 69
                        hold = tcpserver_read(s_cmd);
                        hold_num = str2double(hold);
                    end
                end
                curr_x = curr_pos(1);
                curr_y = curr_pos(2);
                curr_pos = [curr_x-1, curr_y];
                
            elseif pos(3) == 180
                for i = 1:2
                    heading = pos(3)
                    [pos] = move_forward(pos, speed, s_cmd, s_rply);
                    is_correction = 0;
                    step = step + 1;
                    %%disp("111 but localized")
                    next_move = pos(3);
                    %pause(2)
                    hold = tcpserver_read(s_cmd);
                    hold_num = str2double(hold);
                    while hold_num == 69
                        hold = tcpserver_read(s_cmd);
                        hold_num = str2double(hold);
                    end
                end
                curr_x = curr_pos(1);
                curr_y = curr_pos(2);
                curr_pos = [curr_x, curr_y-1];
                
            elseif pos(3) == 270
                for i = 1:2
                    heading = pos(3)
                    [pos] = move_forward(pos, speed, s_cmd, s_rply);
                    is_correction = 0;
                    step = step + 1;
                    %pause(2)
                    %%disp("1111 but localized")
                    hold = tcpserver_read(s_cmd);
                    hold_num = str2double(hold);
                    while hold_num == 69
                        hold = tcpserver_read(s_cmd);
                        hold_num = str2double(hold);
                    end
                end
                curr_x = curr_pos(1);
                curr_y = curr_pos(2);
                curr_pos = [curr_x+1, curr_y];
            end
        end
        
        loading_str = '5';
        cmdstring = [loading_str newline];             % Build command string to move bot
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        
        disp('in the loading zone now hehe')
        blocking = 1;
        
    elseif is_localized == 1 && to_drop_zone == 1
        %% if we are localized and we are heading from the loading zone to the drop zone
        
        while to_drop_zone
            disp('dropping now')
            
            drop_str = '8';    %% go to drop
            
            cmdstring = [drop_str newline];             % Build command string to move bot
            reply = tcpclient_write(cmdstring, s_cmd, s_rply);
            
            [pos(3), to_drop_zone] = pathfind_toDrop(curr_pos, mazepath_dropzone);
        if pos(3) == 0
            %we are moving in the right direction
            %%u_prev = u;
            for i = 1:2
            is_correction = 0;
            [pos] = move_forward(pos, speed, s_cmd, s_rply);
            %pause(1)
            step = step + 1;
            %%disp("1 but localized and droppy drop")
            next_move = pos(3);
            hold = tcpserver_read(s_cmd);
            hold_num = str2double(hold);
            while hold_num == 13
                hold = tcpserver_read(s_cmd);
                hold_num = str2double(hold);
            end
            end
            curr_x = curr_pos(1);
            curr_y = curr_pos(2);
            curr_pos = [curr_x, curr_y+1];
                    
        elseif pos(3) == 90
            for i = 1:2
            [pos] = move_forward(pos, speed, s_cmd, s_rply);
            %pause(1)
            is_correction = 0;
            step = step + 1;
            %%disp("11 but localized & drop it low")
            next_move = pos(3);
            hold = tcpserver_read(s_cmd);
            hold_num = str2double(hold);
            while hold_num == 13
                hold = tcpserver_read(s_cmd);
                hold_num = str2double(hold);
            end
            end
            curr_x = curr_pos(1);
            curr_y = curr_pos(2);
            curr_pos = [curr_x-1, curr_y];
                    
        elseif pos(3) == 180
            for i = 1:2
            [pos] = move_forward(pos, speed, s_cmd, s_rply);
            %pause(1)
            is_correction = 0;
            step = step + 1;
            %%disp("111 but localized & drop it low gilr")
            next_move = pos(3);
            hold = tcpserver_read(s_cmd);
            hold_num = str2double(hold);
            while hold_num == 13
                hold = tcpserver_read(s_cmd);
                hold_num = str2double(hold);
            end
            end
            curr_x = curr_pos(1);
            curr_y = curr_pos(2);
            curr_pos = [curr_x, curr_y-1];
        
        elseif pos(3) == 270
            for i = 1:2
            [pos] = move_forward(pos, speed, s_cmd, s_rply);
            %pause(1);
            is_correction = 0;
            step = step + 1;
            %%disp("1111 but localized & drop that ass")
            hold = tcpserver_read(s_cmd);
            hold_num = str2double(hold);
            while hold_num == 13
                hold = tcpserver_read(s_cmd);
                hold_num = str2double(hold);
            end
            end
            curr_x = curr_pos(1);
            curr_y = curr_pos(2);
            curr_pos = [curr_x+1, curr_y];
        end
        end
        
        disp('we dropped')
        dropping_str = 'a';
        cmdstring = [dropping_str newline];             % Build command string to move bot
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        
%         dropped_str = "done";
%         cmdstring = [dropped_str newline];             % Build command string to move bot
%         reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    end
        
    %%blocking = 1;
    if blocking == 1
        disp('time to block')
            
        starting_heading = pos(3);
        
        [blocking, to_drop_zone, pos] = find_block(u, s_cmd, s_rply, starting_heading, speed, blocking, u_prev);
    end

    %% MOVEMENT LOGIC
    
    if  (u(5) > 5) && (u(2) > 5) && (u(3) > 5) && (u(4) > 5)
        % If the way ahead is clear, go forward
        disp("it is doing the right thing")
        if pos(3) == 0
            %we are moving in the right direction
            %%u_prev = u;
            is_correction = 0;
            [pos] = move_forward(pos, speed, s_cmd, s_rply);
            step = step + 1;
            disp("1")
            if is_localized == 0
                [p, heading, num_walls, is_localized, curr_pos] = localization(u, pos, next_move, stepcount, p, M, ultra, dim1, dim2, n, s_cmd, s_rply);
            end
            [pos, step, state] = check_peripherals(u, u_prev, pos, step, state, speed, s_cmd, s_rply);
            next_move = pos(3);
            %[p, heading] = localization(u, pos, next_move);
            if state == 1
                [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state);
            end
            %%if check peripherals and it is clear, call clearance ^^ 
        
        elseif pos(3) == 90
            [pos] = move_forward(pos, speed, s_cmd, s_rply);
            %%u_prev = u;
            is_correction = 0;
            step = step + 1;
            disp("11")
            if is_localized == 0
                [p, heading, num_walls, is_localized, curr_pos] = localization(u, pos, next_move, stepcount, p, M, ultra, dim1, dim2, n, s_cmd, s_rply);
            end
            [pos, step, state] = check_peripherals(u, u_prev, pos, step, state, speed, s_cmd, s_rply);
            next_move = pos(3);
            %[p, heading] = localization(u, pos, next_move);
            if state == 1
                [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state);
            end
        
        elseif pos(3) == 180
            [pos] = move_forward(pos, speed, s_cmd, s_rply);
            %%u_prev = u;
            is_correction = 0;
            step = step + 1;
            disp("111")
            if is_localized == 0
                [p, heading, num_walls, is_localized, curr_pos] = localization(u, pos, next_move, stepcount, p, M, ultra, dim1, dim2, n, s_cmd, s_rply);
            end
            next_move = pos(3);
            %[p, heading] = localization(u, pos, next_move);
            if state == 1
                [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state);
            end
        
        elseif pos(3) == 270
            [pos] = move_forward(pos, speed, s_cmd, s_rply);
            %%u_prev = u;
            is_correction = 0;
            step = step + 1;
            disp("1111")
            if is_localized == 0
                [p, heading, num_walls, is_localized, curr_pos] = localization(u, pos, next_move, stepcount, p, M, ultra, dim1, dim2, n, s_cmd, s_rply);
            end
            [pos, step, state] = check_peripherals(u, u_prev, pos, step, state, speed, s_cmd, s_rply);
            next_move = pos(3);
            %[p, heading] = localization(u, pos, next_move);
            if state == 1
                [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state);
            end
        end
    elseif (u(2) < 5) && (u(3) < 5) && (u(5) < 5)
        pos(3) = 270; % or tell to rotate 180?
        is_correction = 0;
        next_move = pos(3);
        cmdstring = [strcat('s1-0.5',num2str(speed)) newline];
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        if is_localized == 0
                [p, heading, num_walls, is_localized, curr_pos] = localization(u, pos, next_move, stepcount, p, M, ultra, dim1, dim2, n, s_cmd, s_rply);
        end
        %[p, heading] = localization(u, pos, next_move);
        disp("231")
        
    elseif (u(4) < 5) && (u(3) < 5) && (u(5) < 5)
        pos(3) = 90;
        is_correction = 0;
        next_move = pos(3);
        cmdstring = [strcat('w1-0.5',num2str(speed)) newline];
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        if is_localized == 0
                [p, heading, num_walls, is_localized, curr_pos] = localization(u, pos, next_move, stepcount, p, M, ultra, dim1, dim2, n, s_cmd, s_rply);
        end
        disp("431")
        
    elseif (u(3) < 5) && (u(4) < 5) && (u(2) < 5)
        pos(3) = 0;
        is_correction = 0;
        next_move = pos(3);
        cmdstring = [strcat('d1-0.5',num2str(speed)) newline];
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        if is_localized == 0
                [p, heading, num_walls, is_localized, curr_pos] = localization(u, pos, next_move, stepcount, p, M, ultra, dim1, dim2, n, s_cmd, s_rply);
        end
        disp("342")
        
    elseif (u(5) < 5) && (u(4) < 5) && (u(2) < 5)
        pos(3) = 180;
        is_correction = 0;
        next_move = pos(3);
        cmdstring = [strcat('a1-0.5',num2str(speed)) newline];
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        if is_localized == 0
                [p, heading, num_walls, is_localized, curr_pos] = localization(u, pos, next_move, stepcount, p, M, ultra, dim1, dim2, n, s_cmd, s_rply);
        end
        disp("142")        
        
    elseif (u(2) < 2.5)
        is_correction = 1;
        % If robot is close to the forward wall
        cmdstring = [strcat('s1-0.5',num2str(speed)) newline];  % Build command string to move bot
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        disp("2")
        
    elseif (u(4) < 2.5)
        is_correction = 1;
        % If robot is close to the back wall
        cmdstring = [strcat('w1-0.5',num2str(speed)) newline];  % Build command string to move bot
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        disp("3")
        
    elseif (u(3) < 2.5)
        is_correction = 1;
        % If robot is close to the left wall
        cmdstring = [strcat('d1-0.5',num2str(speed)) newline];  % Build command string to move bot
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        disp("4")
        
    elseif (u(5) < 2.5)
        is_correction = 1;
        % If robot is close to the right wall
        cmdstring = [strcat('a1-0.5',num2str(speed)) newline];  % Build command string to move bot
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        disp("5")
        
        
    end
    
    stepcount = stepcount+1;
end