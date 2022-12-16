function [pos] = move_forward(prev_pos, speed, s_cmd, s_rply)
%   moving in our heading direction lol yay so fun 

pos = prev_pos;

if pos(3) == 0
    cmdstring = [strcat('d1-0.5',num2str(speed)) newline];             % Build command string to move bot
    reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    pos(1) = prev_pos(1) + 0.5

        
elseif pos(3) == 90
    cmdstring = [strcat('w1-0.5',num2str(speed)) newline];             % Build command string to move bot
    reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    pos(1) = prev_pos(2) + 0.5


elseif pos(3) == 180
    cmdstring = [strcat('a1-0.5',num2str(speed)) newline];             % Build command string to move bot
    reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    pos(1) = prev_pos(1) - 0.5

    
elseif pos(3) == 270
    cmdstring = [strcat('s1-0.5',num2str(speed)) newline];             % Build command string to move bot
    reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    pos(1) = prev_pos(2) - 0.5

end

end

