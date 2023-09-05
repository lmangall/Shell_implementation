#ifndef BACKEND_H
#define BACKEND_H
#include "node.h"


char* search_path(char* cmd);
int do_exec_cmd(char** argv);

void exec_pipe_redir(struct node_s *node);
void	first_child(struct node_s *node, int pipe_fd[2]);
void	second_child(struct node_s *node, int pipe_fd[2]);
void execute_pipe_command(struct node_s *node);


int do_simple_command(struct node_s *root_node);
int do_simple_command_former(struct node_s *node);


#endif