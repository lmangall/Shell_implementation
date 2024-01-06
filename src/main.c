/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:22:39 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 14:03:09 by lmangall         ###   ########.fr       */
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
#include "../include/main.h"
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
