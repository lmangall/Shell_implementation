/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:17:26 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 15:31:41 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_NODES_H
# define PARSER_NODES_H

enum			e_node
{
	ROOT,
	VAR,
	SPECIAL,
	MASTER,
};

typedef enum e_operator
{
	NONE,
	RDR_OUT_REPLACE,
	RDR_OUT_APPEND,
	RDR_INPUT,
	RDR_INPUT_UNTIL,
	PIPE
}	t_operator;

struct			s_node
{
	enum e_node			type;
	enum e_operator		operator;
	char				*str;
	int					children;
	struct s_node		*first_child;
	struct s_node		*next_sibling;
	struct s_node		*prev_sibling;
};

struct			s_nodepecial
{
	enum e_node	type;
	char		*str;
};

struct			s_node	*create_root_node(char *token);

/**
 * @brief  creates a new node and sets its type field.
 */
struct			s_node	*new_node(enum e_node type);

/**
 * @brief expands the AST of a simple command by adding a new child node
 *        and incrementing the root node's children field. If the root node
 *        has no children, the new child is assigned to the first_child field
 *        of the root node. Otherwise, the child is appended to the end of the
 *        children's list.
 */
int				add_child_node(struct s_node *parent, struct s_node *child);

/**
 * @brief sets a node's value to the given string. It copies the string to
 *        a newly allocated memory space, then sets the val_type and val.str
 *        fields accordingly.
 */
void			set_s_nodetr(struct s_node *node, char *val);

/**
 * @brief Adds a new sibling node to the list of siblings.
 *
 * @param parent Pointer to the parent node.
 * @param child  Pointer to the new child node.
 *
 * @return 1 if the sibling node was successfully added, 0 otherwise.
 *
 * This function adds a new sibling node to the list of siblings.
 */
int				add_sibling_node(struct s_node *parent, struct s_node *child);

/**
 * @brief Adds a new command node to the list of command nodes.
 *
 * @param cmd          Pointer to the head of the list of command nodes.
 * @param current_cmd  Pointer to the current command node in the list.
 * @param new_cmd      Pointer to the new command node to add to the list.
 *
 * @return 1 if the command node was successfully added, 0 otherwise.
 *
 * This function adds a new command node to the list of command nodes.
 */
int				add_command_node_to_list(struct s_node **cmd,
							struct s_node **current_cmd, 
							struct s_node *new_cmd);

#endif