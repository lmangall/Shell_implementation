#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "../include/node.h"
#include "../include/shell.h"
#include "../include/vars.h"
#include "../include/minishell.h"
#include "../lib/libft/src/libft.h"
#include "../include/vars.h"


// get_vars_value takes a name and returns the value of the variable with that name
// it returns NULL if it failed
// char *get_vars_value(char *name)
// {
// 	int i;

// 	i = 0;
// 	while (vars_container[i].name[0] != '\0')
// 	{
// 		if (strcmp(vars_container[i].name, name) == 0)
// 			return (vars_container[i].value);
// 		i++;
// 	}
// 	return (NULL);
// }
