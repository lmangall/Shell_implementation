#ifndef BUILTINS_H
# define BUILTINS_H

#include "node.h"
#include "../include/shell.h"

//builtins
int do_cd_builtin(struct node_s *path, t_data *data);
int contains_cd(struct node_s *node);

void do_echo_builtin(char **argv);

#endif