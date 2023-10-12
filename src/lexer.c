/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:11:09 by lmangall          #+#    #+#             */
/*   Updated: 2023/10/12 18:20:51 by lmangall         ###   ########.fr       */
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

void	replaceform_feed_with_spaces(char *str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '\f')
			str[i] = ' ';
	}
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

//check for single or double quotes
//calls replaceSpacesWithFormFeed for what is inside the quotes 
char *check_quotes_replace_ff(char *line)
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
    while (strArray[i] != NULL)
        i++;
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

char **erase_quotes(char **tokens)
{
    int i = 0;
    char **new_tokens;

    // Count the number of tokens
    int num_tokens = 0;
    while (tokens[num_tokens] != NULL)
        num_tokens++;

    // Allocate memory for the array of pointers to char
    new_tokens = (char **)malloc((num_tokens + 1) * sizeof(char *));
    if (new_tokens == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    i = 0;
    while (tokens[i] != NULL)
    {
        int len = strlen(tokens[i]);
        new_tokens[i] = (char *)malloc((len + 1) * sizeof(char));
        if (new_tokens[i] == NULL) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        int j = 0, k = 0;
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

    return new_tokens;
}

char	**lexer(char *line)
{
	char	**tokens;

	// printf("line: %s\n", line);
	if (contains_two(line, '\"') || contains_two(line, '\''))
		check_quotes_replace_ff(line);

	if (!line)
		return (NULL);
	tokens = ft_split(line, ' ');
	put_space_back(tokens);
	char	**new_tokens = erase_quotes(tokens);
	// print_double_pointer_to_char(tokens);
	return (new_tokens);
}
