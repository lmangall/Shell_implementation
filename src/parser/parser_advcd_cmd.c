/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_advcd_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:19:36 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/09 10:32:02 by lmangall         ###   ########.fr       */
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

struct node_s	*create_new_command(char **tokens, int i, struct node_s **head,
		struct node_s **current_cmd)
{
	struct node_s	*new_cmd;

	new_cmd = create_root_node(tokens[i]);
	if (!new_cmd)
		return (NULL);
	if (!add_command_node_to_list(head, current_cmd, new_cmd))
		return (NULL);
	new_cmd->operator = get_operator(tokens + i);
	return (new_cmd);
}

void	handle_operator(int *i)
{
	(*i)++;
	(*i)--;
}

struct node_s	*handle_regular_word(char **tokens, int i,
		struct node_s *current_cmd)
{
	struct node_s	*word;

	word = new_node(VAR);
	if (!word)
		return (NULL);
	word->str = tokens[i];
	// set_node_str(word, tokens[i]);
	if (!add_child_node(current_cmd, word))
		return (NULL);
	return (word);
}

struct node_type_master	*create_master_and_link(struct node_s *head)
{
	struct node_type_master	*master_node;

	master_node = create_master_node(head);
	if (master_node == NULL)
		return (NULL);
	link_root_nodes(master_node);
	return (master_node);
}

struct node_type_master	*parse_advanced_command(char **tokens)
{
	int				i;
	struct node_s	*head;
	struct node_s	*current_cmd;

	i = 0;
	head = NULL;
	current_cmd = NULL;
	while (tokens[i] != NULL)
	{
		if ((i == 0) || ((is_operator(tokens[i - 1])) && (i > 0)))
		{
			current_cmd = create_new_command(tokens, i, &head, &current_cmd);
			if (!current_cmd)
				return (NULL);
		}
		else if (is_operator(tokens[i]))
			handle_operator(&i);
		else
		{
			if (!handle_regular_word(tokens, i, current_cmd))
				return (NULL);
		}
		i++;
	}
	return (create_master_and_link(head));
}

// struct node_type_master	*parse_advanced_command(char **tokens)
// {
// 	int						i;
// 	struct node_s			*head;
// 	struct node_s			*current_cmd;
// 	struct node_s			*new_cmd;
// 	struct node_s			*word;
// 	struct node_type_master	*master_node;

// 	i = 0;
// 	head = NULL;
// 	current_cmd = NULL;
// 	while (tokens[i] != NULL)
// 	{
// 		if ((i == 0) || ((is_operator(tokens[i - 1])) && (i > 0)))
// 		{
// 			new_cmd = create_root_node(tokens[i]);
// 			if (!new_cmd)
// 				return (NULL);
// 			if (!add_command_node_to_list(&head, &current_cmd, new_cmd))
// 				return (NULL);
// 			new_cmd->operator = get_operator(tokens + i);
// 		}
// 		else if (is_operator(tokens[i]))
// 		{
// 			i++;
// 			i--;
// 		}
// 		else
// 		{
// 			// Handle regular words (non-options)
// 			word = new_node(VAR);
// 			if (!word)
// 				return (NULL);
// 			set_node_str(word, tokens[i]);
// 			if (!add_child_node(current_cmd, word))
// 				return (NULL);
// 		}
// 		i++;
// 	}
// 	master_node = create_master_node(head);
// 	if (master_node == NULL)
// 		return (NULL);
// 	link_root_nodes(master_node);
// 	return (master_node);
// }
