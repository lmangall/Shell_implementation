/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:11:09 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 13:32:09 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/lexer.h"
#include "../../include/node.h"
#include "../../include/parser.h"
#include "../../include/main.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

/**
 * @brief Tokenizes a given string based on spaces.
 *
 * This function takes a string as input and tokenizes it into an array of strings
 * based on space characters. It also handles cases where the input string contains
 * double or single quotes by checking and replacing them appropriately.
 *
 * @param line The input string to be tokenized.
 *
 * @return A dynamically allocated array of strings (tokens) representing the
 *         individual words extracted from the input string. The last element
 *         of the array is set to NULL.
 * @retval NULL if the input string is NULL or memory allocation fails.
 *
 * @note The caller is responsible for freeing the memory allocated for the
 *       returned array of tokens when it is no longer needed.
 */
char	**lexer(char *line)
{
	char	**tokens;

	tokens = NULL;
	if (!line)
		return (NULL);
	if (contains_two(line, '\"') || contains_two(line, '\''))
		check_quotes_replace_ff(line);
	tokens = ft_split(line, ' ');
	put_space_back(tokens);
	return (tokens);
}
