/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:14:51 by lmangall          #+#    #+#             */
/*   Updated: 2023/10/10 20:59:27 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expander.h"
#include "../include/node.h"
#include "../include/parser.h"
#include "../include/shell.h"
#include "../lib/libft/src/libft.h"
#include <errno.h>
#include <expander.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int	contains_dollar(struct node_s *node)
{
	if (node->str[0] == '$')
		return (1);
	return (0);
}

int	expansion_substitution(struct node_s *node, t_data *data)
{
	int	i;

	i = 0;
	if (contains_dollar(node))
	{
		while (i <= data->num_vars)
		{
			if (ft_strcmp(node->str + 1, data->vars_container[i].name) == 0)
			{
				set_node_str(node, data->vars_container[i].value);
				return (1);
			}
			i++;
		}
	}
	return (0);
}

char	*get_var_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	var_name = malloc(sizeof(char) * strlen(str) + 1);
	while (str[i] != '=')
	{
		var_name[i] = str[i];
		i++;
	}
	var_name[i] = '\0';
	return (var_name);
}

static int	contains_equal(struct node_s *node)
{
	int	i;

	i = 0;
	while (node->str[i] != '\0')
	{
		if (node->str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	expansion_set_var(struct node_s *node, t_data *data)

{
	if (contains_equal(node))
	{
		char *var_name = get_var_name(node->str);
		set_var(data, var_name, node->str + strlen(var_name) + 1);
		return (1);
	}
	return (0);
}