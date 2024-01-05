/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:44:06 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/05 20:23:29 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/executor.h"
#include "../include/free.h"
#include "../include/node.h"
#include "../include/pipe.h"
#include "../include/shell.h"
#include "../lib/libft/src/libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

// probably need to free paths_arr
char	*search_path(char *cmd, t_data *data)
{
	char	*paths;
	char	**paths_arr;
	char	*tmp;
	char	*command;

	paths = return_env_from_container(data);
	paths_arr = ft_split(paths, ':');
	while (*paths_arr)
	{
		tmp = ft_strjoin(*paths_arr, "/");
		command = ft_strjoin(tmp, cmd);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths_arr++;
	}
	printf("mini\033[31m(fucking)\033[0mshell: %s: command not found\n", cmd);
	return (NULL);
}

// =>custom_env needs to be freed ?
int	exec_cmd(char **argv, t_data *data)
{
	char	*path;
	char	**custom_env;

	custom_env = convert_vars_container_to_envp(data);
	if (ft_strchr(argv[0], '/'))
		execve(argv[0], argv, custom_env);
	else
	{
		path = search_path(argv[0], data);
		if (!path)
		{
			return (0);
		}
		execve(path, argv, custom_env);
		free(path);
	}
	free_string_array(argv);
	free_string_array(custom_env);
	return (0);
}

int	do_simple_command(struct node_s *root_node, t_data *data)
{
	struct node_s	*child;
	int				argc;
	long			max_args;
	char			*str;
	char			*argv[255 + 1];

	child = root_node->first_child;
	argc = 0;
	max_args = 255;
	if (!child)
		return (0);
	if (child)
		while (child && argc < max_args)
		{
			str = child->str;
			argv[argc] = malloc(strlen(str) + 1);
			if (!argv[argc])
			{
				free_string_array(argv);
				return (0);
			}
			ft_strlcpy(argv[argc], str, ft_strlen(str) + 1);
			child = child->next_sibling;
			argc++;
		}
	free_node_tree(root_node);
	argv[argc] = NULL;
	exec_cmd(argv, data);
	return (0);
}
