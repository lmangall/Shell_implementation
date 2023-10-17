/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:14:51 by lmangall          #+#    #+#             */
/*   Updated: 2023/10/17 13:10:21 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expander.h"
#include "../include/node.h"
#include "../include/parser.h"
#include "../include/shell.h"
#include "../lib/libft/src/libft.h"
#include <errno.h>
#include <expander.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// static char *ft_strtrim_single(char const *s1, char c) 
// {
//     size_t front = 0;
//     size_t rear;
//     char *str = NULL;

//     if (s1 != NULL) 
// 	{
//         rear = ft_strlen(s1);

//         while (s1[front] && s1[front] == c)
//             front++;

//         while (s1[rear - 1] && s1[rear - 1] == c && rear > front)
//             rear--;

//         str = (char *)malloc(sizeof(char) * (rear - front + 1));

//         if (str)
//             ft_strlcpy(str, &s1[front], rear - front + 1);
//     }

//     return str;
// }

static char *erase_substr(const char *str, const char *set) {
    if (str == NULL || set == NULL)
        return NULL;  // Check for NULL pointers

    size_t len = (ft_strlen(str) - ft_strlen(set));
    char *new_str = ft_calloc(len + 1, sizeof(char));

    if (new_str == NULL) {
        // Handle memory allocation failure
        perror("Memory allocation failed");
        return NULL;
    }

    size_t new_len = 0;
    size_t index = 0;
	size_t i = 0;
    while (str[i] != '\0') 
	{
        if (ft_strchr(set, str[i]) == NULL) 
		{
            new_str[index] = str[i];
            index++;
        }
        i++;
    }

    new_str[new_len] = '\0';  // Null-terminate the new string
    return new_str;
}


char	*identify_var(char *str, t_data *data)
{
// printf("inside identify_var\n");
	int		start;
	int		len;
	int		i;
	char	*var;

	i = 0;
	start = 0;
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
			break;//    carefull with this guy
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
// printf("RETURNING data->vars_container[i].name = %s\n", data->vars_container[i].name);
			return (data->vars_container[i].name);
// printf("data->vars_container[i].name = %s\n", data->vars_container[i].name);
		}
		else
			i++;
	}
	return (NULL);
}

// void	*ft_memcpy(void *dst, const void *src, size_t n)
// size_t	ft_strlcat(char *dst, const char *src, size_t size)
// char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
// char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
// char	*ft_strtrim(char const *s1, char const *set)

void expand_var(char **str, t_vars **var)
{
	int i = 0;
	int j = 0;
	int flag = 0;
	char *expanded_str;
	char *temp_str;

	i = 0;
	j = 0;
	flag = 0;

	// Allocate memory for expanded_str using ft_calloc
	expanded_str = ft_calloc((ft_strlen(*str)) + ft_strlen((*var)->value) - ft_strlen((*var)->name + 1), sizeof(char));
	if (!expanded_str) 
	{
		printf("ft_calloc failed for expanded_str\n");
		return;
	}

	// Allocate memory for temp_str using ft_calloc
	temp_str = ft_calloc(ft_strlen((*var)->name) + 2, sizeof(char));  // $ + var->name + '\0'
	if (!temp_str) {
		printf("ft_calloc failed for temp_str\n");
		free(expanded_str);  // Free previously allocated memory
		return;
	}

	while ((*str)[j] != '\0') {
		if ((*str)[j] == '$' && flag == 0) {
			temp_str[0] = '$';
			ft_strjoin(temp_str, (*var)->name);
			expanded_str = erase_substr(*str, temp_str);
			expanded_str = ft_strjoin(expanded_str, (*var)->value);
			i += ft_strlen((*var)->value);
			j += ft_strlen((*var)->name);
			j++;
			flag = 1;
		}

		expanded_str[i] = (*str)[j];
		j++;
		i++;
	}

	expanded_str[i] = '\0';
	// free(*str);
	// free(temp_str);  // Free temp_str
	*str = expanded_str;
}


char	*find_val(char *name, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_vars)
	{
		if (ft_strcmp(name, data->vars_container[i].name) == 0)
			return (data->vars_container[i].value);
		else
			i++;
	}
	return (NULL);
}

void	expand(struct node_s *node, t_data *data)
{
// printf("\ninside expand\n");
	char	*var_name;
	t_vars	*var;

	while ((var_name = identify_var(node->str, data)) != NULL)
	{
		var = find_var(var_name, data);
		// if (!(contains_two(node->str, '\'')))
		// {
		// 	printf("inside contains two of expand");
		// 	// erase_quotes(&node->str);
		// 	// if (contains_two(node->str, '\"'))
		// 	// 	erase_quotes_str(&node->str);
		// 	expand_var(&node->str, &var);
		// }
		expand_var(&node->str, &var);
		// ft_strtrim_single(&node->str, '\'')
	}
}


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

/*


                 ALL OF WHAT IS BELOW IS FORMER VERSION
				 THE CODE SHOULD WORK WITHOUT IT

*/



// char	*find_val(struct node_s *node, char *str, t_data *data)
// {
// 	char	*value;
// 	char	*var;

// 	var = identify_var(str);
// 	if (var && var_exists(data, var) == 0)
// 	{
// 		if (node != NULL)
// 			node->var_exists = true;
// 		value = search_env_var(data, var);
// 	}
// 	else if (var && var[0] == '?' && var[1] == '=')
// 		value = ft_itoa(g_last_exit_code);
// 	else
// 		value = NULL;
// 	free_ptr(var);
// 	return (value);
// }



// //takes a str that may contain on or several variables
// //returns a malloced string with the variables expanded
// //can use expand_var to expand each variable
// char	*expand_str(char *str, t_data *data)
// {
// 	char	*expanded_str;
// 	char	*tmp;
// 	char	*var;
// 	char	*value;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	expanded_str = malloc(sizeof(char) * ft_strlen(str) + 1);
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '$')
// 		{
// 			var = identify_var(str + i);
// 			value = find_val(NULL, var, data);
// 			if (value)
// 			{
// 				tmp = ft_strjoin(expanded_str, value);
// 				free_ptr(expanded_str);
// 				expanded_str = tmp;
// 				i += ft_strlen(var);
// 			}
// 			else
// 			{
// 				expanded_str[j] = str[i];
// 				j++;
// 				i++;
// 			}
// 			free_ptr(var);
// 		}
// 		else
// 		{
// 			expanded_str[j] = str[i];
// 			j++;
// 			i++;
// 		}
// 	}
// 	expanded_str[j] = '\0';
// 	return (expanded_str);
// }



// char *expand_var(char *node, t_data *data){
//     // Iterate through the variables in data->vars_container
//     for (int i = 0; i < data->num_vars; i++) 
// 	{
//         // Check if the token matches the variable name
//         if (strcmp(node, b. == 0 ||
//             (strlen(node) > 1 && strcmp(node + 1, data->vars_container[i].name) == 0)) {
//             // Return the corresponding variable value
//             return data->vars_container[i].value;
//         }
//     }

//     // Return NULL if the variable is not found
//     return NULL;
// }


// char	*identify_var(char *str)
// {
// 	char	*var;
// 	char	*tmp;
// 	int		start;
// 	int		len;
// 	int		i;

// 	i = 0;
// 	start = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			start = i + 1;
// 			break ;
// 		}
// 		i++;
// 	}
// 	len = var_length(str);
// 	var = ft_substr(str, start, len);
// 	if (!var)
// 		return (NULL);
// 	tmp = ft_strjoin(var, "=");
// 	free_ptr(var);
// 	var = tmp;
// 	return (var);
// }















// static int	contains_dollar(struct node_s *node)
// {
// 	if (node->str[0] == '$')
// 		return (1);
// 	return (0);
// }

// int	expansion_substitution(struct node_s *node, t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	if (contains_dollar(node))
// 	{
// 		while (i <= data->num_vars)
// 		{
// 			if (ft_strcmp(node->str + 1, data->vars_container[i].name) == 0)
// 			{
// 				set_node_str(node, data->vars_container[i].value);
// 				return (1);
// 			}
// 			i++;
// 		}
// 	}
// 	return (0);
// }

// char	*get_var_name(char *str)
// {
// 	int		i;
// 	char	*var_name;

// 	i = 0;
// 	var_name = malloc(sizeof(char) * strlen(str) + 1);
// 	while (str[i] != '=')
// 	{
// 		var_name[i] = str[i];
// 		i++;
// 	}
// 	var_name[i] = '\0';
// 	return (var_name);
// }

// static int	contains_equal(struct node_s *node)
// {
// 	int	i;

// 	i = 0;
// 	while (node->str[i] != '\0')
// 	{
// 		if (node->str[i] == '=')
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int	expansion_set_var(struct node_s *node, t_data *data)

// {
// 	if (contains_equal(node))
// 	{
// 		char *var_name = get_var_name(node->str);
// 		set_var(data, var_name, node->str + strlen(var_name) + 1);
// 		return (1);
// 	}
// 	return (0);
// }