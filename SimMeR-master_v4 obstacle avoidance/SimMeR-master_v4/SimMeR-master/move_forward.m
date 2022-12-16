function [pos] = move_forward(prev_pos, speed, s_cmd, s_rply)
%   moving in our heading direction lol yay so fun 

pos = prev_pos;

if pos(3) == 0
    
    heading = 1;
    strheading = num2str(heading);
    cmdstring = [strheading newline];
    reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    disp("should be sent");
    %cmdstring = [strcat('d1-',num2str(speed)) newline];             % Build command string to move bot
    %reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    pos(1) = prev_pos(1) + 0.5;
    %pause(1);
    
    
    %heading = 90;
%             str_heading = num2str(heading);
%             cmdstring = [str_heading newline];
%             reply = tcpclient_write(cmdstring, s_cmd, s_rply);

        
elseif pos(3) == 90
    
    heading = 2;
    strheading = num2str(heading);
    cmdstring = [strheading newline];
    reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    %cmdstring = [strcat('w1-',num2str(speed)) newline];             % Build command string to move bot
    %reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    pos(2) = prev_pos(2) + 0.5;
    %pause(1);


elseif pos(3) == 180
    
    heading = 3;
    strheading = num2str(heading);
    cmdstring = [strheading newline];
    reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    %cmdstring = [strcat('a1-',num2str(speed)) newline];             % Build command string to move bot
    %reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    pos(1) = prev_pos(1) - 0.5;
    %pause(1);

    
elseif pos(3) == 270
    
    heading = 4;
    strheading = num2str(heading);
    cmdstring = [strheading newline];
    reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    %cmdstring = [strcat('s1-',num2str(speed)) newline];             % Build command string to move bot
    %reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    pos(2) = prev_pos(2) - 0.5;
    %pause(1);

end

end

