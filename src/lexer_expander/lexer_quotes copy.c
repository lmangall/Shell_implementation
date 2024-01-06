/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:14:03 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 15:36:47 by lmangall         ###   ########.fr       */
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

char	**allocate_memory_for_tokens(int num_tokens)
{
	char	**new_tokens;

	new_tokens = ft_calloc((num_tokens + 1), sizeof(char *));
	if (new_tokens == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	return (new_tokens);
}

char	*copy_token_without_quotes(const char *source)
{
	int		len;
	char	*new_token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(source);
	new_token = (char *)malloc((len + 1) * sizeof(char));
	if (new_token == NULL)
	{
		perror("Memory allocation failed in copy_token_without_quotes");
		exit(EXIT_FAILURE);
	}
	while (source[i] != '\0')
	{
		if (source[i] != '\"' && source[i] != '\'')
		{
			new_token[j] = source[i];
			j++;
		}
		i++;
	}
	new_token[j] = '\0';
	return (new_token);
}

char	**erase_quotes_from_tokens(char **tokens)
{
	int		num_tokens;
	char	**new_tokens;
	int		i;

	num_tokens = 0;
	while (tokens[num_tokens] != NULL)
	{
		num_tokens++;
	}
	new_tokens = allocate_memory_for_tokens(num_tokens);
	i = 0;
	while (tokens[i] != NULL)
	{
		new_tokens[i] = copy_token_without_quotes(tokens[i]);
		i++;
	}
	new_tokens[num_tokens] = NULL;
	return (new_tokens);
}

/*
char	**erase_quotes(char **tokens)
{
	int		i;
	char	**new_tokens;
	int		num_tokens;
	int		len;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	num_tokens = 0;
	while (tokens[num_tokens] != NULL)
		num_tokens++;
	new_tokens = ft_calloc((num_tokens + 1), sizeof(char *));
	if (new_tokens == NULL)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (tokens[i] != NULL)
	{
		len = ft_strlen(tokens[i]);
		new_tokens[i] = (char *)malloc((len + 1) * sizeof(char));
		if (new_tokens[i] == NULL)
		{
			perror("Memory allocation failed in erase_quote");
			exit(EXIT_FAILURE);
		}
		j = 0,
		k = 0;
		while (tokens[i][j] != '\0')
		{
			if (tokens[i][j] != '\"' && tokens[i][j] != '\'')
			{
				new_tokens[i][k] = tokens[i][j];
				k++;
			}
			j++;
		}
		new_tokens[i][k] = '\0';
		i++;
	}
	new_tokens[num_tokens] = NULL;
	return (new_tokens);
}
*/