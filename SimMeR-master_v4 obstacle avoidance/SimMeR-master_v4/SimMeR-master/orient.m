function [pos, oriented_state] = orient(pos, u, s_cmd, s_rply, cw)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

oriented_state = 0;
%%disp(u)
if (u(4) < 2.98 && u(2) > 14.5)
    oriented_state = 1;
    %%disp('yuh')
elseif (rem((u(2)+u(4) + 6), 12) > 0.02)
    rotate(s_cmd, s_rply, cw)
    %disp(u(1))
    %disp(u(3))
    disp('should be rotating rn lol')
    hhhh = rem((u(2) + u(4) + 6), 12);
else
    oriented_state = 1;
end



end

