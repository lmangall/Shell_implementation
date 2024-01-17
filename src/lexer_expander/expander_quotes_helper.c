/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quotes_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 19:29:42 by ohoro             #+#    #+#             */
/*   Updated: 2024/01/17 19:34:34 by ohoro            ###   ########.fr       */
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
