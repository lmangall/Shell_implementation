/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:14:51 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/05 17:48:34 by lmangall         ###   ########.fr       */
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

// static int	return_var_name_len(char *str)
// {
// 	printf("in return_var_name_len");
// 	int	i;
// 	int	start;
// 	int	len;

// 	i = 0;
// 	start = 0;
// 	len = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			start = i;
// 			while (str[i] != ' ' && str[i] != '\0' && (str[i] >= 'A'
// 					&& str[i] <= 'Z'))
// 				i++;
// 			len = i - start;
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (len);
// }

// char	*identify_var(char *str, t_data *data)
// {
// 		printf("in identify_var");

// 	int		start;
// 	int		len;
// 	int		i;
// 	char	*var;

// 	start = 0;
// 	len = 0;
// 	i = 0;
// 	var = NULL;
// 	if (str == NULL)
// 		return (NULL);
// 	printf("in identify_var 2");

// 	while (str[start] != '$')
// 		start++;
// 	len = return_var_name_len(str);
// 	printf("len = %i", len);
// 	while (i < data->num_vars)
// 	{
// 		if (len >= 0)
// 		{
// 			var = ft_substr(str, start + 1, ft_strlen(data->vars_container[i].name));
// 		}
// 		if (ft_strcmp(var, data->vars_container[i].name) == 0)
// 		{
// 			free(var);
// 			return (data->vars_container[i].name);
// 		}
// 		else
// 			i++;
// 	}
// 	free(var);
// 	return (NULL);
// }

// char	*identify_var_in_string(char *str, int *start, int *len)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			*start = i;
// 			while (str[i] != ' ' && str[i] != '\0' && (str[i] >= 'A'
// 					&& str[i] <= 'Z'))
// 			{
// 				i++;
// 			}
// 			*len = i - *start;
// 			break ;
// 		}
// 		i++;
// 	}
// 	if (*len > 0)
// 	{
// 		return (ft_substr(str, *start + 1, *len));
// 	}
// 	return (NULL);
// }

// // Main function using helper functions
// char	*identify_var(char *str, t_data *data)
// {
// 	int		start;
// 	int		len;
// 	char	*var;

// 	start = 0;
// 	len = 0;
// 	var = NULL;
// 	if (str == NULL)
// 		return (NULL);
// 	var = identify_var_in_string(str, &start, &len);
// 	if (var != NULL)
// 	{
// 		for (int i = 0; i < data->num_vars; i++)
// 		{
// 			if (ft_strcmp(var, data->vars_container[i].name) == 0)
// 			{
// 				free(var);
// 				return (data->vars_container[i].name);
// 			}
// 		}
// 		free(var);
// 	}
// 	return (NULL);
// }

/**
 * @brief Identifies a variable in a string and returns its name.
 *

	* This function searches for a variable starting with the '$' character in the given string.

	* It returns the name of the identified variable or NULL if no variable is found.
 *
 * @param str   The input string to search for variables.

	* @param data  A pointer to the data structure containing information about variables.
 *

	* @return A dynamically allocated string representing the name of the identified variable,
 *         or NULL if no variable is found or on memory allocation failure.
//  */
char	*identify_var(char *str, t_data *data)
{
	int		start;
	int		len;
	int		i;
	char	*var;

	start = 0;
	len = 0;
	i = 0;
	var = NULL;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i;
			while (str[i] != ' ' && str[i] != '\0' && (str[i] >= 'A'
					&& str[i] <= 'Z'))
				i++;
			len = i - start;
			(void)len;
			break ;
		}
		i++;
	}
	i = 0;
	while (i < data->num_vars)
	{
		if (len >= 0)
		{
			var = ft_substr(str, start + 1,
			ft_strlen(data->vars_container[i].name));
		}
		if (ft_strcmp(var, data->vars_container[i].name) == 0)
		{
			free(var);
			return (data->vars_container[i].name);
		}
		else
			i++;
	}
	free(var);
	return (NULL);
}

/**
 * @brief Finds a variable in the data structure by its name.
 *

	* This function searches for a variable with the given name in the data structure.
 * If found, it returns a pointer to the variable; otherwise,
	it returns a control structure.
 *
 * @param name  The name of the variable to find.

	* @param data  A pointer to the data structure containing information about variables.
 *

	* @return A pointer to the found variable or a control structure if the variable is not found
 *         or on memory allocation failure.
 */
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

char	*expand(char *str, t_data *data)
{
	char	*var_name;
	t_vars	*var;
	int		i;
	int		expansion;

	i = 0;
	expansion = 5;
	if (contains_two(str, '\"') || contains_two(str, '\''))
		expansion = quote_type(str);
	if (expansion <= 2 || expansion == 5)
	{
		while ((var_name = identify_var(str, data)) != NULL || i < 5)
		{
			var = find_var(var_name, data);
			expand_var(&str, &var);
			i++;
		}
	}
	if (contains_two(str, '\"') || contains_two(str, '\''))
		str = (char *)erase_outside_quotes(str);
	return (str);
}
