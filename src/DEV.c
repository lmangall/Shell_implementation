/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DEV.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:46:45 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/05 16:58:39 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/free.h"
#include "../include/lexer.h"
#include "../include/node.h"
#include "../include/parser.h"
#include "../include/shell.h"
#include "../include/vars.h"
#include "../lib/libft/src/libft.h"
#include <unistd.h>

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

void	print_master(struct node_type_master *master_node)
{
	if (master_node == NULL)
	{
		printf("\033[1;33m");
		printf("Master node is NULL\n");
		printf("\033[0m");
		return ;
	}

	printf("\033[1;33m");
	printf("Master Node Type: NODE_MASTER\n");
	printf("Number of Root Nodes: %d\n", master_node->nbr_root_nodes);
	printf("\033[0m");

	for (int i = 0; i < master_node->nbr_root_nodes; i++)
	{
		printf("\033[1;33m");
		printf("Node %d:\n", i);
		printf("\033[0m");
		if (master_node->root_nodes[i] == NULL)
		{
			printf("\033[1;33m");
			printf("  Root Node is NULL\n");
			printf("\033[0m");
		}
		else
		{
			printf("\033[1;33m"); // Set the color to yellow
			printf("  Root Node Type: %d\n", master_node->root_nodes[i]->type);
			printf("  Root Node String: %s\n", master_node->root_nodes[i]->str);
			printf("  Root Node Operator: %d\n",
				master_node->root_nodes[i]->operator);
			printf("  Root Node FC Type: %d\n",
				master_node->root_nodes[i]->first_child->type);
			printf("  root_nodes[%d] first_child->str = %s\n", i,
				master_node->root_nodes[i]->first_child->str);
			if (master_node->root_nodes[i]->first_child->next_sibling != NULL)
				printf("  root_nodes[%d] first_child->next_sibling->str = %s\n",
					i,
					master_node->root_nodes[i]->first_child->next_sibling->str);
			else
				printf("  the first child has no sibling (only 1 word,no flags)\n");

			printf("\033[0m");
			printf("\n\n");
		}
	}
	// print_root_nodes(master_node);
	printf("\n");
}