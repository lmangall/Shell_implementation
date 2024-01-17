/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quotes copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 00:14:03 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 15:50:42 by ohoro            ###   ########.fr       */
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
