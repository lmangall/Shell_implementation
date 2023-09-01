

#ifndef PARSER_H
#define PARSER_H

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
    int num_exported_vars;
    t_vars vars_container[MAX_VARS];
    t_vars exported_vars_container[MAX_VARS];
} t_data;



int find_equal_sign(char *str);
void init_vars(t_data *data);
void print_vars(const t_data *data);

int set_var(t_data *data, const char *name, const char *value);
int unset_var(t_data *data, const char *name);

int export_var(t_data *data, const char *name);
void print_exported_vars(const t_data *data);



int search_special(struct node_s *cmd);


/////////////////////


#endif