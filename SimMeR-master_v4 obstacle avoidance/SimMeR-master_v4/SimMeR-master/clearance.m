function [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state, u_prev)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here
radius = 2;
prev_pos_x = pos(1);
prev_pos_y = pos(2);

if pos(3) == 0
    u_back = u(3);
    u_back_current = u_back;
    while u_back_current <= (u_back + radius)
        disp(u_back_current)
        disp(u_back)
        [pos] = move_forward(pos, speed, s_cmd, s_rply);
        [u, s_cmd, s_rply, len, u_prev] = comm_testing(s_cmd, s_rply, u_prev)
        u_back_current = u_back_current + 0.5;
        disp('clearance')
    end
    state = 0
    disp('left clearance')
    
elseif pos(3) == 90
    u_back = u(4);
    u_back_current = u_back;
    while u_back_current <= (u_back + radius)
        disp(u_back_current)
        disp(u_back)
        [pos] = move_forward(pos, speed, s_cmd, s_rply);
        [u, s_cmd, s_rply, len, u_prev] = comm_testing(s_cmd, s_rply, u_prev)
        
        u_back_current = u_back_current + 0.5;
        disp('clearance')
    end
    state = 0
    disp('left clearance')
elseif pos(3) == 180
    u_back = u(1);
    u_back_current = u_back;
    while u_back_current <= (u_back + radius)
        disp(u_back_current)
        disp(u_back)
        [pos] = move_forward(pos, speed, s_cmd, s_rply);
        [u, s_cmd, s_rply, len, u_prev] = comm_testing(s_cmd, s_rply, u_prev)
        
        u_back_current = u_back_current + 0.5;
        disp('clearance')
    end
    state = 0
    disp('left clearance')
elseif pos(3) == 270
    u_back = u(2);
    u_back_current = u_back;
    while u_back_current <= (u_back + radius)
        disp(u_back_current)
        disp(u_back)
        [pos] = move_forward(pos, speed, s_cmd, s_rply);
        [u, s_cmd, s_rply, len, u_prev] = comm_testing(s_cmd, s_rply, u_prev)
        
        u_back_current = u_back_current + 0.5;
        disp('clearance')
    end
    state = 0
    disp('left clearance')
end

