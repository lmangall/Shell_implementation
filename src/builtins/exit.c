/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:16:34 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/16 12:10:16 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/expander.h"
#include "../../include/free.h"
#include "../../include/parser.h"
#include "../../include/parser_nodes.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"

int	calculate_exit_code(char *arg)
{
	int	exit_code;

	exit_code = ft_atoi(arg) % 256;
	if (exit_code < 0)
		exit_code += 256;
	return (exit_code);
}

int	do_exit_builtin(char *line, t_data *data)
{
	char	**argv;
	int		exit_code;

	argv = ft_split(line, ' ');
	(void)data;
	if (argv[1] != NULL && argv[2] == NULL)
	{
		exit_code = calculate_exit_code(argv[1]);
	}
	else if (argv[1] == NULL)
	{
		exit_code = 0;
	}
	else
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		exit_code = 1;
	}
	free_string_array(argv);
	free(line);
	rl_clear_history();
	exit(exit_code);
}
