/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:11:09 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/03 23:01:56 by lmangall         ###   ########.fr       */
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

void replace_form_feed_with_spaces(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\f')
            str[i] = ' ';
        i++;
    }
}

char	**put_space_back(char **tokens)
{
	int i = 0;

	while (tokens[i] != NULL)
	{
		if (contains_two(tokens[i], '\"') || contains_two(tokens[i], '\''))
			replace_form_feed_with_spaces(tokens[i]);
		i++;
	}
	return (tokens);
}

char *check_quotes_replace_ff(char *line)
{
    int i = 0;

    while (line[i] != '\0')
    {
        if (line[i] == '\'' || line[i] == '\"')
        {
            char quote = line[i];
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
    int num_tokens = 0;

    while (tokens[num_tokens] != NULL)
        num_tokens++;

    // Allocate memory for the array of pointers to char
    // new_tokens = (char **)malloc((num_tokens + 1) * sizeof(char *));
    new_tokens = calloc((num_tokens + 1), sizeof(char *));
    if (new_tokens == NULL) 
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    i = 0;
    while (tokens[i] != NULL)
    {
        int len = strlen(tokens[i]);
        new_tokens[i] = (char *)malloc((len + 1) * sizeof(char));
        if (new_tokens[i] == NULL)
        {
            perror("Memory allocation failed in erase_quote");
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

//If the quotes are single and I have a VAR I should just return


// CHECK IF THE ERASE QUOTES IS WORKING PROPERLY
char	**lexer(char *line)
{
	char	**tokens;
	if (!line)
		return (NULL);
	if (contains_two(line, '\"') || contains_two(line, '\''))
		check_quotes_replace_ff(line);
	tokens = ft_split(line, ' ');
	put_space_back(tokens);
	char	**new_tokens = erase_quotes(tokens);
	// print_double_pointer_to_char(tokens);
	return (new_tokens);
    //return(tokens);
}
