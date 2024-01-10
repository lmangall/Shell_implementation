/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:09:33 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/11 00:09:29 by lmangall         ###   ########.fr       */
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
#include "../../include/DEV.h"
#include <sys/wait.h>
#include <errno.h>
#include <stddef.h>
#include <unistd.h>

char	*duplicate_string(const char *str)
{
	char	*duplicate;
	size_t	len;

	len = ft_strlen(str);
	duplicate = malloc(len + 1);
	if (!duplicate)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	ft_strlcpy(duplicate, str, len + 1);
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

int	do_simple_command(struct node_s *root_node, t_data *data)
{
	int		argc;
	char	**argv;

	argv = build_argv(root_node, &argc);
	if (!argv)
		return (0);
	free_node_tree(root_node);
	exec_cmd(argv, data);
printf("\033[0;31m" "do_simple_command : after exec_cmd (which calls execve)\n" "\033[0m");
	free_string_array(argv);
	cleanup_and_exit(NULL);
	return (0);
}
