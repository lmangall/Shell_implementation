/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:21:03 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/16 12:30:16 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

struct s_node	*create_root_node(char *token)
{
	struct s_node	*new_cmd;
	struct s_node	*cmd_var;

	new_cmd = new_node(ROOT);
	if (!new_cmd)
		return (NULL);
	cmd_var = new_node(VAR);
	if (!cmd_var)
		return (NULL);
	cmd_var->str = ft_strdup(token);
	if (!add_child_node(new_cmd, cmd_var))
		return (NULL);
	return (new_cmd);
}

int	add_command_node_to_list(struct s_node **cmd, struct s_node **current_cmd,
		struct s_node *new_cmd)
{
	if (*cmd == NULL)
	{
		*cmd = new_cmd;
		*current_cmd = *cmd;
	}
	else
	{
		(*current_cmd)->next_sibling = new_cmd;
		*current_cmd = (*current_cmd)->next_sibling;
	}
	return (1);
}
