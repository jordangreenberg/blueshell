function [] = rotate(s_cmd, s_rply, cw)
%UNTITLED3 Summary of this function goes here
%   will rotate by 2 degrees in the clockwise direction

if cw == 1
    disp("sending counter clockwise");
    cw_str = 6;
    cmdstring = [cw_str newline];             % Build command string to move bot
    reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    %pause(0.5);
elseif cw == 0
    disp("sending clockwise");
    ccw_str = 7;
    cmdstring = [ccw_str newline];             % Build command string to move bot
    reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    %pause(0.5);
end

end

