
#ifndef FREE_H
#define FREE_H


#include "parser_nodes.h"
#include "../include/main.h"

/**
 * @brief Recursively frees a tree of nodes.
 *
 * This function frees a tree of nodes, starting from the given node and recursively
 * freeing all child nodes. The memory allocated for each node is also freed.
 *
 * @param node The root node of the tree to free.
 */
void free_node_tree(struct node_s *node);

/**
 * @brief Frees an abstract syntax tree.
 *
 * This function frees an abstract syntax tree, starting from the root nodes and recursively
 * freeing all child nodes. The memory allocated for each node is also freed.
 *
 * @param master_node The master node of the abstract syntax tree to free.
 */
void free_ast(struct node_type_master *master_node);

/**
 * @brief Frees an array of string tokens.
 *
 * This function frees an array of string tokens, where each token is a null-terminated string.
 * The memory allocated for each string is also freed.
 *
 * @param tokens The array of tokens to free.
 */
void free_string_array(char **tokens);

#endif