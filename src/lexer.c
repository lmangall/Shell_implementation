/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:11:09 by lmangall          #+#    #+#             */
/*   Updated: 2023/10/10 19:34:13 by lmangall         ###   ########.fr       */
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

void	replace_spaces_with_form_feed(char *str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
		{
			str[i] = '\f';
		}
	}
}

void	replaceform_feed_with_spaces(char *str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '\f')
		{
			str[i] = ' ';
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
    return line;
}


void print_double_pointer_to_char(char **strArray) {
    int i = 0;
    while (strArray[i] != NULL) {
        printf("\nString %d: %s\n", i, strArray[i]);
        i++;
    }
}

int	contains_two(char *str, char c)
{
	int i = 0;
	int count = 0;

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

char	**put_space_back(char **tokens)
{
	int i = 0;

	while (tokens[i] != NULL)
	{
		if (contains_two(tokens[i], '\"') || contains_two(tokens[i], '\''))
			replaceform_feed_with_spaces(tokens[i]);
		i++;
	}
	return (tokens);
}

char	**lexer(char *line)
{
	char	**tokens;

	// printf("line: %s\n", line);
	check_for_quotes(line);
	// printf("line: %s\n", line);
	
	// go through line and check for
	if (!line)
		return (NULL);
	tokens = ft_split(line, ' ');
	// print_double_pointer_to_char(tokens);
	put_space_back(tokens);
	// print_double_pointer_to_char(tokens);
	return (tokens);
}
