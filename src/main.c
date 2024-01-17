/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:22:39 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 15:39:41 by ohoro            ###   ########.fr       */
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

void	remove_leading_tabs(char *str)
{
	int	i;
	int	j;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] == '\t')
		i++;
	j = 0;
	while (str[i] != '\0')
	{
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;

	(void)argc;
	(void)argv;
	init_vars(&data, envp);
	set_signal_handlers();
	while (1)
	{
		line = readline(SHELL_PROMPT);
		add_history(line);
		remove_leading_tabs(line);
		if (!line)
			handle_ctrl_d(SIGQUIT);
		if (line[0] != '\0')
		{
			signal(SIGQUIT, handle_ctrl_backslash);
			signal(SIGINT, handle_ctrl_c_in_command);
			if (g_global_exit_status == 1)
				set_var(&data, "?", "130");
			prepare_command_execution(&line, &data);
			builtins_to_parsing(line, &data);
			free(line);
		}
		set_signal_handlers();
	}
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
