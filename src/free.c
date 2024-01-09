/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:47:47 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/09 10:24:34 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/executor.h"
#include "../include/free.h"
#include "../include/parser_nodes.h"
#include "../include/main.h"
#include "../lib/libft/src/libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

//we can use a preprocessor # define to define the error messages
// code and message can just be copied from errno.h for accuracy

// # define ENOMEM "Cannot allocate memory\n"
// # define ENODATA "No message available on STREAM\n"

// # define ENODATA "No message available on STREAM\n"
// # define ENODATA "No message available on STREAM\n"

void	cleanup_and_exit(char *line)
{
	rl_clear_history();
	if (line)
		free(line);
	exit(EXIT_SUCCESS);
}

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
	if(node->str)
	{
		free(node->str);
	}
	if(node)
	{
		free(node);
	}
}

void	free_ast(struct node_type_master *master_node)
{
	int	i;

	i = 0;
	while (i < master_node->nbr_root_nodes)
	{
		free_node_tree(master_node->root_nodes[i]);
		i++;
	}
if(master_node->root_nodes)
{
	free(master_node->root_nodes);
}
if(master_node)
{
	free(master_node);
}
}

void	free_string_array(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}
