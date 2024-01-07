/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:14:03 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/07 18:18:30 by lmangall         ###   ########.fr       */
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

int	contains_two(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (count == 2)
		return (1);
	return (0);
}

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

char	**put_space_back(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		// if (contains_two(tokens[i], '\"') || contains_two(tokens[i], '\''))
			replace_form_feed_with_spaces(tokens[i]);
		i++;
	}
	return (tokens);
}

/**
 * @brief Checks for single and double quotes in a string
 * and replaces spaces within quotes with form feed characters.
 *
 * @note The input string is modified in-place,
 * and the function returns a pointer to the same string.
 */
char	*check_quotes_replace_ff(char *line)
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
	return (line);
}
