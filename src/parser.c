/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:27:44 by lmangall          #+#    #+#             */
/*   Updated: 2023/09/13 20:37:41 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/src/libft.h"
#include <unistd.h>
#include "../include/shell.h"
#include "../include/lexer.h"
#include "../include/node.h"
#include "../include/vars.h"
#include "../include/shell.h"
#include "../include/parser.h"
#include "../include/free.h"
#include "../include/fcntl.h"


//  ->  COMMENTED OUT FOR COMPLEX AST (pipe) TESTING
struct node_s *parse_simple_command(char **tokens)
{
	int i = 0;
	
	struct node_s *cmd = new_node(ROOT);
	if(!cmd)
		return NULL;
	while(tokens[i] != NULL)
	{
		struct node_s *word = new_node(VAR);
		if (!word)
			return NULL;
		set_node_str(word, tokens[i]);
		add_child_node(cmd, word);
		i++;
	}
	return cmd;
}

int is_operator(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return 1;
	if (ft_strcmp(str, ">") == 0)
		return 1;
	if (ft_strcmp(str, ">>") == 0)
		return 1;
	if (ft_strcmp(str, "<") == 0)
		return 1;
	if (ft_strcmp(str, "<<") == 0)
		return 1;
	return 0;
}

/**
 * @brief Looks for the first operator 
 * in the array of tokens and returns the operator type.
 *
 * This function iterates over the array of tokens and determines the operator type
 * based on the token values. The following operators are supported:
 * - PIPE: "|"
 * - RDR_OUT_REPLACE: ">"
 * - RDR_OUT_APPEND: ">>"
 * - RDR_INPUT: "<"
 * - RDR_INPUT_UNTIL: "<<"
 *
 * @param token An array of tokens to search for operators.
 * @return The operator type, or NONE if no operator is found.
 */
t_operator	get_operator(char **token)
{
	int i;

	i = 0;
	while (token[i] != NULL)
	{
		if (ft_strnstr(token[i], ">>", 2))
			return RDR_OUT_APPEND;
		if (ft_strnstr(token[i], "<<", 2))
			return RDR_INPUT_UNTIL;
		if (ft_strnstr(token[i], "|", 1))
			return PIPE;
		if (ft_strnstr(token[i], ">", 1))
			return RDR_OUT_REPLACE;
		if (ft_strnstr(token[i], "<", 1))
			return RDR_INPUT;
		i++;
	}
	return NONE;
}

struct node_type_master *parse_advanced_command(char **tokens)
{
	int i = 0;
	int rdr_input = 0;
	int rdr_output = 0;
	struct node_s *head = NULL;
	struct node_s *current_cmd = NULL;

	while (tokens[i] != NULL)
	{
		if ((i == 0) || ((is_operator(tokens[i - 1])) && (i > 0)))
		{
			struct node_s *new_cmd = create_root_node(tokens[i]);
			if (!new_cmd)
				return NULL;
			if (!add_command_node_to_list(&head, &current_cmd, new_cmd))
				return NULL;
			new_cmd->operator = get_operator(tokens + i);
			//end of this "if" is used for the ->    wc > output.txt < input.txt   
			if(rdr_output == 1 && rdr_input == 1)
			{
				new_cmd->prev_sibling = head;
				new_cmd->operator = RDR_INPUT;//this is getting overwritten	
			}
			if(get_operator(tokens + i) == RDR_OUT_REPLACE)
				rdr_output++;
			if(get_operator(tokens + i) == RDR_INPUT)
				rdr_input++;
		}
		else if (is_operator(tokens[i])) //(strcmp(tokens[i], "|") == 0)
		{
			i++;
			i--;
		}
		else 
		{
			// Handle regular words (non-options)
			struct node_s *word = new_node(VAR);
			if (!word)
				return NULL;
			set_node_str(word, tokens[i]);
			if (!add_child_node(current_cmd, word))
				return NULL;
		}

		i++;
	}
		
		

	struct node_type_master *master_node = create_master_node(head);
	if (master_node == NULL)
	{
		return NULL;
	}
	link_root_nodes(master_node);
	return master_node;
}


// struct node_s *create_pipe_command_node(void)
// {
//     struct node_s *pipe_cmd = new_node(NODE_COMMAND);
//     if (!pipe_cmd)
//         return NULL;
//     struct node_s *pipe_node = new_node(NODE_SPECIAL);
//     if (!pipe_node)
//         return NULL;
//     set_node_str(pipe_node, "|");
//     if (!add_child_node(pipe_cmd, pipe_node)){
//         return NULL;}
// 	pipe_cmd->operator = PIPE;
// 	pipe_node->operator = PIPE;
//     return pipe_cmd;
// }


struct node_s *create_root_node(char *token)
{
	struct node_s *new_cmd = new_node(ROOT);
	if (!new_cmd)
		return NULL;
	struct node_s *cmd_var = new_node(VAR);
	if (!cmd_var)
		return NULL;
	set_node_str(cmd_var, token);
	if (!add_child_node(new_cmd, cmd_var))
		return NULL;
	return new_cmd;
}

/**
 * @brief Adds a new command node to the list of command nodes.
 *
 * @param cmd Pointer to the head of the list of command nodes.
 * @param current_cmd Pointer to the current command node in the list.
 * @param new_cmd Pointer to the new command node to add to the list.
 *
 * @return 1 if the command node was successfully added to the list, 0 otherwise.
 *
 * This function adds a new command node to the list of command nodes. If the list is empty,
 * the new command node becomes the head of the list. If the list is not empty, the new command
 * node is added to the end of the list.
 */
int add_command_node_to_list(struct node_s **cmd, struct node_s **current_cmd, struct node_s *new_cmd)
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
	return 1;
}


struct node_type_master *create_master_node(struct node_s *cmd)
{
	struct node_type_master *master_node = malloc(sizeof(struct node_type_master));
	if (!master_node)
		return NULL;
	master_node->type = MASTER;
	master_node->str = NULL;
	master_node->nbr_root_nodes = 0;
	master_node->root_nodes = NULL;
	struct node_s *current_cmd = cmd;
	while (current_cmd != NULL)
	{
		master_node->nbr_root_nodes++;
		master_node->root_nodes = realloc(master_node->root_nodes, sizeof(struct node_s *) * master_node->nbr_root_nodes);
		master_node->root_nodes[master_node->nbr_root_nodes - 1] = current_cmd;
		current_cmd = current_cmd->next_sibling;
	}
	return master_node;
}

void link_root_nodes(struct node_type_master *master_node)
{
	int i = 0;
	while (i < master_node->nbr_root_nodes)
	{
		if ((master_node->root_nodes[i]->next_sibling == NULL) && (master_node->root_nodes[i + 1]))
			add_sibling_node(master_node->root_nodes[i], master_node->root_nodes[i + 1]);
		i++;
	}
	master_node->root_nodes[master_node->nbr_root_nodes - 1]->next_sibling = NULL;
}