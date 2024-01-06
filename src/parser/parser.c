/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:27:44 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 15:03:32 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
#include "../../include/vars.h"
#include "../include/free.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

/**
 * @brief Parses a simple command.
 *
 * This function takes an array of tokens and a data structure as input,
 * and it generates a one level linked list representing the parsed command.
 * The `expand` function is called to handle variable expansion.
 *
 *There is one empty root node of type "ROOT"
 *There is one one node per word of type "WORD"
 *
 * @param tokens An array of tokens representing the command.
 * @param data A data structure containing information about variables.
 * @return A pointer to the root node of the generated one level linked list
 */
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
	return (root);
}

struct node_type_master	*parse_advanced_command(char **tokens)
{
	int						i;
	struct node_s			*head;
	struct node_s			*current_cmd;
	struct node_s			*new_cmd;
	struct node_s			*word;
	struct node_type_master	*master_node;

	i = 0;
	head = NULL;
	current_cmd = NULL;
	while (tokens[i] != NULL)
	{
		if ((i == 0) || ((is_operator(tokens[i - 1])) && (i > 0)))
		{
			new_cmd = create_root_node(tokens[i]);
			if (!new_cmd)
				return (NULL);
			if (!add_command_node_to_list(&head, &current_cmd, new_cmd))
				return (NULL);
			new_cmd->operator = get_operator(tokens + i);
		}
		else if (is_operator(tokens[i]))
		{
			i++;
			i--;
		}
		else
		{
			// Handle regular words (non-options)
			word = new_node(VAR);
			if (!word)
				return (NULL);
			set_node_str(word, tokens[i]);
			if (!add_child_node(current_cmd, word))
				return (NULL);
		}
		i++;
	}
	master_node = create_master_node(head);
	if (master_node == NULL)
		return (NULL);
	link_root_nodes(master_node);
	return (master_node);
}

int	parse_and_execute(char *line, t_data *data)
{
	char	**tokens;

	tokens = lexer(line);
	// free(line);      ==>> causes a double free when outp.redir is used
	simple_or_advanced(tokens, data);
	free_string_array(tokens);
	return (1);
}
