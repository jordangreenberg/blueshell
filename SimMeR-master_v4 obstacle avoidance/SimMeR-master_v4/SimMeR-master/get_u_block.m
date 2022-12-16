function [u, s_cmd, s_rply, u_prev] = get_u_block(s_cmd, s_rply, u_prev, blocking)

[u, s_cmd, s_rply, u_prev] = comm_testing(s_cmd, s_rply, u_prev);


blocking_str = num2str(blocking);
cmdstring = [blocking_str newline];             % Build command string to move bot
reply = tcpclient_write(cmdstring, s_cmd, s_rply);



%%fclose(s_cmd);

end

