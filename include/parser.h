

#ifndef PARSER_H
#define PARSER_H

struct node_type_master *search_special(struct node_s *cmd);
void print_master(struct node_type_master *master_node);


//  ->  COMMENTED OUT FOR COMPLEX AST (pipe) TESTING
// struct node_s *parse_simple_command(char **tokens)
//  ->  ADDED FOR COMPLEX AST (pipe) TESTING
struct node_type_master *parse_simple_command(char **tokens);


/////////////////////


#endif