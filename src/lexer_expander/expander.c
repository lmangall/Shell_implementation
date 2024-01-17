/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:14:51 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 21:52:24 by lmangall         ###   ########.fr       */
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

int	quote_pattern(const char *str)
{
	int	ret;

	ret = 0;
	if (contains_two((char *)str, '\"') && contains_two((char *)str, '\''))
		ret = inside_quote(str);
	else
	{
		if (contains_two((char *)str, '\"'))
			ret = 1;
		if (contains_two((char *)str, '\''))
			ret = 4;
	}
	return (ret);
}

void	expand_variables(char *str, t_data *data, char *xpned_str, int *idx)
{
	data->o_i = 0;
	while (str[data->o_i] != '\0')
	{
		if (str[data->o_i] == '$')
			process_variable(str, data, xpned_str, idx);
		else
			xpned_str[(*idx)++] = str[data->o_i++];
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
