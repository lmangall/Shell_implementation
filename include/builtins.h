#ifndef BUILTINS_H
# define BUILTINS_H

#include "node.h"
#include "../include/main.h"

int	check_for_builtins(char *line, t_data *data);
int do_cd_builtin(char **argv, t_data *data);
int do_echo_builtin(char **argv);
int do_pwd_builtin(t_data *data);
int do_env_builtin(t_data *data);

#endif