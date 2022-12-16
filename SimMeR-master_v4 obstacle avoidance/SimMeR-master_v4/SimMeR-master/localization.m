function [p, heading, num_walls, is_localized, curr_loc] = localization(u, pos, next_move, stepcount, p, M, ultra, dim1, dim2, n, s_cmd, s_rply)

num_walls = 0;

        
for j = 1:4
    if u(j) < 10
        num_walls = num_walls + 1;
    end
end

heading = pos(3); %270 degrees implied down
%%m_u = [ 3,  3,  3,  1,  1,  1,  1,  5,  5,  5,  5,  0,  0,  0,  0,  5,  5,  5,  5,  2,  2,  2,  2,  2,  2];
%%m_m = ['w','w','w','d','a','d','w','w','w','w','w','w','w','w','w','w','w','w','w','w','d','w','w','w','a'];

%initalization of the world
% dim1 = 32; dim2 = 16; 
% locationindex = reshape(1:dim1*dim2,dim1,dim2)'; 
% n = numel(locationindex);
% rand('twister',5489);
% bw = reshape(randi([0 1],n,1),dim2,dim1); %0 = black, 1 = white
% 
% %make blocks
% M = zeros(size(bw));
% Blocks = [2, 3; 3, 2; 4, 3; 5, 1; 5, 3; 7, 1; 7, 3; 7, 4;];
% for xx = 1:size(Blocks,1),
% 	x = Blocks(xx,1); y = Blocks(xx,2);
% 	M(1+(y-1)*4:(y-1)*4+4, 1+(x-1)*4:(x-1)*4+4) = 1;
% end
% M = [ones(dim2,1) M ones(dim2,1)];
% M = [ones(1, dim1+2); M; ones(1, dim1+2)];
% 
% %generate ultrasonic world
% ultra = zeros(size(bw));
% for sec_row = 1:4:dim2,
%     for sec_col = 1:4:dim1,
%         segRow = M(sec_row+2, sec_col:sec_col+5);
%         segCol = M(sec_row:sec_row+5, sec_col+2);
%         val = sum(segRow)+sum(segCol);
%         if val == 2 && sum(segRow)~=1,
%             val = 5;
%         end
%         ultra(sec_row:sec_row+3, sec_col:sec_col+3) = val;
%     end
% end
% 
% %create mask for blocks
% M = abs(M-1);
% M = M(2:end-1, 2:end-1);
% figure; imagesc((bw+1).*M); colormap(gray);
% 
% %initialize probability
% p = ones(dim2,dim1)*(1/n); 

    figure(3);
    %%if is_correction == 0
        
        %   for j = 1:4
        % if there are zero blocking walls
        if u(1) > 10 && u(2) > 10 && u(3) > 10 && u(4) > 10
            num_walls = 0;
            
        % if there are 2 parallel walls 
        elseif u(2) > 10 && u(4) > 10 && u(3) < 10 && u(1) < 10
            num_walls = 5;
        elseif u(2) < 10 && u(4) < 10 && u(3) > 10 && u(1) > 10
            num_walls = 5;
            
            %3 blocking
        elseif u(1) > 10 && u(2) < 10 && u(3) < 10 && u(4) < 10
            num_walls = 3;
        elseif u(1) < 10 && u(2) > 10 && u(3) < 10 && u(4) < 10
            num_walls = 3;
        elseif u(1) < 10 && u(2) < 10 && u(3) > 10 && u(4) < 10
            num_walls = 3;
        elseif u(1) < 10 && u(2) < 10 && u(3) < 10 && u(4) > 10
            num_walls = 3;
            
            %2 blocking adjascent
        elseif u(1) > 10 && u(2) > 10 && u(3) < 10 && u(4) < 10
            num_walls = 2;
        elseif u(1) < 10 && u(2) > 10 && u(3) > 10 && u(4) < 10
            num_walls = 2;
        elseif u(1) < 10 && u(2) < 10 && u(3) > 10 && u(4) > 10
            num_walls = 2;
        elseif u(1) > 10 && u(2) < 10 && u(3) < 10 && u(4) > 10
            num_walls = 2;
            
            %1 blocking
        elseif u(1) > 10 && u(2) > 10 && u(3) > 10 && u(4) < 10
            num_walls = 1;
        elseif u(1) > 10 && u(2) > 10 && u(3) < 10 && u(4) > 10
            num_walls = 1;
        elseif u(1) > 10 && u(2) < 10 && u(3) > 10 && u(4) > 10
            num_walls = 1;
        elseif u(1) < 10 && u(2) > 10 && u(3) > 10 && u(4) > 10
            num_walls = 1;
        end
        % end
        
        if (num_walls == 3)
            possible_headings = [90, 270];
        else
            possible_headings = [0, 90, 180, 270];
        end
        
       
        maximum_p = [0, 0, 0, 0];
        pos_of_p = [0 0; 0 0; 0 0; 0 0];
        end_heading = [5, 5, 5, 5];
        headd = length(possible_headings);
        %sensor update
        for i = 1:headd                        % where i is each heading
            %%p = ones(dim2,dim1)*(1/n);
            pos_tracker = [];
            
                pos_tracker(stepcount+1) = num_walls;
                p = sense_u(ultra, M, p, num_walls);
                
                imagesc(p);
                title(['step: ' num2str(stepcount)]);
                %%pause;
                
                %movement update
                [p, heading] = move(p, M, possible_headings(i), next_move);
            %%end 
                [maximum_p(i), x, y] = maxavgp(p);
                pos_of_p(i, 1) = x(1);
                pos_of_p(i, 2) = y(1);
                end_heading(i) = possible_headings(i);
        end
         
        
        [Max_p, Pos_p] = max(maximum_p);
        
        if Max_p >= 0.045
            is_localized = 1;
            disp('localized yay')
            loading_str = 0;    %%% localized
            cmdstring = [loading_str newline];             % Build command string to move bot
            reply = tcpclient_write(cmdstring, s_cmd, s_rply);
            curr_loc = [pos_of_p(Pos_p,1), pos_of_p(Pos_p, 2)];
            heading = end_heading(Pos_p);
        else
            is_localized = 0; 
            curr_loc = [0,0];
            disp('lol obvs you;re not localized')
            
        end
end
        
        
        
        
        
        
        