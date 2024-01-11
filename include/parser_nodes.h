/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:17:26 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/11 13:17:55 by lmangall         ###   ########.fr       */
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

typedef enum	e_operator
{
	NONE,
	RDR_OUT_REPLACE,
	RDR_OUT_APPEND,
	RDR_INPUT,
	RDR_INPUT_UNTIL,
	PIPE,
}						t_operator;

struct			node_s
{
	enum e_node	type;
	enum e_operator		operator;
	char				*str;
	int					children;
	struct node_s		*first_child;
	struct node_s		*next_sibling;
	struct node_s		*prev_sibling;
};

struct			node_type_master
{
	enum e_node	type;
	char				*str;
	int					nbr_root_nodes;
	struct node_s		**root_nodes;
};

struct			node_special
{
	enum e_node type;
	char *str;
};

struct			node_s	*create_root_node(char *token);

/**
 * @brief  creates a new node and sets its type field.
 */
struct			node_s	*new_node(enum e_node type);

/**
 * @brief expands the AST of a simple command by adding a new child node
 *        and incrementing the root node's children field. If the root node
 *        has no children, the new child is assigned to the first_child field
 *        of the root node. Otherwise, the child is appended to the end of the
 *        children's list.
 */
int				add_child_node(struct node_s *parent, struct node_s *child);

/**
 * @brief frees the memory allocated for a node and its descendants.
 */
void			free_node_tree(struct node_s *node);

/**
 * @brief sets a node's value to the given string. It copies the string to
 *        a newly allocated memory space, then sets the val_type and val.str
 *        fields accordingly.
 */
void			set_node_str(struct node_s *node, char *val);

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
int				add_sibling_node(struct node_s *parent, struct node_s *child);

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
int				add_command_node_to_list(struct node_s **cmd,
							struct node_s **current_cmd, 
							struct node_s *new_cmd);


#endif