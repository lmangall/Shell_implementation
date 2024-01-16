/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:14:51 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/16 12:38:26 by ohoro            ###   ########.fr       */
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
		if (strcmp(var_name, data->shell_vc[i].name) == 0)
		{
			return (strdup(data->shell_vc[i].value));
		}
		i++;
	}
	i = 0;
	while (i < data->num_vars)
	{
		if (strcmp(var_name, data->vc[i].name) == 0)
		{
			return (strdup(data->vc[i].value));
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
		&& ((isalnum(str[*original_index]) || str[*original_index] == '_') 
			|| str[*original_index] == '?'))
	{
		var_name[var_name_index++] = str[(*original_index)++];
	}
	var_name[var_name_index] = '\0';
	return (strdup(var_name));
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

	expanded_str = (char *)malloc(strlen(str) * 2 + 1);
	if (!expanded_str)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	return (expanded_str);
}

char	*expand(char *str, t_data *data)
{
	char	*expanded_str;
	int		original_index;
	int		expanded_index;
	char	*var_name;
	char	*var_value;

	expanded_str = allocate_memory_for_expanded_string(str);
	original_index = 0;
	expanded_index = 0;
	while (str[original_index] != '\0')
	{
		if (str[original_index] == '$')
		{
			var_name = extract_variable_name(str, &original_index);
			var_value = find_var_value(var_name, data);
			if (var_value != NULL)
			{
				append_variable_value(var_value, expanded_str, &expanded_index);
			}
		}
		else
			expanded_str[expanded_index++] = str[original_index++];
	}
	expanded_str[expanded_index] = '\0';
	return (expanded_str);
}


// var->value
// var->name

// //this function should replace one or several variables in a string
// //the variables start with $ and are followed by a name (var-name)

// void	expand_var(char **str, t_vars **var)
// {
// 	int		i;
// 	int		j;
// 	char	*str_xpnded;

// 	i = 0;
// 	j = 0;
// 	str_xpnded = ft_strdup("");
// 	while ((*str)[j] != '\0')
// 	{
// 		if ((*str)[j] == '$')
// 		{
// 			str_xpnded = ft_strjoin(str_xpnded, (*var)->value);
// 			i += ft_strlen((*var)->value);
// 			j += ft_strlen((*var)->name) + 1;
// 		}
// 		if ((*str)[j] != '\0')
// 		{
// 			str_xpnded = ft_strjoin(str_xpnded, ft_substr(*str, j, 1));
// 			j++;
// 			i++;
// 		}
// 	}
// 	free(*str);
// 	*str = str_xpnded;
// }
// t_vars	*find_var(char *name, t_data *data)
// {
// 	int		i;
// 	t_vars	*control;

// 	i = 0;
// 	control = ft_calloc(1, sizeof(t_vars));
// 	if (!control)
// 		return (control);
// 	while (i < data->num_vars)
// 	{
// 		if (ft_strcmp(name, data->vc[i].name) == 0)
// 		{
// 			free(control);
// 			return (&data->vc[i]);
// 		}
// 		else
// 			i++;
// 	}
// 	return (control);
// }

// char	*identify_var(char *str, t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	if (str == NULL)
// 		return (NULL);
// 	while (i < data->num_vars)
// 	{
// 		if (ft_strstr(str, data->vc[i].name) != NULL)
// 			return (data->vc[i].name);
// 		else
// 			i++;
// 	}
// 	return (NULL);
// }

// char	*expand(char *str, t_data *data)
// {
// 	char	*var_name;
// 	t_vars	*var;
// 	int		expansion;
// 	char	*str_without_quotes;

// 	var_name = NULL;
// 	var = NULL;
// 	expansion = 5;
// 	if (contains_two(str, '\"') || contains_two(str, '\''))
// 		expansion = quote_pattern(str);
// 	if (expansion <= 2 || expansion == 5)
// 	{
// 		var_name = identify_var(str, data);
// 		if (var_name == NULL)
// 			return (str);
// 		var = find_var(var_name, data);
// 		expand_var(&str, &var);
// 	}
// 	if (contains_two(str, '\"') || contains_two(str, '\''))
// 	{
// 		str_without_quotes = (char *)erase_outside_quotes(str);
// 		data->erased_out_quotes = 1;
// 		free(str);
// 		str = str_without_quotes;
// 	}
// 	return (str);
// }
