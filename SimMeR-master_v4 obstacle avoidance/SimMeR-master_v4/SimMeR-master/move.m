function [pnew, heading] = move(p, mask, heading, Move)
   %models movement error
   K = [0.1 0.1 0.1; 0.1 0.8 0.1; 0.1 0.1 0.1];
   
   %2D convolution
   pnew = conv2(p, K,'same');

   %%disp(['heading: ' num2str(heading)])
   
   %direction  
   if Move == 180
        heading = mod(heading + 90,360);
   elseif Move == 0
		heading = mod(heading - 90,360);
   elseif Move == 270
		heading = mod(heading + 180,360);
   end

%     if Move - 90 == -90
%         temp_Move = 270;
%     elseif Move + 90 == 360
%         temp_Move = 0;
%     else
%         temp_move = Move;

%    if (Move ~= heading) && (temp_move+90 == heading)
%         heading = mod(heading + 90,360)
%    elseif (Move ~= heading) && (temp_move-90 == heading)
% 		heading = mod(heading + 90,360)
%    end
   
   col_move = cosd(heading);
   row_move = sind(heading);
   
   if col_move > 0,
	   pnew = [zeros(size(pnew,1),1) pnew(:,1:end-1)];
   elseif col_move < 0,
	   pnew = [pnew(:,2:end) zeros(size(pnew,1),1)];
   end
   
   if row_move < 0,
	   pnew = [zeros(1,size(pnew,2)); pnew(1:end-1,:)];
   elseif row_move > 0,
	   pnew = [pnew(2:end,:); zeros(1,size(pnew,2))];
   end

   %masking matrix
   pnew = pnew.*mask;

   %normalization
   pnew = pnew/sum(sum(pnew));
   %%disp(['move: ' Move ' heading: ' num2str(heading)])
  
end