/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:44:06 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/12 11:36:53 by lmangall         ###   ########.fr       */
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

int	exec_cmd(char **argv, t_data *data)
{
	char	*path;
	char	**custom_env;

	custom_env = convert_vc_to_envp(data);
	data->envp_arr = custom_env;
	if (ft_strchr(argv[0], '/'))
	{
		handle_absolute_path(argv, custom_env);
	}
	else
	{
		path = search_path(argv[0], data);
		if (!path)
			return (0);
		data->path = path;
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
		data->last_command_exit_status = status_char;
		set_var(data, "?", data->last_command_exit_status);
		free(status_char);
	}
}

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
		free_node_tree_recursive(cmd);
	}
	else
	{
		if (fork() == 0)
		{
			cmd = parse_simple_command(tokens, data);
			exec_pipe_redir(cmd, data);
		}
		waitpid(-1, &status, 0);
	}
	free_string_array(data->tokens);
	update_status_and_cleanup(status, data);
}
