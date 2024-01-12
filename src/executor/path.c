/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 10:09:42 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/12 11:37:54 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/free.h"
#include "../../include/lexer.h"
#include "../../include/main.h"
#include "../../include/parser.h"
#include "../../include/parser_nodes.h"
#include "../../include/pipe.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <stddef.h>
#include <sys/wait.h>
#include <unistd.h>

char	*search_path(char *cmd, t_data *data)
{
	char	*paths;
	char	**paths_arr;
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	paths = return_env_from_container(data);
	paths_arr = ft_split(paths, ':');
	while (paths_arr[i] != NULL)
	{
		tmp = ft_strjoin(paths_arr[i], "/");
		command = ft_strjoin(tmp, cmd);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		command = NULL;
		i++;
	}
	free_string_array_index(paths_arr, i);
	if (paths_arr)
		free(paths_arr);
	paths_arr = NULL;
	printf("mini\033[31m(fucking)\033[0mshell: %s: command not found\n", cmd);
	return (NULL);
}

void	handle_absolute_path(char **argv, char **custom_env)
{
	if (access(argv[0], 0))
	{
		printf("No such file or directory\n");
		exit(127);
	}
	execve(argv[0], argv, custom_env);
}
