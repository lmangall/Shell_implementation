/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:07:18 by lmangall          #+#    #+#             */
/*   Updated: 2023/12/14 21:57:32 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/expander.h"
#include "../../include/node.h"
#include "../../include/parser.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

//the -1 return is needed for the command not be executed
int	check_and_builtins(char *line, t_data *data)
{
	// check_for_variable_setting(data, line);

	// if (ft_strncmp(line, "unset ", 6) == 0)
	// {
	// 	do_unset_builtin(lexer(line), data);
	// 	return (-1);
	// }
	// if (ft_strncmp(line, "export ", 7) == 0)
	// {
	// 	do_export_builtin(lexer(line), data);
	// 	return (-1);
	// }
	if (ft_strcmp(line, "exit") == 0)
	{
		printf("exit\n");
		return(2);
	}
	if (ft_strncmp(line, "cd ", 3) == 0)
	{
		do_cd_builtin(lexer(line), data);
		return (-1);
	}
	if (ft_strcmp(line, "env") == 0) ///     => check if working properly
	{
		do_env_builtin(data);
		return (-1);
	}
	if (ft_strcmp(line, "pwd") == 0)
	{
		do_pwd_builtin(data);
		return (-1);
	}

	// 	display_history();

	
	return (1);
}

void display_history()
{
	int i = history_base;

	while (i < history_length)
	{
		HIST_ENTRY *entry = history_get(i);
		if (entry != NULL)
			printf("%d: %s\n", i, entry->line);
	}
		i++;
}