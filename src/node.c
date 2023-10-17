/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:52:55 by lmangall          #+#    #+#             */
/*   Updated: 2023/10/17 21:07:33 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/free.h"
#include "../include/node.h"
#include "../include/shell.h"
#include "../lib/libft/src/libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node_s	*new_node(enum node_type_e type)
{
	struct node_s	*node;

	node = malloc(sizeof(struct node_s));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(struct node_s));
	node->type = type;
	node->str = NULL;
	node->first_child = NULL;
	node->prev_sibling = NULL;
	node->next_sibling = NULL;
	node->operator= NONE;
	return (node);
}

int	add_child_node(struct node_s *parent, struct node_s *child)
{
	struct node_s	*current_child;

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

void	set_node_str(struct node_s *node, char *val)
{
	char	*val2;

	if (!val)
		node->str = NULL;
	else
	{
		val2 = ft_calloc(strlen(val) + 1, sizeof(char));
		if (!val2)
			node->str = NULL;
		else
		{
			if (node->str)
				free(node->str);
			ft_strlcpy(val2, val, ft_strlen(val) + 1);
			node->str = val2;
		}
	}
}

int	add_sibling_node(struct node_s *parent, struct node_s *child)
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