

#ifndef VARS_H
#define VARS_H

#define MAX_VARS 100  // Max number of variables

struct Vars {
    char name[50];
    char value[100];
};

struct Vars vars_container[MAX_VARS];

void init_vars(void);
void print_vars(void);
int find_equal_sign(char *str);
int set_vars(char *name, char *value);
int unset_vars(char *name);
char *get_vars_value(char *name);

#endif
