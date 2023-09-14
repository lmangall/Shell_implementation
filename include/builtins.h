#ifndef BUILTINS_H
# define BUILTINS_H

#include "node.h"
#include "../include/shell.h"

//builtins
void do_cd_builtin(char **argv, t_data *data);

void do_echo_builtin(char **argv);

void do_pwd_builtin(t_data *data);

void do_env_builtin(t_data *data);

#endif