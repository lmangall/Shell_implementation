#ifndef EXPANDER_H
#define EXPANDER_H

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../include/shell.h"
#include "../include/lexer.h"
#include "../include/vars.h"
#include "../include/parser.h"
#include "../include/executor.h"
#include "../include/expander.h"
#include "../lib/libft/src/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

// /**
//  * @brief Replaces the variable in the given node's string with its value.
//  * 
//  * @param node The node to replace the variable in.
//  * @return int Returns 0 on success.
//  */
// static int replace_var(struct node_s *node);

// /**
//  * @brief Checks if the given node's string contains a dollar sign.
//  * 
//  * @param node The node to check.
//  * @return struct node_s* Returns the node if it contains a dollar sign, otherwise returns NULL.
//  */
// struct node_s *contains_dollar(struct node_s *node);


/*
** Expands variables in the given command node's string.
** @param node The command node to expand variables in.
** @param data The data structure containing the variables to expand.
*/
void	expand(struct node_s **node, t_data *data);

/*
** Identifies the variable name in the given string.
** @param str The string to search for the variable name.
** @param data The data structure containing the variables to search for.
** @return The variable name if found, otherwise NULL.
*/
char	*identify_var(char *str, t_data *data);

/*
** Search if the first encountered $VAR exists
** If so it returns its name
** @param str The string to expand the variable in.
** @param data The data structure containing the variables to expand.
** @return The name of the VAR found.
*/
void	expand_var(char **str, t_vars **var);

/*
** Finds the value of the given variable name in the given data structure.
** @param name The name of the variable to find the value of.
** @param data The data structure containing the variables to search for.
** @return The value of the variable if found, otherwise NULL.
*/
char	*find_val(char *name, t_data *data);

/*
** Finds the variable with the given name in the given data structure.
** @param name The name of the variable to find.
** @param data The data structure containing the variables to search for.
** @return The variable if found, otherwise NULL.
*/
t_vars	*find_var(char *name, t_data *data);




#endif 
