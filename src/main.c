/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:22:39 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 14:53:53 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/executor.h"
#include "../include/expander.h"
#include "../include/free.h"
#include "../include/lexer.h"
#include "../include/main.h"
#include "../include/parser.h"
#include "../include/pipe.h"
#include "../include/redirect.h"
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
	t_data	data;
	int		execution_status;
	char	*line;

	execution_status = 1;
	(void)argc;
	(void)argv;
	init_vars(&data, envp);
	set_signal_handlers();
	while (1)
	{
		line = readline(SHELL_PROMPT);
		if (!line)
			handle_ctrl_d(SIGQUIT);
		if (line[0] != '\0')
		{
			prepare_command_execution(&line, &data);
			execution_status = builtins_to_parsing(line, &data);
			if (execution_status == 2)
			{
				cleanup_and_exit(line);
			}
			free(line);
		}
	}
	cleanup_and_exit(NULL);
}

void	set_signal_handlers(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	prepare_command_execution(char **line, t_data *data)
{
	char	*expanded_line;

	signal(SIGQUIT, handle_ctrl_backslash);
	signal(SIGINT, handle_ctrl_c_in_command);
	add_history(*line);
	if (ft_strchr(*line, '$') != NULL)
	{
		expanded_line = expand(*line, data);
		// free(*line);          ==>> causes a double free when expansion is triggered
		*line = ft_strdup(expanded_line);
		free(expanded_line);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_ctrl_c);
}

int	builtins_to_parsing(char *line, t_data *data)
{
	int	status;

	status = check_for_builtins(line, data);
	if (status == 1)
		status = parse_and_execute(line, data);
	return (status);
}

void	cleanup_and_exit(char *line)
{
	if (line)
		free(line);
	// Clear Readline history
	clear_history();
	exit(EXIT_SUCCESS);
}
