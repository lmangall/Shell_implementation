#ifndef EXPANDER_H
#define EXPANDER_H


#include "shell.h"
#include "expander.h"
#include "parser.h"



/**
 * @brief Replaces the variable in the given node's string with its value.
 * 
 * @param node The node to replace the variable in.
 * @return int Returns 0 on success.
 */
static int replace_var(struct node_s *node);

/**
 * @brief Checks if the given node's string contains a dollar sign.
 * 
 * @param node The node to check.
 * @return struct node_s* Returns the node if it contains a dollar sign, otherwise returns NULL.
 */
struct node_s *contains_dollar(struct node_s *node);

/**
 * @brief Expands variables in the given node's string using the given variables container.
 * 
 * @param node The node to expand variables in.
 * @param vars_container The container of variables to use for expansion.
 */
void expansion(struct node_s *node, t_data *data);



int 	parse_and_execute(char *line, t_data *data);
int		check_dollar(char *str);



#endif 
