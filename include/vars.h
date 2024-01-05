
#ifndef VARS_H
#define VARS_H
#include "node.h"

#define MAX_VARS 100

typedef struct s_vars {
    char name[50];
    char value[100];
} t_vars;

typedef struct s_data {
    char *paths;
    char *envp;
    int num_vars;
    int num_shell_vars;
    int last_command_exit_status;
    t_vars vars_container[MAX_VARS];
    t_vars shell_vars_container[MAX_VARS];
} t_data;


//vars
int     check_for_variable_setting(t_data *data, char *token);
void    init_vars(t_data *data, char **envp);
int     is_valid_variable_declaration(const char *input);
char	**convert_vars_container_to_envp(t_data *data);
//set
int		set_shell_var(t_data *data, const char *name, const char *value);
int     set_var(t_data *data, const char *name, const char *value);
//export
int export_var(t_data *data, const char *name);
int do_export_builtin(char **tokens, t_data *data);
//unset
int unset_shell_var(t_data *data, const char *name);
int	unset_var(t_data *data, const char *name);
int do_unset_builtin(char **tokens, t_data *data);
//utils
char	*return_env_from_container(t_data *data);
int     find_equal_sign(char *str);
//utils_dev
void    print_vars(const t_data *data);
void    print_exported_vars(const t_data *data);

#endif
