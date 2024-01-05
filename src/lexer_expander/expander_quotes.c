
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

//use an exit function
char	*erase_outside_quotes(const char *str)
{
	int		j;
	int		flag;
	char	*new_str;

	j = 0;
	flag = 0;
	new_str = (char *)malloc((ft_strlen(str) + 1) * sizeof(char));
	while (*str != '\0')
	{
		if (*str == '\'' && (flag == 0 || flag == 1))
		{
			flag = 1;
			str++;
		}
		else if (*str == '\"' && (flag == 0 || flag == 2))
		{
			flag = 2;
			str++;
		}
		new_str[j] = *str;
		str++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}


/**
 * @brief Find the first occurrence of quotes in the string.
 *
 * @param str The input string to be examined.
 * @return A pointer to the first occurrence of quotes or NULL if not found.
 */
static	const	char	*find_first_quotes(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			return &str[i];
		i++;
	}

	return (NULL);
}

/**
* @brief Find the last occurrence of quotes in the string.
*
* @param str The input string to be examined.
* @return A pointer to the last occurrence of quotes or NULL if not found.
*/
static	const char	*find_last_quotes(const char *str) 
{
	int	i;

	i = ft_strlen(str);
	while (i != 0) 
	{
		i--;

		if (str[i] == '\"' || str[i] == '\'')
			return (&str[i]);
	}

	return (NULL);
}

/**
* @return 2 if there are double quotes
*         3 if there are single quotes
*         5 if different or missing quotes
*/
static int inside_quote(const char *str)
{
	const char *start_quote = find_first_quotes(str);
	const char *end_quote = find_last_quotes(str);

	if (start_quote != NULL && end_quote != NULL && *start_quote == '\"' && *end_quote == '\"')
		return (2); // Double quotes
	if (start_quote != NULL && end_quote != NULL && *start_quote == '\'' && *end_quote == '\'')
		return (3); // Single quotes
	return (5); // Different or missing quotes
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
	int	ret;

	ret = 0;
	if (contains_two((char *)str, '\"') && contains_two((char *)str, '\''))
		ret = inside_quote(str);
	else
	{
		if (contains_two((char *)str, '\"'))
			ret = 1; // Double quotes
		if (contains_two((char *)str, '\''))
			ret = 4; // Single quotes
	}

	return (ret);
}
