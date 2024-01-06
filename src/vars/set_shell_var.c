/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shell_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:57:18 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 17:58:07 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/parser.h"
#include "../../include/parser_nodes.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

static int	check_max_vars(t_data *data)
{
	if (data->num_shell_vars >= MAX_VARS)
	{
		write(STDERR_FILENO, "Maximum number of shell variables reached\n", 43);
		return (-1);
	}
	return (0);
}

static int	find_var_index(t_data *data, const char *name)
{
	int	i;

	i = 0;
	while (i < data->num_shell_vars)
	{
		if (ft_strcmp(data->shell_vc[i].name, name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	set_new_var(t_data *data, const char *name, const char *value)
{
	int	index;

	index = data->num_shell_vars;
	ft_strlcpy(data->shell_vc[index].name, name,
		sizeof(data->shell_vc[index].name));
	data->shell_vc[index].name[sizeof(data->shell_vc[index].name) - 1] = '\0';
	ft_strlcpy(data->shell_vc[index].value, value,
		sizeof(data->shell_vc[index].value));
	data->shell_vc[index].value[sizeof(data->shell_vc[index].value) - 1] = '\0';
	data->num_shell_vars++;
	return (0);
}
int	set_shell_var(t_data *data, const char *name, const char *value)
{
	int	index;

	if (check_max_vars(data) == -1)
		return (-1);
	index = find_var_index(data, name);
	if (index >= 0)
	{
		ft_strlcpy(data->shell_vc[index].value, value,
			sizeof(data->shell_vc[index].value) - 1);
		data->shell_vc[index].value[sizeof(data->shell_vc[index].value)
			- 1] = '\0';
		return (0);
	}
	return (set_new_var(data, name, value));
}
