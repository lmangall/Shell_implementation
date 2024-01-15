/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:22:39 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/15 09:57:28 by ohoro            ###   ########.fr       */
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
	char	*line;

	(void)argc;
	(void)argv;
	init_vars(&data, envp);
	set_signal_handlers();
// printf("? before loop %d\n", get_var(&data, "?"));
	while (1)
	{
// printf("? at start %d\n", get_var(&data, "?"));
		line = readline(SHELL_PROMPT);
		add_history(line);
		if (!line)
{
// printf("line is null\n");
			handle_ctrl_d(SIGQUIT);
			}
		if (line[0] != '\0')
		{
			signal(SIGQUIT, handle_ctrl_backslash);
			signal(SIGINT, handle_ctrl_c_in_command);
			prepare_command_execution(&line, &data);
			builtins_to_parsing(line, &data);
			free(line);
		}
		set_signal_handlers();
	}
	cleanup_and_exit(line, &data);
	return (0);
}

void	set_signal_handlers(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	prepare_command_execution(char **line, t_data *data)
{
	char	*expanded_line;

	if (ft_strchr(*line, '$') != NULL)
	{
		expanded_line = expand(*line, data);
		*line = ft_strdup(expanded_line);
		free(expanded_line);
	}
}

int	builtins_to_parsing(char *line, t_data *data)
{
	int	status;

	status = check_for_builtins(line, data);
	if (status == 1)
		status = parse_and_execute(line, data);
	if (status == 2)
		cleanup_and_exit(line, data);
	return (status);
}
