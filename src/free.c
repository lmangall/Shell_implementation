/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:47:47 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 15:39:01 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/executor.h"
#include "../include/free.h"
#include "../include/main.h"
#include "../include/parser_nodes.h"
#include "../include/vars.h"
#include "../lib/libft/src/libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int	get_var(t_data *data, char *name)
{
	int	i;

	i = 0;
	while (i != 255)
	{
		if (strcmp(data->vc[i].name, name) == 0)
		{
			return (ft_atoi(data->vc[i].value));
		}
		i++;
	}
	return (0);
}

void	cleanup_and_exit(char *line, t_data *data)
{
	int	ex;

	rl_clear_history();
	if (line)
		free(line);
	ex = get_var(data, "?");
	exit(ex);
}

void	free_node_tree_recursive(struct s_node *node)
{
	if (!node)
		return ;
	free_node_tree_recursive(node->next_sibling);
	free_node_tree(node, NULL);
}

void	free_node_tree(struct s_node *node, struct s_node *parent)
{
	struct s_node	*child;
	struct s_node	*next;

	if (!node)
		return ;
	child = node->first_child;
	while (child)
	{
		next = child->next_sibling;
		free_node_tree(child, node);
		child = next;
	}
	if (node->str)
		free(node->str);
	if (parent && parent->first_child == node)
		parent->first_child = node->next_sibling;
	free(node);
}

void	free_string_array(char **tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return ;
	while (tokens[i] != NULL)
	{
		if (tokens[i])
		{
			free(tokens[i]);
			tokens[i] = NULL;
		}
		i++;
	}
	free(tokens);
	tokens = NULL;
}
