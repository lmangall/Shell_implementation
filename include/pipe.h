#ifndef PIPE_H
#define PIPE_H
#include "node.h"


void exec_pipe_redir(struct node_s *node);
void	first_child(struct node_s *node, int pipe_fd[2]);
void	second_child(struct node_s *node, int pipe_fd[2]);
void execute_pipe_command(struct node_s *node);


#endif