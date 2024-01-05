
#include "../../include/expander.h"
#include "../../include/fcntl.h"
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