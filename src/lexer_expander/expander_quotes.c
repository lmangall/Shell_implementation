/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:13:46 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 15:03:32 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/lexer.h"
#include "../../include/main.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <stddef.h>
#include <unistd.h>

// use an exit function
char	*erase_outside_quotes(const char *str)
{
	int		j;
	int		flag;
	char	*new_str;

	j = 0;
	flag = 0;
	new_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	while (*str != '\0')
	{
		if (*str == '\'' && (flag == 0 || flag == 1))
		{
			flag = 1;
			str++;
		}
		else if (*str == '\"' && (flag == 0 || flag == 2))
		{
			flag = 2;
			str++;
		}
		new_str[j] = *str;
		str++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

const char	*find_first_quotes(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			return (&str[i]);
		i++;
	}
	return (NULL);
}

const char	*find_last_quotes(const char *str)
{
	int	i;

	i = ft_strlen(str);
	while (i != 0)
	{
		i--;
		if (str[i] == '\"' || str[i] == '\'')
			return (&str[i]);
	}
	return (NULL);
}

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
