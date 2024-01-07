/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:27:44 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/07 17:35:11 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/free.h"
#include "../../include/parser.h"
#include "../../include/parser_nodes.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include "../../include/DEV.h"
#include <errno.h>
#include <unistd.h>

struct node_s	*parse_simple_command(char **tokens, t_data *data)
{
	int				i;
	struct node_s	*root;
	struct node_s	*var;

	i = 0;
	root = new_node(ROOT); // THIS IS MALLOCED AND SHOULD BE FREED
	if (!root)
		return (NULL);
	while (tokens[i] != NULL)
	{
		var = new_node(VAR);
		if (!var)
			return (NULL);
		set_node_str(var, tokens[i]);
		(void)data;
		add_child_node(root, var);
		i++;
	}
	free_string_array(tokens);
	return (root);
}

int	parse_and_execute(char *line, t_data *data)
{
	char	**tokens;

	tokens = lexer(line);
	// free(line);      ==>> causes a double free when outp.redir is used
	simple_or_advanced(tokens, data);
	// free_string_array(tokens);//==>is this happening
	return (1);
}
