function [u, s_cmd, s_rply, len, u_prev] = comm_testing(s_cmd, s_rply, u_prev)


%         cmdstring = ['ua' newline];
%         u = tcpclient_write(cmdstring, s_cmd, s_rply)

%%[s_cmd, s_rply] = tcp_setup()

%%%clc, clear all
speed = 2;

% s_cmd=serial('COM6','BAUD', 9600);
% s_rply = s_cmd;
% 
% fopen(s_cmd);
% s_cmd.ReadAsyncMode='continuous';
% 
% s_cmd.BytesAvailable;


%cmdstring = [strcat('d1-0.5',num2str(speed)) newline];
%reply = tcpclient_write(cmdstring, s_cmd, s_rply);

%[cmd] = tcpserver_read(s_cmd)
u = zeros(1,6);

    uu = tcpserver_read(s_cmd);
    %%pause(0.3);
        
    ustr = strsplit(uu,',');

    len = length(ustr)
    
    %%while len < 5
        
        if len >= 5
            proceed = 'y';
            disp("yes");
            cmdstring = [proceed newline];
            reply = tcpclient_write(cmdstring, s_cmd, s_rply);
            for j= 1:len
                u(1,j) = str2double(ustr(j));
            end
            u_prev = u;
            
        elseif (len == 1) && (str2double(ustr) == 13)   % from 69
            disp("in the branch")
        %%elseif (len == 1) && (str2double(ustr) == 
        
        else
            %%pause(0.3);
            while len < 6
                u = u_prev;
                disp('uhg');
                proceed = 'n';
                cmdstring = [proceed newline];
                reply = tcpclient_write(cmdstring, s_cmd, s_rply);
                uu = tcpserver_read(s_cmd);
                ustr = strsplit(uu,',');
                len = length(ustr)
                
            end
            proceed = 'y';
        end
    
    %%end



end