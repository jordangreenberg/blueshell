function [u] = collectData(s_cmd)
% Read received data and store it in the UserData property on the bluetooth object
    
u = fscanf(s_cmd, '%d');


end

