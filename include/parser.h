

#ifndef PARSER_H
#define PARSER_H

#include <node.h>
#include <vars.h>

struct node_type_master *search_special(struct node_s *cmd);
void print_master(struct node_type_master *master_node);
int is_operator(char *str);
t_operator	get_operator(char **token);
void i_and_o_redir(struct node_type_master *master_node);
struct node_s *parse_simple_command(char **tokens, t_data *data);
struct node_type_master *parse_advanced_command(char **tokens);
struct node_s *create_pipe_command_node(void);
struct node_s *create_root_node(char *token);
int add_command_node_to_list(struct node_s **cmd, struct node_s **current_cmd, struct node_s *new_cmd);
struct node_type_master *create_master_node(struct node_s *cmd);
void    link_root_nodes(struct node_type_master *master_node);
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