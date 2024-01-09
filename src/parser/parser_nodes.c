/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:21:03 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/09 10:26:55 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

// static void *my_realloc(void *ptr, size_t size)
// {
// 	void *reptr;

// 	if (ptr == NULL)
// 		return (malloc(size));
// 	reptr = malloc(size);
// 	if (reptr)
// 		ft_memcpy(reptr, ptr, size);
// 	if (ptr)
// 		free(ptr);
// 	return (reptr);
// }

struct node_s	*create_root_node(char *token)
{
	struct node_s	*new_cmd;
	struct node_s	*cmd_var;

	new_cmd = new_node(ROOT);
	if (!new_cmd)
		return (NULL);
	cmd_var = new_node(VAR);
	if (!cmd_var)
		return (NULL);
	cmd_var->str = token;
	// set_node_str(cmd_var, token);
	if (!add_child_node(new_cmd, cmd_var))
		return (NULL);
	return (new_cmd);
}

void	link_root_nodes(struct node_type_master *master_node)
{
	int	i;

	i = 0;
	while (i < master_node->nbr_root_nodes)
	{
		if ((master_node->root_nodes[i]->next_sibling == NULL)
			&& (master_node->root_nodes[i]))
			add_sibling_node(master_node->root_nodes[i],
				master_node->root_nodes[i]);
		i++;
	}
	master_node->root_nodes[master_node->nbr_root_nodes
		- 1]->next_sibling = NULL;
}

int	add_command_node_to_list(struct node_s **cmd, struct node_s **current_cmd,
		struct node_s *new_cmd)
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

struct node_type_master	*create_master_node(struct node_s *cmd)
{
	struct node_type_master	*master_node;
	struct node_s			*current_cmd;

	master_node = malloc(sizeof(struct node_type_master));
printf("\034[0;31m" "create_master_node, pointer created= %p\n" "\033[0m", master_node);
	if (!master_node)
		return (NULL);
	master_node->type = MASTER;
	master_node->str = NULL;
	master_node->nbr_root_nodes = 0;
	master_node->root_nodes = NULL;
	current_cmd = cmd;
	while (current_cmd != NULL)
	{
		master_node->nbr_root_nodes++;
		master_node->root_nodes = realloc(master_node->root_nodes,
				sizeof(struct node_s *) * master_node->nbr_root_nodes);
		master_node->root_nodes[master_node->nbr_root_nodes - 1] = current_cmd;
		current_cmd = current_cmd->next_sibling;
	}
	return (master_node);
}
