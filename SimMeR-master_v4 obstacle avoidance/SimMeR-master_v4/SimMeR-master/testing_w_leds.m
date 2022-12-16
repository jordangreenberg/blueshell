%%function [u, s_cmd, s_rply, u_prev] = get_u_values(s_cmd, s_rply, u_prev)

clc, clear all
delete(instrfind({'Port'},{'COM6'}));

s_cmd=serial('COM6','BAUD', 9600);
set(s_cmd,'BaudRate', 9600);

s_rply = s_cmd;
set(s_rply, 'BaudRate', 9600);

fopen(s_cmd);
s_cmd.ReadAsyncMode='continuous';

s_cmd.BytesAvailable;
%%speed = 2;
u_prev = zeros(1,5);


    
    
    for i = 1:50
        [u, s_cmd, s_rply, len, u_prev] = comm_testing(s_cmd, s_rply, u_prev);
    if len >= 5
        if u(1) < 10
            heading = 1;
            str_heading = num2str(heading);
            cmdstring = [str_heading newline];
            flushinput(s_cmd);
            reply = tcpclient_write(cmdstring, s_cmd, s_rply);
            %%%fwrite(x, heading);
            disp('in u1 loop')
        elseif u(2) < 10
            heading = 2;
            %%fprintf(s_cmd,heading);
            str_heading = num2str(heading);
            cmdstring = [str_heading newline];
            flushinput(s_cmd);
            reply = tcpclient_write(cmdstring, s_cmd, s_rply);
            disp('in u2 loop')
        elseif u(3) < 10
            heading = 3;
            %%fprintf(s_cmd,heading);
            str_heading = num2str(heading);
            cmdstring = [str_heading newline];
            flushinput(s_cmd);
            reply = tcpclient_write(cmdstring, s_cmd, s_rply);
            disp('in u3 loop')
        elseif u(4) < 10
            heading = 4;
            %%fprintf(s_cmd,heading);
            str_heading = num2str(heading);
            cmdstring = [str_heading newline];
            flushinput(s_cmd);
            reply = tcpclient_write(cmdstring, s_cmd, s_rply);
            disp('in u4 loop')
        elseif u(5) < 10
            heading = 5;
            %%fprintf(s_cmd,heading);
            str_heading = num2str(heading);
            cmdstring = [str_heading newline];
            flushinput(s_cmd);
            reply = tcpclient_write(cmdstring, s_cmd, s_rply);
            disp('in u5 loop')
        else
            heading = 6;
            %%fprintf(s_cmd,heading);
            str_heading = num2str(heading);
            cmdstring = [str_heading newline];
            flushinput(s_cmd);
            reply = tcpclient_write(cmdstring, s_cmd, s_rply);
            disp('in 666666666 loop')
        end
%     elseif blocking == 1
%         heading = 5;
%         %%fprintf(s_cmd,heading);
%         str_heading = num2str(heading);
%         cmdstring = [str_heading newline];
%         reply = tcpclient_write(cmdstring, s_cmd, s_rply);
%         disp('in u5 loop')
%     end
    
    end

%%fclose(s_cmd);

end