
#ifndef FREE_H
#define FREE_H


#include "node.h"
#include "../include/shell.h"

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
 * @brief Frees an array of string arguments.
 *
 * This function frees an array of string arguments, where each argument is a null-terminated
 * string. The memory allocated for each string is also freed.
 *
 * @param argc The number of arguments in the array.
 * @param argv The array of arguments to free.
 */
void free_argv(int argc, char **argv);

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
void free_token_array(char **tokens);

#endif