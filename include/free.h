/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:16:27 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/12 09:04:45 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "parser_nodes.h"
# include "../include/main.h"

/**
 * @brief Recursively frees a tree of nodes.
 *
 * This function frees a tree of nodes, starting 
 * from the given node and recursively
 * freeing all child nodes. The memory allocated 
 * for each node is also freed.
 *
 * @param node The root node of the tree to free.
 */
void	free_node_tree(struct s_node *node);

/**
 * @brief Frees an array of string tokens.
 *
 * This function frees an array of string tokens, 
 * where each token is a null-terminated string.
 * The memory allocated for each string is also freed.
 *
 * @param tokens The array of tokens to free.
 */
void	free_string_array(char **tokens);

void	free_node_tree_recursive(struct s_node *node);

#endif