
#include "../../include/expander.h"
#include "../../include/node.h"
#include "../../include/parser.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

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
	set_node_str(cmd_var, token);
	if (!add_child_node(new_cmd, cmd_var))
		return (NULL);
	return (new_cmd);
}

/**
 * @brief Links the root nodes
 *
 * This function iterates through the root nodes and links them by.

	* The linking is done based on the presence of next siblings: master_node->root_nodes[i
	+ 1]
 * and the existence of the next root node in the array.
 *

	* @param master_node Pointer to the master node structure containing information about the tree.
 *
 * @note The linking is performed using the add_sibling_node function.
 *       The last root node's next_sibling is set to NULL after linking.
 */
void	link_root_nodes(struct node_type_master *master_node)
{
	int i;

	i = 0;
	while (i < master_node->nbr_root_nodes)
	{
		if ((master_node->root_nodes[i]->next_sibling == NULL)
			&& (master_node->root_nodes[i + 1]))
			add_sibling_node(master_node->root_nodes[i],
				master_node->root_nodes[i + 1]);
		i++;
	}
	master_node->root_nodes[master_node->nbr_root_nodes
		- 1]->next_sibling = NULL;
}


/**
 * @brief Adds a new command node to the list of command nodes.
 *
 * @param cmd Pointer to the head of the list of command nodes.
 * @param current_cmd Pointer to the current command nosde in the list.
 * @param new_cmd Pointer to the new command node to add to the list.
 *
 * @return 1 if the command node was successfully added to the list,
	0 otherwise.
 *
* This function adds a new command node to the list of command nodes. If the list is empty,
 * the new command node becomes the head of the list. If the list is not empty,
	the new command  node is added to the end of the list.
 */
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