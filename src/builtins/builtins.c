/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:07:18 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/11 12:16:20 by lmangall         ###   ########.fr       */
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
	int		ret;

	ret = 1;
	ret = check_for_variable_setting(data, line);
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
	else if (ft_strncmp(line, "exit", 4) == 0)
		ret = do_exit_builtin(line, data);
	return (ret);
}
