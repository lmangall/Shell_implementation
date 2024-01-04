/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:14:51 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/04 12:51:31 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"
#include "../../include/shell.h"
#include "../../include/fcntl.h"
#include "../../include/vars.h"
#include "../../include/expander.h"
#include "../../include/node.h"
#include "../../include/parser.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

// static char *ft_strtrim_single(char **s1, char c) 
// {
// 	size_t front = 0;
// 	size_t rear = 0;
// 	char *str = NULL;
// 	printf("inside ft_strtrim_single\n");

// 	if (s1 != NULL && *s1 != NULL && **s1 != '\0') 
// 	{
// 		rear = ft_strlen(*s1);
// printf("rear = %zu\n", rear);

// 		while (front < rear && (*s1)[front] == c)
// 			front++;
// printf("front = %zu\n", front);

// 		while (rear > front && (*s1)[rear - 1] == c)
// 			rear--;
// printf("rear = %zu\n", rear);

// 		str = ft_calloc(rear - front + 1, sizeof(char));
// printf("str = %s\n", str);
// 		if (str)
// 			ft_strlcpy(str, &(*s1)[front], rear - front + 1);
// 	}
// printf("str = %s\n", str);

// 	return str;
// }
	// int	ft_strncmp(const char *str1, const char *str2, size_t n);
	// int	ft_strcmp(const char *s1, const char *s2);

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


void	trim_quotes(char **str, char quote) 
{
	int i = 0;
	int j = 0;
	char *trimmed_str;

	trimmed_str = ft_calloc(ft_strlen(*str) - 1, sizeof(char));
	while (*str[i] != '\0') 
	{
		if (*str[i] != quote)
		{
			trimmed_str[j] = *str[i];
			j++;
		}
		i++;
	}
	free((char *)str);
	trimmed_str[j] = '\0';
	*str = trimmed_str;
}

void expand(struct node_s **node, t_data *data)
{
    char *var_name;
    t_vars *var;
    int i = 0;

    while ((var_name = identify_var((*node)->str, data)) != NULL || i < 5)
    {
        var = find_var(var_name, data);
        expand_var(&(*node)->str, &var);
        i++;
    }
}

// void	expand(struct node_s **node, t_data *data)
// {
// // printf("\ninside expand\n");
// 	char	*var_name;
// 	t_vars	*var;
// 	int i = 0;

// // 	if (contains_two((*node)->str, '\"'))
// // 	{
// // 			trim_quotes(&(*node)->str, '\"');
// // printf("node->str in expand 1= %s\n", (*node)->str);
// // 		while ((var_name = identify_var((*node)->str, data)) != NULL || i < 5)
// // 		{
// // 			var = find_var(var_name, data);
// // 			expand_var(&(*node)->str, &var);
// // 			i++;
// // 		}
// // 	}                                           =>THIS IS DONE BEFORE
// 	// else if (contains_two((*node)->str, '\''))
// 	// {
// 	// 		trim_quotes(&(*node)->str, '\'');
// 	// }
// 	// else
// 	// {
// 		while ((var_name = identify_var((*node)->str, data)) != NULL || i < 5)
// 		{
// 			var = find_var(var_name, data);
// 			expand_var(&(*node)->str, &var);
// 			i++;
// 		}
// 	// }
// }	

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