function [heading, to_loading_zone] = pathfind_toLZ(curr_pos, LZ_path)

min_a = 0;

to_loading_zone = 1;

i = curr_pos(1);
j = curr_pos(2);

a = zeros(1,4);

if i+1 > 4
    a(3) = 1000;
else
    a(3) = LZ_path(i+1, j);
end

if j+1 > 8
    a(2) = 1000;
else
    a(2) = LZ_path(i, j+1);
end 

if i-1 < 1
    a(1) = 1000;
else
    a(1) = LZ_path(i-1, j);
end

if j-1 < 1
    a(4) = 1000;
else
    a(4) = LZ_path(i, j-1);
end

[m, min_a] = min(a);
disp(a)

if min(a) == 0
    to_loading_zone = 0; %% we have made it to the loading zone
end

if min_a == 1
    heading = 90;
elseif min_a == 2
    heading = 0;
elseif min_a == 3
    heading = 270;
elseif min_a == 4
    heading = 180;
end
disp(heading)

end

