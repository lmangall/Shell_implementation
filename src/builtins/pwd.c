/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:06:44 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 15:03:32 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/expander.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

int	do_pwd_builtin(t_data *data)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	(void)data;
	if (pwd == NULL)
	{
		fprintf(stderr, "pwd: error retrieving current directory: getcwd: cannot access parent directories: %s\n", strerror(errno));
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (-1);
}
