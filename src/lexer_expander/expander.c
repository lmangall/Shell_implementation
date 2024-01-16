/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:14:51 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/16 20:34:14 by ohoro            ###   ########.fr       */
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

int	surrounded_by_double_quotes(char *str, int current_index)
{
	int	double_quotes_count;
	int	i;

	double_quotes_count = 0;
	i = 0;
	while (i <= current_index)
	{
		if (str[i] == '"')
		{
			double_quotes_count++;
		}
		i++;
	}

	return (double_quotes_count % 2 != 0);
}

int	is_inside_single_quotes(char *str, int current_index)
{
	int	inside_single_quotes;
	int	i;

	inside_single_quotes = 0;
	i = 0;
	while (i < current_index)
	{
		if (str[i] == '\'')
		{
			inside_single_quotes = !inside_single_quotes;
		}
		i++;
	}
	return (inside_single_quotes);
}

char	*expand(char *str, t_data *data)
{
	char	*expanded_str;
	int		o_i;
	int		expanded_index;
	char	*var_name;
	char	*var_value;

	expanded_str = allocate_memory_for_expanded_string(str);
	o_i = 0;
	expanded_index = 0;

	while (str[o_i] != '\0')
	{
	//	if (str[o_i] == '$' && !is_inside_single_quotes(str, o_i))
	if ((str[o_i] == '$' && surrounded_by_double_quotes(str, o_i) && is_inside_single_quotes(str, o_i))
			|| (str[o_i] == '$' && !is_inside_single_quotes(str, o_i)))

		{
			var_name = extract_variable_name(str, &o_i);
			var_value = find_var_value(var_name, data);
			if (var_value != NULL)
				append_variable_value(var_value, expanded_str, &expanded_index);
			free(var_name);
		}
		else
			expanded_str[expanded_index++] = str[o_i++];
	}
	expanded_str[expanded_index] = '\0';
	return (expanded_str);
}
