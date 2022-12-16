function [blocking, to_drop_zone, heading] = find_block(u, s_cmd, s_rply, starting_heading, speed, blocking, u_prev)
% u5_lower = u(5)*0.85;
% u5_upper = u(5)*1.15;
cw = 1;
starting_pos = [0, 0, starting_heading];
heading = [0, 0, starting_heading];
steppers = 0;

% for testing = 1:90
%     rotate(s_cmd, s_rply, cw)
%     heading(3) = heading(3) + 2;
%     starting_pos(3) = starting_pos(3) + 2
% end

if starting_pos(3) == 360
    starting_pos(3) = 0;
end


while blocking
    %%[u, s_cmd, s_rply, u_prev] = get_u_block(s_cmd, s_rply, u_prev, blocking)
    disp("we are blocking");
    [u, s_cmd, s_rply, len, u_prev] = comm_testing(s_cmd, s_rply, u_prev)
    if u(6) == 0
        u(6) == u(5);
        u_prev(6) == u_prev(5);
    end
    disp("got u values");
    blocking_str = num2str(blocking);
    cmdstring = [blocking_str newline];             % Build command string to move bot
    reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    
    
    
    u6_lower = u(6)*0.85;
    u6_upper = u(6)*1.15;
    if (u(5) <= u6_upper) && (u(5) >= u6_lower)
        
        rotate(s_cmd, s_rply, cw);
        heading(3) = heading(3) + 2
        disp('rotating')
        proceed = 'y';
        cmdstring = [proceed newline];
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
    else
        rotate(s_cmd, s_rply, cw);
        while u(6) >= 5
            %%cmdstring = ['ua' newline];
            %%u = tcpclient_write(cmdstring, s_cmd, s_rply)
            [u, s_cmd, s_rply, u_prev] = get_u_block(s_cmd, s_rply, u_prev, blocking)
            pos = move_forward(starting_pos, speed, s_cmd, s_rply);
            steppers = steppers + 1
            disp('moving towards block')
        end
        blocking = 0;
        blocking_str = '9';  %% start grabbing
        cmdstring = [blocking_str newline];             % Build command string to move bot
        reply = tcpclient_write(cmdstring, s_cmd, s_rply);
        
        disp('at the block, going back now')
        %%run go back function
        
        %% going back once we have the block
        %read arduino command : grabbed
        %grabbed = tcp read () 
        % while grabbed = 0
        % tcp read ()
        % end
        
        grr = tcpserver_read(s_cmd);
        grr_num = str2num(grr);
        while grr_num == 11
            grr = tcpserver_read(s_cmd);
            grr_num = str2num(grr);
        end
        
        go_back(starting_pos(3), heading(3), steppers, s_cmd, s_rply, speed);
        disp('i am back, time to go to drop zone')
       
        to_drop_zone = 1;
        
    end
end
end

