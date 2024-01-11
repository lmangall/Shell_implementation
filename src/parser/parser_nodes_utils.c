/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:52:55 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/11 16:06:47 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/free.h"
#include "../include/parser_nodes.h"
#include "../include/main.h"
#include "../lib/libft/src/libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct s_node	*new_node(enum e_node type)
{
	struct s_node	*node;

	node = malloc(sizeof(struct s_node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(struct s_node));
	node->type = type;
	node->str = NULL;
	node->first_child = NULL;
	node->prev_sibling = NULL;
	node->next_sibling = NULL;
	node->operator = NONE;
	return (node);
}

int	add_child_node(struct s_node *parent, struct s_node *child)
{
	struct s_node	*current_child;

	if (parent == NULL || child == NULL)
		return (0);
	if (parent->first_child == NULL)
	{
		parent->first_child = child;
		return (1);
	}
	else
	{
		current_child = parent->first_child;
		while (current_child->next_sibling != NULL)
			current_child = current_child->next_sibling;
		current_child->next_sibling = child;
		return (1);
	}
}

// void	set_s_nodetr(struct s_node *node, char *val)
// {
// 	char	*val2;

// 	if (!val)
// 		node->str = NULL;
// 	else
// 	{
// 		val2 = ft_calloc(strlen(val) + 1, sizeof(char));
// 		if (!val2)
// 			node->str = NULL;
// 		else
// 		{
// 			if (node->str)
// 				free(node->str);
// 			ft_strlcpy(val2, val, ft_strlen(val) + 1);
// 			node->str = val2;
// 		}
// 	}
// }

int	add_sibling_node(struct s_node *parent, struct s_node *child)
{
	if (parent == NULL || child == NULL)
		return (0);
	if (parent->next_sibling == NULL)
	{
		parent->next_sibling = child;
		return (1);
	}
	return (0);
}
