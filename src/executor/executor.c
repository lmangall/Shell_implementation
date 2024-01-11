/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:44:06 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/11 21:47:22 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/DEV.h"
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
		{
			return (command);
		}
		paths_arr++;
	}
	free(command);
	printf("mini\033[31m(fucking)\033[0mshell: %s: command not found\n", cmd);
	exit(1);
	return (NULL);
}

int	exec_cmd(char **argv, t_data *data)
{
	char	*path;
	char	**custom_env;

	custom_env = convert_vc_to_envp(data);
	data->envp_arr = custom_env;
	if (ft_strchr(argv[0], '/'))
	{
		if (access(argv[0], 0))
		{
			printf("No such file or directory\n");
			exit(127);
		}
		execve(argv[0], argv, custom_env);
	}
	else
	{
		path = search_path(argv[0], data);
		data->path = path;
		if (!path)
		{
			free(path);
			free_string_array(custom_env);
			return (0);
		}
		execve(path, argv, custom_env);
	}
	return (0);
}

void	update_status_and_cleanup(int status, t_data *data)
{
	char	*status_char;

	if (WIFEXITED(status))
	{
		status_char = ft_itoa(WEXITSTATUS(status));
		data->last_command_exit_status = status_char;
		set_var(data, "?", data->last_command_exit_status);
		free(status_char);
	}
	else if (WIFSIGNALED(status))
	{
		status_char = ft_itoa(WTERMSIG(status) + 128);
		data->last_command_exit_status =  status_char;
		set_var(data, "?", data->last_command_exit_status);
		free(status_char);
	}
}

// shoud the call to update_status_and_cleanup be in parse_and_execute
void	simple_or_advanced(char **tokens, t_data *data)
{
	int				status;
	struct s_node	*cmd;

	status = 0;
	if (get_operator(tokens) != NONE)
	{
			cmd = parse_advanced_command(tokens);
		if (fork() == 0)
		{
			exec_pipe_redir(cmd, data);
		}
		waitpid(-1, &status, 0);
		free_string_array(data->tokens);
		free_node_tree_recursive(cmd);
		update_status_and_cleanup(status, data);
	}
	else
	{
		if (fork() == 0)
		{
			cmd = parse_simple_command(tokens, data);
			exec_pipe_redir(cmd, data);
		}
		waitpid(-1, &status, 0);
		free_string_array(data->tokens);
		update_status_and_cleanup(status, data);
	}
}
