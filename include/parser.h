

#ifndef PARSER_H
#define PARSER_H

struct node_type_master *search_special(struct node_s *cmd);
void print_master(struct node_type_master *master_node);


//  ->  COMMENTED OUT FOR COMPLEX AST (pipe) TESTING
// struct node_s *parse_simple_command(char **tokens)
//  ->  ADDED FOR COMPLEX AST (pipe) TESTING
// struct node_type_master *parse_simple_command(char **tokens);

/////////////////////

void set_pipe_operator(struct node_type_master *master);
void set_redir_operator(struct node_type_master *master);


struct node_s *parse_simple_command(char **tokens);
struct node_type_master *parse_advanced_command(char **tokens);

struct node_s *create_pipe_command_node(void);
struct node_s *create_new_command_node(char *token);
int add_command_node_to_list(struct node_s **cmd, struct node_s **current_cmd, struct node_s *new_cmd);
struct node_type_master *create_master_node(struct node_s *cmd);

void    link_root_nodes(struct node_type_master *master_node);


#endif