/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:07:18 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 21:06:00 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/expander.h"
#include "../../include/parser.h"
#include "../../include/parser_nodes.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

// the builtins return -1 if they are called
// if they return -1 to main, main exit the readline main loop
int	check_for_builtins(char *line, t_data *data)
{
	int	ret;

	ret = 1;
	check_for_variable_setting(data, line);
	if (ft_strncmp(line, "unset ", 6) == 0)
		ret = do_unset_builtin(lexer(line), data);
	else if (ft_strncmp(line, "export ", 7) == 0)
		ret = do_export_builtin(lexer(line), data);
	else if (ft_strncmp(line, "cd ", 3) == 0)
		ret = do_cd_builtin(lexer(line), data);
	else if (ft_strcmp(line, "env") == 0)
		ret = do_env_builtin(data);
	else if (ft_strcmp(line, "pwd") == 0)
		ret = do_pwd_builtin(data);
	else if (ft_strncmp(line, "echo ", 5) == 0)
		ret = do_echo_builtin(lexer(line));
	else if (ft_strcmp(line, "exit") == 0)
	{
		printf("exit\n");
		return (2);
	}
	return (ret);
}

void	display_history(void)
{
	int			i;
	HIST_ENTRY	*entry;

	i = history_base;
	while (i < history_length)
	{
		entry = history_get(i);
		if (entry != NULL)
			printf("%d: %s\n", i, entry->line);
	}
	i++;
}
