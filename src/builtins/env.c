/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:06:14 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 15:03:32 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/expander.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <stdio.h>

#define COLOR_RESET "\x1b[0m"
#define COLOR_BOLD "\x1b[1m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"

int	do_env_builtin(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf(COLOR_BOLD "%-26s%-18s\n" COLOR_RESET, "Name", "Value");
	while (i < data->num_vars)
	{
		printf("%s%-26s" COLOR_RESET, COLOR_GREEN, data->vc[i].name);
		printf("%s\n", data->vc[i].value);
		i++;
	}
	if (data->num_shell_vars > 0)
	{
		printf("%sShell Vars (for clarity) :\n" COLOR_RESET, COLOR_BOLD);
		while (j < data->num_shell_vars)
		{
			printf("%s%-26s" COLOR_RESET, COLOR_RED, data->shell_vc[j].name);
			printf("%s\n", data->shell_vc[j].value);
			j++;
		}
	}
	return (-1);
}
