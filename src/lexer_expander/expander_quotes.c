
#include "../../include/expander.h"
#include "../../include/lexer.h"
#include "../../include/node.h"
#include "../../include/parser.h"
#include "../../include/shell.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <stddef.h>
#include <unistd.h>

char	*erase_outside_quotes(const char *str)
{
	int		i;
	int		flag;
	char	*new_str;

	i = 0;
	flag = 0;
	new_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	if (new_str == NULL)
	{
		perror("Memory allocation failed in erase_quotes");
		exit(EXIT_FAILURE);
	}
	int j = 0; // Use a separate index for new_str
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && (flag == 0 || flag == 1))
		{
			flag = 1;
			i++; // Remove this line to avoid skipping the first character
		}
		else if (str[i] == '\"' && (flag == 0 || flag == 2))
		{
			flag = 2;
			i++; // Remove this line to avoid skipping the first character
		}
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

/**
 * @brief Determine the presence and types of quotes in a given string.
 *

	* This function analyzes a string and categorizes the occurrence and types of quotes.
 *
 * @param str The input string to be examined.
 *
 * @return 0 if there are no quotes										EXPAND
 * @return 1 if there are double quotes (not inside single quotes)		EXPAND
 * @return 2 if there are single quotes inside double quotes			EXPAND
 * @return 3 if there are double quotes inside single quotes			DONT_EXPAND

	* @return 4 if there are single quotes									DONT_EXPAND
 */
int	quote_type(const char *str)
{
	int	doubleq;
	int	single;

	doubleq = 0;
	single = 0;
	while (*str)
	{
		if (*str == '\"')
		{
			// Check for double quotes not inside single quotes
			if (!single && ft_strrchr(str + 1, '\"') != NULL)
				doubleq = 1;
			// Check for double quotes inside single quotes
			else if (single && ft_strrchr(str + 1, '\"') != NULL
				&& ft_strchr(str + 1, '\'') != NULL)
				return (3); // Return 3 for double quotes inside single quotes
		}
		else if (*str == '\'')
		{
			// Check for single quotes not inside double quotes
			if (!doubleq && ft_strrchr(str + 1, '\'') != NULL)
				single = 1;
			// Check for single quotes inside double quotes
			else if (doubleq && ft_strrchr(str + 1, '\'') != NULL
					&& ft_strchr(str + 1, '\"') != NULL)
				return (2);
			else
				return (4);
		}
		++str;
	}
	if (doubleq)
		return (1);
	else if (single)
		return (4);
	else
		return (0);
}
