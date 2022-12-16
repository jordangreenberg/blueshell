function [new_rot, step_out] = check_peripherals(u, rot, step)
%UNTITLED2 Summary of this function goes here
%   this function will check the peripherals of the robot. need to consider
%   which direction the robot is moving, ie the heading and then check.
%   this will prevent us from getting stuck

% call the clearance function in this function

step_out = step;
new_rot = rot;

if step >= 15
    if (rot == 0) || (rot == 180)
        %need to check u2 and u4
        if (rot == 0) && (u(1) > 12)
            %if the way we are going is clear
            new_rot = rot;
        elseif (rot == 180) && (u(3) > 12)
            new_rot = rot;
        elseif u(2) > 3*(u(1)) || u(2) > 3*(u(3))
            %going up takes priotity over going down if in a big open corridor
            new_rot = 90;
            step_out = 0;
        elseif u(4) > 3*(u(1)) || u(4) > 3*(u(3))
            new_rot = 270;
            step_out = 0;
        else
            new_rot = rot;
        end
    end
    
    if (rot == 90) || (rot == 270)
        if (rot == 90) && (u(2) > 12)
            %if the way we are going is clear
            new_rot = rot;
        elseif (rot == 270) && (u(4) > 12)
            new_rot = rot;
            %need to check u3 and u1
        elseif u(3) > 3*(u(2)) || u(3) > 3*(u(4))
            new_rot = 180;
            step_out = 0;
        elseif u(1) > 3*(u(2)) || u(1) > 3*(u(4))
            new_rot = 0;
            step_out = 0;
        else
            new_rot = rot;
        end
        
    end
    
end


end

