/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:21:23 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 17:21:26 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vars.h"
#include "../../include/expander.h"
#include "../../include/parser_nodes.h"
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
