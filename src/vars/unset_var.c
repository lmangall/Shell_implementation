/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:54:37 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 22:04:05 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vars.h"
#include "../../include/expander.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
#include "../../lib/libft/src/libft.h"
#include "../../include/free.h"
#include <errno.h>
#include <unistd.h>

int	find_var_index(t_data *data, const char *name)
{
	int	i;

	i = 0;
	while (i < data->num_shell_vars)
	{
		if (ft_strcmp(data->shell_vc[i].name, name) == 0)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

void	remove_var_at_index(t_data *data, int index)
{
	int	j;

	j = index;
	while (j < data->num_shell_vars - 1)
	{
		ft_strlcpy(data->shell_vc[j].name, data->shell_vc[j + 1].name, 50);
		ft_strlcpy(data->shell_vc[j].value, data->shell_vc[j + 1].value, 150);
		j++;
	}
	data->num_shell_vars--;
	data->shell_vc[data->num_shell_vars].name[0] = '\0';
	data->shell_vc[data->num_shell_vars].value[0] = '\0';
}

int	unset_shell_var(t_data *data, const char *name)
{
	int	index;

	index = find_var_index(data, name);
	if (index == -1)
	{
		//perror("Variable not found");
		return (-1);
	}
	remove_var_at_index(data, index);
	return (0);
}

int	unset_var(t_data *data, const char *name)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->num_vars)
	{
		if (ft_strcmp(data->vc[i].name, name) == 0)
		{
			j = i;
			while (j < data->num_vars - 1)
			{
				ft_strlcpy(data->vc[j].name, data->vc[j + 1].name, 50);
				ft_strlcpy(data->vc[j].value, data->vc[j + 1].value, 150);
				j++;
			}
			data->num_vars--;
			data->vc[data->num_vars].name[0] = '\0';
			data->vc[data->num_vars].value[0] = '\0';
			return (0);
		}
		i++;
	}
	return (-1);
}

// if the command "unset" is called with a space
// and a variable name, it will call this function unset

int	do_unset_builtin(char **tokens, t_data *data)
{
	int	i;

	i = 1;
	while (tokens[i] != NULL)
	{
		if (unset_shell_var(data, tokens[i]) == 0)
		{
			i++;
		}
		else
		{
			unset_var(data, tokens[i]);
			i++;
		}
	}
	free_string_array(tokens);
	return (-1);
}
