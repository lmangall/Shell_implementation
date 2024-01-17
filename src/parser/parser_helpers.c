/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:58:08 by ohoro             #+#    #+#             */
/*   Updated: 2024/01/17 16:01:25 by ohoro            ###   ########.fr       */
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

struct s_node	*create_new_command(char **tokens, int i, struct s_node **head,
		struct s_node **current_cmd)
{
	struct s_node	*new_cmd;

	new_cmd = create_root_node(tokens[i]);
	if (!new_cmd)
		return (NULL);
	if (!add_command_node_to_list(head, current_cmd, new_cmd))
		return (NULL);
	new_cmd->operator = get_operator(tokens + i);
	return (new_cmd);
}

struct s_node	*handle_regular_word(char **tokens, int i,
		struct s_node *current_cmd)
{
	struct s_node	*word;

	word = new_node(VAR);
	if (!word)
		return (NULL);
	word->str = ft_strdup(tokens[i]);
	if (!add_child_node(current_cmd, word))
		return (NULL);
	return (word);
}
