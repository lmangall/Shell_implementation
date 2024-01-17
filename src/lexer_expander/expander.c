/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:14:51 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 16:35:25 by lmangall         ###   ########.fr       */
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

char *expand(char *str, t_data *data)
{
	char *expanded_str;
	int o_i;
	int expanded_index;
	char *var_name;
	char *var_value;
	t_vars *var;
	int expansion;

	var_name = NULL;
	var = NULL;
	expansion = 5;
	o_i = 0;
	expanded_index = 0;
	expanded_str = (char *)malloc(sizeof(char) * (ft_strlen(str) * 2 + 1)); //      THIS IS WRONG
	if (expanded_str == NULL)
		return (NULL);

	if (contains_two(str, '\"') || contains_two(str, '\''))
		expansion = quote_pattern(str);
	if (expansion <= 2 || expansion == 5)
	{
		while (str[o_i] != '\0')
		{
			if (str[o_i] == '$')
			{
				var_name = extract_variable_name(str, &o_i);
				if (var_name == NULL)
					printf("var_name is NULL\n");
				var_value = find_var_value(var_name, data);
				if (var_value != NULL)
					append_variable_value(var_value, expanded_str, &expanded_index);
				else
				{
					expanded_str[expanded_index++] = '$';
					o_i++;
				}
				free(var_name);
			}
			else
				expanded_str[expanded_index++] = str[o_i++];
		}
		expanded_str[expanded_index] = '\0';
	return expanded_str;  //           THE OTHER HAS TO BE FREED

	}
	else
		return (str);//           THE OTHER HAS TO BE FREED

}


