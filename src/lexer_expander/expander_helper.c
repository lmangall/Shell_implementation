/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 19:13:25 by ohoro             #+#    #+#             */
/*   Updated: 2024/01/17 18:57:42 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/lexer.h"
#include "../../include/main.h"
#include "../../include/parser.h"
#include "../../include/parser_nodes.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

char	*find_var_value(char *var_name, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_shell_vars)
	{
		if (ft_strcmp(var_name, data->shell_vc[i].name) == 0)
		{
			return (ft_strdup(data->shell_vc[i].value));
		}
		i++;
	}
	i = 0;
	while (i < data->num_vars)
	{
		if (ft_strcmp(var_name, data->vc[i].name) == 0)
		{
			return (ft_strdup(data->vc[i].value));
		}
		i++;
	}
	return (NULL);
}
char	*extract_variable_name(char *str, int *original_index)
{
	char	var_name[50];
	int		var_name_index;

	(*original_index)++;
	var_name_index = 0;
	while ((str[*original_index] != '\0')
		&& ((ft_isalnum(str[*original_index]) || str[*original_index] == '_') 
			|| str[*original_index] == '?'))
	{
		var_name[var_name_index++] = str[(*original_index)++];
	}
	var_name[var_name_index] = '\0';

	if (var_name_index == 0)
		return NULL;

	return (ft_strdup(var_name));
}

void	append_variable_value(char *var_value, char *expanded_str,
		int *expanded_index)
{
	int	var_value_index;

	var_value_index = 0;
	while (var_value[var_value_index] != '\0')
	{
		expanded_str[(*expanded_index)++] = var_value[var_value_index++];
	}
	free(var_value);
}

char	*allocate_memory_for_expanded_string(char *str)
{
	char	*expanded_str;

	expanded_str = (char *)malloc(ft_strlen(str) * 2 + 1);
	if (!expanded_str)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	return (expanded_str);
}
