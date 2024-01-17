/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:21:03 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 15:47:48 by ohoro            ###   ########.fr       */
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
	{
		free(new_cmd);
		return (NULL);
	}
	cmd_var->str = ft_strdup(token);
	if (!cmd_var->str)
	{
		free(new_cmd);
		free(cmd_var);
		return (NULL);
	}
	if (!add_child_node(new_cmd, cmd_var))
	{
		free(new_cmd);
		free(cmd_var);
	}
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
