/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:13:46 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 20:44:10 by lmangall         ###   ########.fr       */
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

void	process_inside_quotes(char *new_str, size_t *j,
			int *flag, char **original_str)
{
	if (**original_str == '\'' && (*flag == 0 || *flag == 1))
	{
		*flag = 1;
		(*original_str)++;
	}
	else if (**original_str == '\"' && (*flag == 0 || *flag == 2))
	{
		*flag = 2;
		(*original_str)++;
	}
	else
	{
		new_str[(*j)++] = **original_str;
		(*original_str)++;
	}
}

void	erase_outside_quotes(char **str)
{
	size_t	j;
	int		flag;
	char	*new_str;
	char	*original_str;

	j = 0;
	flag = 0;
	new_str = (char *)malloc((strlen(*str) + 1) * sizeof(char));
	if (new_str == NULL)
		return ;
	original_str = *str;
	while (*original_str != '\0')
	{
		process_inside_quotes(new_str, &j, &flag, &original_str);
	}
	new_str[j] = '\0';
	free(*str);
	*str = new_str;
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
