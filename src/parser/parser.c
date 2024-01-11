/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:27:44 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/11 19:35:48 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/free.h"
#include "../../include/parser.h"
#include "../../include/parser_nodes.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

struct s_node	*parse_simple_command(char **tokens, t_data *data)
{
	int				i;
	struct s_node	*root;
	struct s_node	*var;

	i = 0;
	root = new_node(ROOT);
	if (!root)
		return (NULL);
	while (tokens[i] != NULL)
	{
		var = new_node(VAR);
		if (!var)
			return (NULL);
		var->str = tokens[i];
		(void)data;
		add_child_node(root, var);
		i++;
	}
	return (root);
}

int	parse_and_execute(char *line, t_data *data)
{
	char	**tokens;

	tokens = lexer(line);
	data->tokens = tokens;
	simple_or_advanced(tokens, data);
	return (1);
}
