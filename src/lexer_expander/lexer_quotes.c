
#include "../../include/expander.h"
#include "../../include/lexer.h"
#include "../../include/node.h"
#include "../../include/parser.h"
#include "../../include/shell.h"
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
		if (contains_two(tokens[i], '\"') || contains_two(tokens[i], '\''))
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

char	**erase_quotes(char **tokens)
{
	int		i;
	char	**new_tokens;
	int		num_tokens;
	int		len;
	int		j;
    int     k;
    
	i = 0;
	j = 0;
    k = 0;
	num_tokens = 0;
	while (tokens[num_tokens] != NULL)
		num_tokens++;
	// Allocate memory for the array of pointers to char
	// new_tokens = (char **)malloc((num_tokens + 1) * sizeof(char *));
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
		j = 0, k = 0;
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
