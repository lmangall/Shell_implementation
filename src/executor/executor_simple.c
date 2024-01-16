/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_simple.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:09:33 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/16 13:46:22 by lmangall         ###   ########.fr       */
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

char	**build_argv(struct s_node *root_node, int *argc)
{
	struct s_node	*child;
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

int	do_simple_command(struct s_node *root_node, t_data *data)
{
	int		argc;
	char	**argv;

	argv = build_argv(root_node, &argc);
	if (!argv)
		return (0);
	else
		data->argv = argv;
	// free_node_tree_recursive(root_node);
	free_node_tree(root_node, NULL);
	exec_cmd(argv, data);

	// free_string_array(data->argv);
	// free_string_array(data->envp_arr);
	// free_string_array(data->tokens);
	

	// free_string_array(argv);
	// free_string_array(data->envp_arr);
	// cleanup_and_exit(NULL, data);
	return (1);
}
