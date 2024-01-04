
#include "../../include/fcntl.h"
#include "../../include/vars.h"
#include "../../include/expander.h"
#include "../../include/node.h"
#include "../../include/parser.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

int	is_operator(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (1);
	if (ft_strcmp(str, ">") == 0)
		return (1);
	if (ft_strcmp(str, ">>") == 0)
		return (1);
	if (ft_strcmp(str, "<") == 0)
		return (1);
	if (ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}

/**
 * @brief Looks for the first operator
 * in the array of tokens and returns the operator type.
 *

	* This function iterates over the array of tokens and determines the operator type
 * based on the token values. The following operators are supported:
 * - PIPE: "|"
 * - RDR_OUT_REPLACE: ">"
 * - RDR_OUT_APPEND: ">>"
 * - RDR_INPUT: "<"
 * - RDR_INPUT_UNTIL: "<<"
 *
 * @param token An array of tokens to search for operators.
 * @return The operator type, or NONE if no operator is found.
 */
t_operator	get_operator(char **token)
{
	int	i;

	i = 0;
	while (token[i] != NULL)
	{
		if (ft_strnstr(token[i], ">>", 2))
			return (RDR_OUT_APPEND);
		if (ft_strnstr(token[i], "<<", 2))
			return (RDR_INPUT_UNTIL);
		if (ft_strnstr(token[i], "|", 1))
			return (PIPE);
		if (ft_strnstr(token[i], ">", 1))
			return (RDR_OUT_REPLACE);
		if (ft_strnstr(token[i], "<", 1))
			return (RDR_INPUT);
		i++;
	}
	return (NONE);
}