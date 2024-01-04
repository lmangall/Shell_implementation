#ifndef SIGNALS_H
#define SIGNALS_H

void handle_ctrl_c(int sig);
void handle_ctrl_backslash(int sig);
void handle_ctrl_d(int sig);
void handle_ctrl_c_heredoc(int sig);
void	handle_ctrl_c_simple_command(int sig);

#endif