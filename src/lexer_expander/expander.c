/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:14:51 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/04 15:48:33 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"
#include "../../include/shell.h"
#include "../../include/vars.h"
#include "../../include/expander.h"
#include "../../include/node.h"
#include "../../include/parser.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

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
 */
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
			while(str[i] != ' ' && str[i] != '\0' && (str[i] >= 'A' && str[i] <= 'Z'))
				i++;
			len = i - start;
			(void)len;
			break;
		}
		i++;
	}
	i = 0;
	while (i < data->num_vars)
	{
		if (len >= 0)
		{
// printf("str, start, len = %s, %d, %d\n", str, start, len);
		var = ft_substr(str, start + 1, ft_strlen(data->vars_container[i].name));
// printf(" = str + start + 1 = %s\n", str + start + 1);
// printf("var = %s\n", var);
		}
		if (ft_strcmp(var, data->vars_container[i].name) == 0)
		{
			free(var);
// printf("RETURNING data->vars_container[i].name = %s\n", data->vars_container[i].name);
			return (data->vars_container[i].name);
// printf("data->vars_container[i].name = %s\n", data->vars_container[i].name);
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
 * If found, it returns a pointer to the variable; otherwise, it returns a control structure.
 *
 * @param name  The name of the variable to find.
 * @param data  A pointer to the data structure containing information about variables.
 *
 * @return A pointer to the found variable or a control structure if the variable is not found
 *         or on memory allocation failure.
 */
t_vars	*find_var(char *name, t_data *data)
{
	int	i;
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
void expand_var(char **str, t_vars **var)
{
    int i = 0;
    int j = 0;
    int flag = 0;
    char *expanded_str;

    i = 0;
    j = 0;
    flag = 0;
    expanded_str = ft_strdup("");  // Initialize with an empty string

    while ((*str)[j] != '\0') 
    {
        if ((*str)[j] == '$' && flag == 0) 
        {
            expanded_str = ft_strjoin(expanded_str, (*var)->value);
            i += ft_strlen((*var)->value);
            j += ft_strlen((*var)->name) + 1;  // +1 to skip the '$' character
            flag = 1;
        }

        if ((*str)[j] != '\0')
        {
            expanded_str = ft_strjoin(expanded_str, (char[]){(*str)[j], '\0'});  // Append one character at a time
            j++;
            i++;
        }
    }
    free(*str);
    *str = expanded_str;
}


/**
 * @brief Expands variables within a node's string.
 *
 * This function recursively expands variables within the string of a given node.
 * It identifies variables, finds their values, and expands them in the node's string.
 *
 * @param node  A double pointer to the node whose string is to be expanded.
 * @param data  A pointer to the data structure containing information about variables.
 */
void expand(struct node_s **node, t_data *data)
{
    char *var_name;
    t_vars *var;
    int i = 0;
	int expansion = 0;

	//1 if there is double quotes ("), not preceeded by single quotes('), then expand and remove the double quotes
	//2 if there is single quotes ('), expand only if they are inside double quotes
	//3 if there is no quotes, expand and erase single quotes

    while ((var_name = identify_var((*node)->str, data)) != NULL || i < 5)
    {
        var = find_var(var_name, data);
        expand_var(&(*node)->str, &var);
        i++;
    }
}


	
// /**
// 	* @brief This function that takes a string
// 	*the function should return 1 if there is double quotes, not preceeded by single quotes
// 	*the function should return 2 if there is single quotes inside double quotes
// 	*the function should return 3 if there is no quotes
// 	*otherwise the function should return 0
// 	 */
// int should_expand(char *str)
// {
//     int i = 0;
//     int double_quotes = 0;
//     int single_quotes = 0;

//     while (str[i] != '\0')
//     {
//         if (str[i] == '\"' && single_quotes == 0)
//             double_quotes++;
//         if (str[i] == '\'' && double_quotes % 2 == 1)
//             single_quotes++;
//         i++;
//     }

//     if (double_quotes % 2 == 1 && single_quotes == 0)
//         return 1;
//     if (double_quotes % 2 == 1 && single_quotes % 2 == 1)
//         return 2;
//     if (double_quotes == 0 && single_quotes == 0)
//         return 3;

//     return 0;
// }