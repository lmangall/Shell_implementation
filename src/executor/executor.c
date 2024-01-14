/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:44:06 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/14 22:00:39 by lmangall         ###   ########.fr       */
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
set_var(data, "?", "0");
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
		set_var(data, "?", "0");
		execve(path, argv, custom_env);
	}
	return (0);
}

void	update_status_and_cleanup(int status, t_data *data)
{

	if (WIFEXITED(status))
		set_var(data, "?", ft_itoa(WEXITSTATUS(status)));
	else if (WIFSIGNALED(status))
		set_var(data, "?", ft_itoa(WTERMSIG(status) + 128));
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
// printf(" before exec_pipe_redir with status %d\n", get_var(data, "?"));
			exec_pipe_redir(cmd, data);
// printf(" after exec_pipe_redir with status %d\n", get_var(data, "?"));
		}
		waitpid(-1, &status, 0);
// printf(" after waitpid with status %d\n", get_var(data, "?"));
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

		// if(WIFEXITED(status))
		// {	
		// 	printf("   after waitpid with status %d\n", WEXITSTATUS(status));
		// 	set_var(data, "?", ft_itoa(WEXITSTATUS(status)));
		// }
		// else if (WIFSIGNALED(status))
		// 	printf(" after waitpid with status %d\n", WTERMSIG(status) + 128);
	update_status_and_cleanup(status, data);
	}

	// printf("   after waitpid with env %d\n", get_var(data, "?"));
	free_string_array(data->tokens);

}
