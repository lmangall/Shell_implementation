/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DEV.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:46:45 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/11 12:17:09 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/free.h"
#include "../include/lexer.h"
#include "../include/parser_nodes.h"
#include "../include/parser.h"
#include "../include/main.h"
#include "../include/vars.h"
#include "../lib/libft/src/libft.h"
#include <unistd.h>

void	print_string_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		printf("array[%d] = %s\n", i, array[i]);
		i++;
	}
}

void	print_the_first_child_of_root_nodes(struct node_type_master *master)
{
	struct node_s	*node;

	for (int i = 0; i < master->nbr_root_nodes; i++)
	{
		node = master->root_nodes[i]->first_child;
		while (node)
		{
			printf("node->str: %s\n", node->str);
			node = node->next_sibling;
		}
	}
}

// goes through the root nodes (node_command) and prints the first child of each
// the function should use the next_sibling pointer to go through the list of root nodes
void	print_root_nodes(struct node_type_master *master_node)
{
	struct node_s	*current;
	int				i;

	printf("\n\n\n\n");
	current = master_node->root_nodes[0];
	i = 0;
	while (current != NULL)
	{
		printf("root_nodes[%d] first_child->str = %s\n", i,
			current->first_child->str);
		current = current->next_sibling;
		i++;
	}
}
