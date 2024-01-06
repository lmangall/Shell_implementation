/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:57:06 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 17:57:08 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/parser.h"
#include "../../include/parser_nodes.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

static int	set_existing_var(t_data *data, int i, const char *value)
{
	ft_strlcpy(data->vc[i].value, value, sizeof(data->vc[i].value));
	data->vc[i].value[sizeof(data->vc[i].value) - 1] = '\0';
	return (0);
}

static int	set_new_var(t_data *data, const char *name, const char *value)
{
	ft_strlcpy(data->vc[data->num_vars].name, name,
		sizeof(data->vc[data->num_vars].name));
	data->vc[data->num_vars].name[sizeof(data->vc[data->num_vars].name)
		- 1] = '\0';
	ft_strlcpy(data->vc[data->num_vars].value, value,
		sizeof(data->vc[data->num_vars].value));
	data->vc[data->num_vars].value[sizeof(data->vc[data->num_vars].value)
		- 1] = '\0';
	data->num_vars++;
	return (0);
}

static int	check_var_limit(t_data *data)
{
	if (data->num_vars >= MAX_VARS)
	{
		write(STDERR_FILENO, "Maximum number of variables reached\n", 37);
		return (-1);
	}
	return (0);
}


int	set_var(t_data *data, const char *name, const char *value)
{
	int	i;

	i = 0;
	if (check_var_limit(data) == -1)
		return (-1);
	while (i < data->num_vars)
	{
		if (ft_strcmp(data->vc[i].name, name) == 0)
		{
			return (set_existing_var(data, i, value));
		}
		i++;
	}
	if (check_var_limit(data) == -1)
		return (-1);
	return (set_new_var(data, name, value));
}
