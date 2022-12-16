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
u = [0,0,0,0,0,0];  % Ultrasonic measurements
pos = [0,0,0];  % Position (x,y,rotation)
speed = 2;
rot_stuck = 90;
stepcount = 0;

while 1
    str = input('enter message: ', 's');
    
    %Check if user wants to exit
    if strcmp(str,'exit')
        disp('Exiting program after closing all connections...')
        fclose(s_cmd);
        delete(instrfindall);
        break;
    end
    
    cmdstring = [str newline]; 
    reply = tcpclient_write(cmdstring, s_cmd, s_rply);

    disp(reply)
end