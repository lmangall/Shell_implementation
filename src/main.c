/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:22:39 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/05 20:59:02 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/executor.h"
#include "../include/expander.h"
#include "../include/free.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include "../include/pipe.h"
#include "../include/redirect.h"
#include "../include/shell.h"
#include "../include/signals.h"
#include "../include/vars.h"
#include "../lib/libft/src/libft.h"
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		status;
	t_data	data;
	char	*tmp;

	(void)argc;
	(void)argv;
	data.paths = NULL;
	data.envp = NULL;
	init_vars(&data, envp);
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	status = 1;
	while (status)
	{
		line = readline(SHELL_PROMPT);
		// what is returned is malloced and should be freed
		if (line == NULL)
			handle_ctrl_d(SIGQUIT);
		if (line[0] != '\0')
		{
			signal(SIGQUIT, handle_ctrl_backslash);
			signal(SIGINT, handle_ctrl_c_in_command);
			add_history(line);
			if (ft_strchr(line, '$') != NULL)
			{
				tmp = NULL;
				tmp = expand(line, &data);
				line = ft_strdup(tmp);
				free(tmp);
			}
			status = check_and_builtins(line, &data);
			if (status == 1)
				status = parse_and_execute(line, &data);
			if (status == 2)
			{
				free(line);
				rl_clear_history();
				return (EXIT_SUCCESS);
			}
		}
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, handle_ctrl_c);
		// this free might be causing a double free
		// free(line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}

int	parse_and_execute(char *line, t_data *data)
{
	char **tokens;
	int status;
	struct node_type_master *master_node;
	struct node_s *cmd;

	tokens = lexer(line);
	free(line);
	status = 0;

	if (get_operator(tokens) != NONE)
	{
		master_node = parse_advanced_command(tokens);
		print_master(master_node);

		if (fork() == 0)
		{
			exec_pipe_redir(master_node->root_nodes[0], data);
		}

		waitpid(-1, &status, 0);

		if (WIFEXITED(status))
		{
			data->last_command_exit_status = WEXITSTATUS(status);
			set_var(data, "?", ft_itoa(data->last_command_exit_status));
		}
		else if (WIFSIGNALED(status))
		{
			data->last_command_exit_status = 128 + WTERMSIG(status);
			// Signalnummer + 128
			set_var(data, "?", ft_itoa(data->last_command_exit_status));
		}

		free_ast(master_node);
	}
	else
	{
		cmd = parse_simple_command(tokens, data);

		if (fork() == 0)
		{
			exec_pipe_redir(cmd, data);
		}

		waitpid(-1, &status, 0);

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

		// free_node(cmd);
	}

	free_string_array(tokens);
	return (1);
}