/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:11:09 by lmangall          #+#    #+#             */
/*   Updated: 2023/10/09 20:37:57 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/shell.h"
#include "../lib/libft/src/libft.h"
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	replaceSpacesWithFormFeed(char *str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
		{
			str[i] = 'X'; // Replace space with form feed   \f
		}
	}
}

void	replaceFormFeedWithSpaces(char *str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == 'X')
		{
			str[i] = ' '; // Replace form feed with space     \f
		}
	}
}

//check for single or double quotes
//calls replaceSpacesWithFormFeed for what is inside the quotes 
char *check_for_quotes(char *line)
{
    int i = 0;

    while (line[i] != '\0')
    {
        if (line[i] == '\'' || line[i] == '\"')
        {
            char quote = line[i];  // Store the quote character
            i++;
            while (line[i] != quote && line[i] != '\0')
            {
                if (line[i] == ' ')
                    line[i] = 'X'; // Replace space with a placeholder ('X')
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
    return line;
}


char	**lexer(char *line)
{
	char	**tokens;

	printf("line: %s\n", line);
	check_for_quotes(line);
	printf("line: %s\n", line);
	replaceFormFeedWithSpaces(line);
	printf("line: %s\n", line);
	
	// go through line and check for
	if (!line)
		return (NULL);
	tokens = ft_split(line, ' ');
	return (tokens);
}
