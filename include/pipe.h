#ifndef PIPE_H
#define PIPE_H
#include "parser_nodes.h"


void exec_pipe_redir(struct node_s *node, t_data *data);
void	first_child(struct node_s *node, int pipe_fd[2], t_data *data);
void	second_child(struct node_s *node, int pipe_fd[2], t_data *data);
void execute_pipe_command(struct node_s *node, t_data *data);


#endif