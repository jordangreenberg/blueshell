function [max_PROBval, x, y] = maxavgp(p)
%UNTITLED9 Summary of this function goes here
%   Convultion Step for Average Pooling 

[MatRow, MatCol] = size(p);
avg_factor = 1/16;
new_p = zeros(13,29);

% Avg_Pool = avgpool(p, size(p));

for row = 1:(MatRow - 3)
    for col = 1:(MatCol - 3)
        take_p = p(row:row+3, col:col+3);
        take_p_x = take_p(:);
        sum_take_p_x = sum(take_p_x);
        new_p(row,col) = sum_take_p_x*avg_factor;
    end 
end 

p_new_row = new_p(:);
max_PROBval = max(p_new_row);
[initialx, initialy] = find(new_p == max_PROBval);
%%disp('x & y before ceil')
x(1) = (initialx(1)/3);
y(1) = (initialy(1)/3);

%%disp('x & y valyues')
x(1) = ceil(x);
y(1) = ceil(y);

    
if x(1) > 4
    x(1) = 4;
end

if y(1) > 8
    y(1) = 8;
end
if((x(1)==1) && (y(1)==5||y(1)==7)) || (x(1) == 2 && y(1) == 3) || ((x(1) == 3) && (y(1)==2 ||y(1)==4||y(1)==5||y(1)==7)) || (x(1) == 4 && y(1) == 7)
    x = floor(initialx / 3);
    y = floor(initialy / 3);
end


end