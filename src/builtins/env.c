/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:06:14 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/16 11:22:54 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/expander.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <stdio.h>
#include <unistd.h>

#define COLOR_RESET "\x1b[0m"
#define COLOR_BOLD "\x1b[1m"
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"

static void	print_variable(const char *name, const char *value)
{
	write(STDOUT_FILENO, name, ft_strlen(name));
	write(STDOUT_FILENO, "=", 1);
	write(STDOUT_FILENO, value, ft_strlen(value));
	write(STDOUT_FILENO, "\n", 1);
}

static void	print_environment_variables(t_data *data, int num_vars)
{
	int	i;

	i = 0;
	while (i < num_vars)
	{
		print_variable(data->vc[i].name, data->vc[i].value);
		i++;
	}
}

static void	print_shell_variables(t_data *data, int num_shell_vars)
{
	int	j;

	j = 0;
	write(STDOUT_FILENO, "Shell Vars (for clarity) :\n", 28);
	while (j < num_shell_vars)
	{
		print_variable(data->shell_vc[j].name, data->shell_vc[j].value);
		j++;
	}
}

int	do_env_builtin(t_data *data)
{
	ft_putstr_fd("Name            Value\n", STDOUT_FILENO);
	print_environment_variables(data, data->num_vars);
	if (data->num_shell_vars > 0)
	{
		print_shell_variables(data, data->num_shell_vars);
	}
	return (-1);
}
