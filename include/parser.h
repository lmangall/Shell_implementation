

#ifndef PARSER_H
#define PARSER_H

#include <parser_nodes.h>
#include <vars.h>

struct node_type_master *search_special(struct node_s *cmd);
void print_master(struct node_type_master *master_node);
int is_operator(char *str);


/**
 * @brief Looks for the first operator
 * in the array of tokens and returns the operator type.
 *

	* This function iterates over the array of tokens and determines the operator type
 * based on the token values. The following operators are supported:
 * - PIPE: "|"
 * - RDR_OUT_REPLACE: ">"
 * - RDR_OUT_APPEND: ">>"
 * - RDR_INPUT: "<"
 * - RDR_INPUT_UNTIL: "<<"
 *
 * @param token An array of tokens to search for operators.
 * @return The operator type, or NONE if no operator is found.
 */
t_operator	get_operator(char **token);
void i_and_o_redir(struct node_type_master *master_node);
struct node_s *parse_simple_command(char **tokens, t_data *data);
struct node_type_master *parse_advanced_command(char **tokens);



/**
 * @brief Parse and execute a given command line.
 *
 * This function parses the command line, determines the type of command,
 * and delegates the execution to the appropriate handler function.
 *
 * @param line The input command line to be parsed and executed.
 * @param data A pointer to the data structure containing relevant information.
 * @return 1 on successful execution.
 */
int parse_and_execute(char *line, t_data *data);

#endif