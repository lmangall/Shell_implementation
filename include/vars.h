

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
    t_vars vars_container[MAX_VARS];
    t_vars shell_vars_container[MAX_VARS];
} t_data;

char	*return_env_from_container(t_data *data);

int     find_equal_sign(char *str);
void    init_vars(t_data *data, char **envp);
void    print_vars(const t_data *data);

int     set_var(t_data *data, const char *name, const char *value);
int     unset_var(t_data *data, const char *name);

int     export_var(t_data *data, const char *name);
void    print_exported_vars(const t_data *data);


int     isValidVariableDeclaration(const char *input);
int     check_for_variable_setting(t_data *data, char *token);
int		do_unset_builtin(char **tokens, t_data *data);
char	**convert_vars_container_to_envp(t_data *data);
int		do_export_builtin(char **tokens, t_data *data);
int		unset_shell_var(t_data *data, const char *name);
int		set_shell_var(t_data *data, const char *name, const char *value);
// char *get_vars_value(char *name);

#endif
