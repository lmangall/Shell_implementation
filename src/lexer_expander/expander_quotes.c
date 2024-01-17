/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:13:46 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 16:26:02 by ohoro            ###   ########.fr       */
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
		if (*original_str == '\'' && (flag == 0 || flag == 1))
		{
			flag = 1;
			original_str++;
			continue ;
		}
		else if (*original_str == '\"' && (flag == 0 || flag == 2))
		{
			flag = 2;
			original_str++;
			continue ;
		}
		new_str[j] = *original_str;
		original_str++;
		j++;
	}
	new_str[j] = '\0';
	free(*str);
	*str = new_str;
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
