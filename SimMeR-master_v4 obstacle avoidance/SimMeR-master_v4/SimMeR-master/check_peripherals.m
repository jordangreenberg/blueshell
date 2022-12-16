function [pos, step_out, state] = check_peripherals(u, u_prev, pos, step, state, speed, s_cmd, s_rply)
%UNTITLED2 Summary of this function goes here
%   this function will check the peripherals of the robot. need to consider
%   which direction the robot is moving, ie the heading and then check.
%   this will prevent us from getting stuck

% call the clearance function in this function

step_out = step;
disp('checking peripherals')
% if step >= 12
%     if (pos(3) == 0) || (pos(3) == 180)
%         disp('moving horizontal')
%         if u(2) > (u_prev(2) + 12)
%             state = 1;
%             disp('in loop')
%             if state == 1
%                 disp('clearancee')
%                 [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state);
%             end
%             pos(3) = 90;
%             step_out = 0;
%         elseif u(4) > (u_prev(4) + 12)
%             state = 1;
%             disp('in loop')
%             if state == 1
%                 disp('clearancee')
%                 [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state);
%             end
%             pos(3) = 270;
%             step_out = 0;
%         else
%             pos(3) = pos (3);
%         end
%     elseif (pos(3) == 90) || (pos(3) == 270)
%         if u(3) > (u_prev(3) + 12)
%             state = 1;
%             if state == 1
%                 [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state);
%             end
%             pos(3) = 180;
%             step_out = 0;
%         elseif u(1) > (u_prev(1) + 12)
%             state = 1;
%             if state == 1
%                 [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state);
%             end
%             pos(3) = 0;
%             step_out = 0;
%         else
%             pos(3) = pos(3);
%         end
%     end
    if (pos(3) == 0) || (pos(3) == 180)
        %need to check u2 and u4
        if (pos(3) == 0) && (u(1) > 12)
            %if the way we are going is clear
            pos(3) = pos(3);
        elseif (pos(3) == 180) && (u(3) > 12)
            pos(3) = pos(3);
        elseif u(2) > 3*(u(1)) || u(2) > 3*(u(3))
            %going up takes priotity over going down if in a big open corridor
            state = 1;
            disp('checking clearance')
            if state == 1
                [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state, u_prev);
            end
            pos(3) = 90;
            step_out = 0;
        elseif u(4) > 3*(u(1)) || u(4) > 3*(u(3))
            state = 1;
            disp('checking clearance')
            if state == 1
                [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state, u_prev);
            end
            pos(3) = 270;
            step_out = 0;
        else
            pos(3) = pos(3);
        end
    end
    
    if (pos(3) == 90) || (pos(3) == 270)
        if (pos(3) == 90) && (u(2) > 12)
            %if the way we are going is clear
            pos(3) = pos(3);
        elseif (pos(3) == 270) && (u(4) > 12)
            pos(3) = pos(3);
            %need to check u3 and u1
        elseif u(3) > 3*(u(2)) || u(3) > 3*(u(4))
            state = 1;
            disp('checking clearance')
            if state == 1
                [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state, u_prev);
            end
            pos(3) = 180;
            step_out = 0;
           
        elseif u(1) > 3*(u(2)) || u(1) > 3*(u(4))
            state = 1;
            disp('checking clearance')
            if state == 1
                [pos, state] = clearance(u, pos, speed, s_cmd, s_rply, state, u_prev);
            end
            pos(3) = 0;
            step_out = 0;
            
        else
            pos(3) = pos(3);
        end
        
    end
    
end





