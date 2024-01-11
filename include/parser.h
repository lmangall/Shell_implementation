/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:17:45 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/11 13:50:26 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <vars.h>
# include "parser_nodes.h"

int						is_operator(char *str);

/**
 * @brief Looks for the first operator
 * in the array of tokens and returns the operator type.
 *

 * This function iterates over the array of 
 * tokens and determines the operator type
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
t_operator				get_operator(char **token);
/**
 * @brief Parses a simple command.
 *
 * This function takes an array of tokens and a data structure as input,
 * and it generates a one level linked list representing the parsed command.
 * The `expand` function is called to handle variable expansion.
 *
 *There is one empty root node of type "ROOT"
 *There is one one node per word of type "WORD"
 *
 * @param tokens An array of tokens representing the command.
 * @param data A data structure containing information about variables.
 * @return A pointer to the root node of the generated one level linked list
 */
struct node_s			*parse_simple_command(char **tokens, t_data *data);
struct node_s			*parse_advanced_command(char **tokens);

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
int						parse_and_execute(char *line, t_data *data);

struct node_s			*create_new_command(char **tokens,
							int i, struct node_s **head,
							struct node_s **current_cmd);
struct node_s			*handle_regular_word(char **tokens,
							int i,
							struct node_s *current_cmd);
struct node_type_master	*create_master_and_link(struct node_s *head);

#endif