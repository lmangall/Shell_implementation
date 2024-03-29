/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:44:06 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 16:45:23 by ohoro            ###   ########.fr       */
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
		{
			printf("%s: invalid command\n", argv[0]);
			free_string_array(data->argv);
			free_string_array(data->envp_arr);
			exit(127);
			return (1);
		}
		data->path = path;
		execve(path, argv, custom_env);
	}
	return (0);
}

void	update_status(int status, t_data *data)
{
	char	*status_str;

	status_str = NULL;
	if (WIFEXITED(status))
	{
		status_str = ft_itoa(WEXITSTATUS(status));
		set_var(data, "?", status_str);
	}
	else if (WIFSIGNALED(status))
	{
		status_str = ft_itoa(WTERMSIG(status) + 128);
		set_var(data, "?", status_str);
	}
	free(status_str);
}

void	simple_or_advanced(char **tokens, t_data *data)
{
	int				status;
	struct s_node	*cmd;

	status = 0;
	if (get_operator(tokens) != NONE)
	{
		cmd = parse_advanced_command(tokens);
		data->ast = cmd;
		if (fork() == 0)
			exec_pipe_redir(cmd, data);
		waitpid(-1, &status, 0);
		update_status(status, data);
		free_node_tree_recursive(data->ast);
	}
	else
	{
		cmd = NULL;
		cmd = parse_simple_command(tokens, data);
		data->ast = cmd;
		if (fork() == 0)
			exec_pipe_redir(cmd, data);
		waitpid(-1, &status, 0);
		update_status(status, data);
		free_node_tree_recursive(data->ast);
	}
}
