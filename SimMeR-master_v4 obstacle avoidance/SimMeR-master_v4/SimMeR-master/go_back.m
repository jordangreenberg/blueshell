function [] = go_back(starting_heading, heading, steppers, s_cmd, s_rply, speed)
%%this function will make us go back to where we came from bc lol

cw = 1;

if starting_heading == 0
    back_heading = 180;
elseif starting_heading == 90
    back_heading = 270;
elseif starting_heading == 180
    back_heading = 0;
elseif starting_heading == 270
    back_heading = 90;
end
    

for i = 1:(steppers-1)
    temp_heading = [0, 0, back_heading];
    [pos] = move_forward(temp_heading, speed, s_cmd, s_rply);
    disp('moving forward')
end

if (heading - 180) > 0
    heading = heading - 180;
    rotations = (heading - starting_heading)/2;
    for j = 1:rotations
        rotate(s_cmd, s_rply, cw);
        heading = heading - 2;
        disp('rotatinghg')
    end
elseif heading - 180 == 0
    disp('no need to rotate more')
else
    rotations = (heading - starting_heading)/2;
    for j = 1:rotations
        rotate(s_cmd, s_rply, cw);
        heading = heading - 2;
    disp('rotatinghg')
    end
end

% for j = 1:rotations
%     rotate(s_cmd, s_rply, cw);
%     heading = heading - 2;
%     disp('rotatinghg')
% end

end

