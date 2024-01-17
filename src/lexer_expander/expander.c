/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:14:51 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 20:44:42 by lmangall         ###   ########.fr       */
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

int	inside_quote(const char *str)
{
	const char	*start_quote = find_first_quotes(str);
	const char	*end_quote = find_last_quotes(str);

	if (start_quote != NULL && end_quote != NULL && *start_quote == '\"'
		&& *end_quote == '\"')
		return (2);
	if (start_quote != NULL && end_quote != NULL && *start_quote == '\''
		&& *end_quote == '\'')
		return (3);
	return (5);
}

int	contains_two(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (count == 2)
		return (1);
	return (0);
}

void	handle_variable(char *var_name, t_data *data, char *xpned_str, int *idx)
{
	char	*var_value;
	int		var_name_len;

	var_name_len = ft_strlen(var_name);
	var_value = find_var_value(var_name, data);
	if (var_value != NULL)
		append_variable_value(var_value, xpned_str, idx);
	else
	{
		xpned_str[(*idx)++] = '$';
		ft_memcpy(&xpned_str[*idx], var_name, var_name_len);
		*idx += var_name_len;
	}
	free(var_name);
}

void	expand_variables(char *str, t_data *data, char *xpned_str, int *idx)
{
	int		o_i;
	char	*var_name;

	o_i = 0;
	var_name = extract_variable_name(str, &o_i);
	while (str[o_i] != '\0')
	{
		if (str[o_i] == '$')
		{
			if (var_name != NULL)
				handle_variable(var_name, data, xpned_str, idx);
			else
				xpned_str[(*idx)++] = '$';
		}
		else
			xpned_str[(*idx)++] = str[o_i++];
	}
	xpned_str[*idx] = '\0';
}

char	*expand(char *str, t_data *data)
{
	char	*expanded_str;
	int		expanded_index;
	int		expansion;

	expansion = 5;
	expanded_index = 0;
	expanded_str = (char *)malloc(sizeof(char) * (ft_strlen(str) * 15 + 1));
	if (expanded_str == NULL)
		return (NULL);
	if (contains_two(str, '\"') || contains_two(str, '\''))
		expansion = quote_pattern(str);
	if (expansion <= 2 || expansion == 5)
	{
		expand_variables(str, data, expanded_str, &expanded_index);
		return (expanded_str);
	}
	else
	{
		free(expanded_str);
		return (str);
	}
}
