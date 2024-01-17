/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:13:46 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 20:30:56 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/lexer.h"
#include "../../include/main.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
#include "../../include/vars.h"
#include "../../include/free.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	get_quote_type(char c)
{
	if (c == '\'')
		return (1);
	else
		return (2);
}

void process_variable(char *str, t_data *data, char *xpned_str, int *idx, int *o_i)
{
	char *var_name = extract_variable_name(str, o_i);
	if (var_name != NULL)
	{
		char *var_value = find_var_value(var_name, data);
		if (var_value != NULL)
			append_variable_value(var_value, xpned_str, idx);
		else
			handle_missing_variable(var_name, xpned_str, idx);
		free(var_name);
	}
	else
		xpned_str[(*idx)++] = '$';
}
