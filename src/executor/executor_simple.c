/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:09:33 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 18:21:35 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/lexer.h"
#include "../../include/main.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
#include "../../include/free.h"
#include "../../include/pipe.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <sys/wait.h>
#include <errno.h>
#include <stddef.h>
#include <unistd.h>

char	*duplicate_string(const char *str)
{
	char	*duplicate;

	duplicate = malloc(strlen(str) + 1);
	if (!duplicate)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strcpy(duplicate, str);
	return (duplicate);
}

char	**build_argv(struct node_s *root_node, int *argc)
{
	struct node_s	*child;
	int				max_args;
	char			**argv;

	child = root_node->first_child;
	max_args = 255;
	argv = malloc((max_args + 1) * sizeof(char *));
	if (!argv)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	*argc = 0;
	while (child && *argc < max_args)
	{
		argv[*argc] = duplicate_string(child->str);
		child = child->next_sibling;
		(*argc)++;
	}
	argv[*argc] = NULL;
	return (argv);
}

void	free_argv(char **argv)
{
	for (int i = 0; argv[i] != NULL; i++)
	{
		free(argv[i]);
	}
	free(argv);
}

int	do_simple_command(struct node_s *root_node, t_data *data)
{
	int		argc;
	char	**argv;

	argv = build_argv(root_node, &argc);
	if (!argv)
	{
		return (0);
	}
	free_node_tree(root_node);
	exec_cmd(argv, data);
	free_argv(argv);
	return (0);
}
