/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:44:06 by lmangall          #+#    #+#             */
/*   Updated: 2023/12/12 13:02:23 by lmangall         ###   ########.fr       */
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
		// free(tmp); => this free was causing a problem :
		// pointer being freed was not allocated
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths_arr++;
	}
	//probably need to free paths_arr
	printf("mini\033[31m(fucking)\033[0mshell: %s: command not found\n", cmd);
	// set errno, maybe errno = ENOENT;
	return (NULL);
}

int	exec_cmd(char **argv, t_data *data)
{
	char	*path;

	char **custom_env = convert_vars_container_to_envp(data);

	if (ft_strchr(argv[0], '/'))
		execve(argv[0], argv,custom_env );
	else
	{
		path = search_path(argv[0], data);
		if (!path)
		{
			return (0);
		}
		execve(path, argv,custom_env );
		free(path);
	}
	free_string_array(argv);
	free_string_array(custom_env);
	// =>custom_env needs to be freed
	
	return (0);
}

int	do_simple_command(struct node_s *root_node, t_data *data)
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
	free_node_tree(root_node);
	argv[argc] = NULL;
	exec_cmd(argv, data);
	free_argv(argc, argv);
	return (0);
}

