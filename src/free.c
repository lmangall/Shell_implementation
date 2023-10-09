/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:47:47 by lmangall          #+#    #+#             */
/*   Updated: 2023/10/09 14:54:39 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/executor.h"
#include "../include/free.h"
#include "../include/node.h"
#include "../include/shell.h"
#include "../lib/libft/src/libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

// void free_command_str(struct node_s *node)
// {
//     if (node == NULL)
//     {
//         return ;
//     }

//     if (node->type == NODE_COMMAND)
//     {
//         free(node->str);
//     }

//     struct node_s *child = node->first_child;
//     while (child != NULL)
//     {
//         free_command_str(child);
//         child = child->next_sibling;
//     }
// }

// void free_master_command_str(struct node_type_master *master_node)
// {
//     if (master_node == NULL)
//     {
//         return ;
//     }

//     for (int i = 0; i < master_node->nbr_root_nodes; i++)
//     {
//         free_command_str(master_node->root_nodes[i]);
//     }
// }

// static void free_node(struct node_s *node)
// {
//     if (!node)
//         return ;

//     free_node(node->first_child);
//     free_node(node->next_sibling);
//     free(node->str);
//     free(node);
// }

// static void free_master(struct node_type_master *master)
// {
//     if (!master)
//         return ;

//     for (int i = 0; i < master->nbr_root_nodes; i++)
//         free_node(master->root_nodes[i]);

//     free(master->root_nodes);
//     free(master->str);
//     free(master);
// }

void	free_node_tree(struct node_s *node)
{
	struct node_s	*child;
	struct node_s	*next;

	if (!node)
	{
		return ;
	}
	child = node->first_child;
	while (child)
	{
		next = child->next_sibling;
		free_node_tree(child);
		child = next;
	}
	free(node);
}

void	free_argv(int argc, char **argv)
{
	if (!argc)
		return ;
	while (argc--)
		free(argv[argc]);
}
