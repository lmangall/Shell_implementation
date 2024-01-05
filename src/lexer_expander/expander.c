/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:14:51 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/05 20:19:40 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/lexer.h"
#include "../../include/node.h"
#include "../../include/parser.h"
#include "../../include/shell.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

/**
 * @brief Expands a variable in a string by replacing it with its value.
 *
* This function takes a string containing a variable and replaces it with its corresponding value.
 *
 * @param str  A pointer to a string that may contain a variable to be expanded.
* @param var  A pointer to the variable structure containing the name and value.
 */
void	expand_var(char **str, t_vars **var)
{
	int		i;
	int		j;
	int		flag;
	char	*expanded_str;

	i = 0;
	j = 0;
	flag = 0;
	i = 0;
	j = 0;
	flag = 0;
	expanded_str = ft_strdup("");
	while ((*str)[j] != '\0')
	{
		if ((*str)[j] == '$' && flag == 0)
		{
			expanded_str = ft_strjoin(expanded_str, (*var)->value);
			i += ft_strlen((*var)->value);
			j += ft_strlen((*var)->name) + 1;
			flag = 1;
		}
		if ((*str)[j] != '\0')
		{
			expanded_str = ft_strjoin(expanded_str, (char[]){(*str)[j], '\0'});
			j++;
			i++;
		}
	}
	free(*str);
	*str = expanded_str;
}

t_vars	*find_var(char *name, t_data *data)
{
	int		i;
	t_vars	*control;

	i = 0;
	control = ft_calloc(1, sizeof(t_vars));
	if (!control)
		return (control);
	while (i < data->num_vars)
	{
		if (ft_strcmp(name, data->vars_container[i].name) == 0)
			return (&data->vars_container[i]);
		else
			i++;
	}
	return (control);
}

char	*identify_var(char *str, t_data *data)
{
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (i < data->num_vars)
	{
		if (ft_strstr(str, data->vars_container[i].name) != NULL)
			return (data->vars_container[i].name);
		else
			i++;
	}
	return (NULL);
}

char	*expand(char *str, t_data *data)
{
	char	*var_name;
	t_vars	*var;
	int		expansion;

	var_name = NULL;
	var = NULL;
	expansion = 5;
	if (contains_two(str, '\"') || contains_two(str, '\''))
		expansion = quote_type(str);
	if (expansion <= 2 || expansion == 5)
	{
		var_name = identify_var(str, data);
		var = find_var(var_name, data);
		expand_var(&str, &var);
	}
	if (contains_two(str, '\"') || contains_two(str, '\''))
		str = (char *)erase_outside_quotes(str);
	return (str);
}
