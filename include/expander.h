#ifndef EXPANDER_H
#define EXPANDER_H


#include "shell.h"
#include "expander.h"
#include "parser.h"


// //UPDATE DOXY COMMENT
// /**
//  * @brief Replaces the variable in the given node's string with its value.
//  * 
//  * @param node The node to replace the variable in.
//  * @return int Returns 0 on success.
//  */
// int replace_var(struct node_s *node, char *new_value);

/**
 * @brief Checks if the given node's string contains a dollar sign.
 * 
 * @param node The node to check.
 * @return struct node_s* Returns the node if it contains a dollar sign, otherwise returns NULL.
 */
struct node_s *contains_dollar(struct node_s *node);

/**
 * @brief Expands variables in a command node.
 *
 * This function replaces any variable references in the command node with their
 * corresponding values from the variables container in the t_data structure.
 *
 * @param node The command node to expand.
 * @param data Pointer to the t_data structure containing the variables container.
 */
void expansion(struct node_s *node, t_data *data);



int 	parse_and_execute(char *line, t_data *data);



#endif 
