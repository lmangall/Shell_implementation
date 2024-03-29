/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:14:03 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 15:49:26 by ohoro            ###   ########.fr       */
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

void	replace_form_feed_with_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\f')
			str[i] = ' ';
		i++;
	}
}

void	put_space_back(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		replace_form_feed_with_spaces(tokens[i]);
		i++;
	}
}
/**
 * @brief Checks for single and double quotes in a string
 * and replaces spaces within quotes with form feed characters.
 *
 * @note The input string is modified in-place,
 * and the function returns a pointer to the same string.
 */

void	check_quotes_replace_ff(char *line)
{
	int		i;
	char	quote;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			quote = line[i];
			i++;
			while (line[i] != quote && line[i] != '\0')
			{
				if (line[i] == ' ')
					line[i] = '\f';
				i++;
			}
			if (line[i] == quote)
				i++;
		}
		else
		{
			i++;
		}
	}
}

void	replace_space_by_ff(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			str[i] = '\f';
		i++;
	}
}
