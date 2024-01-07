/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:11:09 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/07 18:22:25 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/lexer.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
#include "../../include/main.h"
#include "../../include/vars.h"
#include "../../include/DEV.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

char	**lexer(char *line)
{
	char	**tokens;

	tokens = NULL;
	if (!line)
		return (NULL);
	if (contains_two(line, '\"') || contains_two(line, '\''))
	{
		check_quotes_replace_ff(line);
		char	*line_without_quotes;
		line_without_quotes = erase_outside_quotes(line);
		line = ft_strdup(line_without_quotes);
		free(line_without_quotes);
	}
	tokens = ft_split(line, ' ');
	put_space_back(tokens);
	return (tokens);
}
