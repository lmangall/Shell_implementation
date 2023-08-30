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

// /**
//  * @brief Expands variables in the given node's string using the given variables container.
//  * 
//  * @param node The node to expand variables in.
//  * @param vars_container The container of variables to use for expansion.
//  */
// void expansion(struct node_s *node, struct Vars *vars_container);

int expansion_substitution(struct node_s *node, t_data *data);
int expansion_set_var(struct node_s *node, t_data *data);

#endif 
