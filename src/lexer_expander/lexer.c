/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:11:09 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 16:16:08 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/lexer.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
#include "../../include/main.h"
#include "../../include/vars.h"
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
		tokens = ft_split(line, ' ');
	}
	else
		tokens = ft_split(line, ' ');
	put_space_back(tokens);
	return (tokens);
}
