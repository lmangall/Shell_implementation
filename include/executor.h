#ifndef EXECUTOR_H
#define EXECUTOR_H
#include "node.h"


char	*search_path(char *cmd, t_data *data);
int exec_cmd(char** argv, t_data *data);

int do_simple_command(struct node_s *root_node, t_data *data);


#endif