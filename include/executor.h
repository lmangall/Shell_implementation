#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "node.h"


char* search_path(char* cmd);
int do_exec_cmd(char** argv);

int do_simple_command(struct node_s *root_node);
int do_simple_command_former(struct node_s *node);


#endif