/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:44:06 by lmangall          #+#    #+#             */
/*   Updated: 2023/10/09 14:45:11 by lmangall         ###   ########.fr       */
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

// extern long long g_exit_status;       //   => get rid of this global var

char	*search_path(char *cmd)
{
	char	*paths;
	char	**paths_arr;
	char	*tmp;
	char	*command;

	paths = getenv("PATH");
	paths_arr = ft_split(paths, ':');
	while (*paths_arr)
	{
		tmp = ft_strjoin(*paths_arr, "/");
		command = ft_strjoin(tmp, cmd);
		// free(tmp); => this free was causing a problem :
		// pointer being freed was not allocated
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths_arr++;
	}
	printf("mini\033[31m(fucking)\033[0mshell: %s: command not found\n", cmd);
	// errno = ENOENT;
	return (NULL);
}

int	do_exec_cmd(char **argv)
{
	char	*path;

	if (ft_strchr(argv[0], '/'))
		execv(argv[0], argv);
	else
	{
		path = search_path(argv[0]);
		if (!path)
		{
			return (0);
		}
		execv(path, argv);
		free(path);
	}
	return (0);
}

int	do_simple_command(struct node_s *root_node)
{
	struct node_s	*child;
	int				argc;
	long			max_args;
	char			*str;

	child = root_node->first_child;
	if (!child)
		return (0);
	argc = 0;
	max_args = 255;
	char *argv[max_args + 1]; /* keep 1 for the terminating NULL arg */
	if (child)
		while (child && argc < max_args)
		{
			str = child->str;
			argv[argc] = malloc(strlen(str) + 1);
			if (!argv[argc])
			{
				free_argv(argc, argv);
				return (0);
			}
			ft_strlcpy(argv[argc], str, strlen(str) + 1);
			// maybe there should be a guard if next_sibling is inexistant
			child = child->next_sibling;
			argc++;
		}
	argv[argc] = NULL;
	do_exec_cmd(argv);
	free_argv(argc, argv);
	return (0);
}
