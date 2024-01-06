/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:44:06 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 15:03:32 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/executor.h"
#include "../include/free.h"
#include "../include/parser_nodes.h"
#include "../include/pipe.h"
#include "../include/main.h"
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

void	update_status_and_cleanup(int status, t_data *data)
{
	if (WIFEXITED(status)) 
	{
		data->last_command_exit_status = WEXITSTATUS(status);
		set_var(data, "?", ft_itoa(data->last_command_exit_status));
	}
	else if (WIFSIGNALED(status)) 
	{
		data->last_command_exit_status = 128 + WTERMSIG(status);
		set_var(data, "?", ft_itoa(data->last_command_exit_status));
	}
}

//shoud the call to update_status_and_cleanup be in parse_and_execute
void	simple_or_advanced(char **tokens, t_data *data)
{
	int						status;
	struct node_s			*cmd;
	struct node_type_master	*master_node;

	status = 0;
	if (get_operator(tokens) != NONE)
	{
		master_node = parse_advanced_command(tokens);
		if (fork() == 0)
			exec_pipe_redir(master_node->root_nodes[0], data);
		waitpid(-1, &status, 0);
		update_status_and_cleanup(status, data);
		free_ast(master_node);
	}
	else 
	{
		cmd = parse_simple_command(tokens, data);
		if (fork() == 0)
			exec_pipe_redir(cmd, data);
		waitpid(-1, &status, 0);
		update_status_and_cleanup(status, data);
		// free_node(cmd);
	}
}
