/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_advcd_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:19:36 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 16:54:16 by ohoro            ###   ########.fr       */
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

static void	set_head_and_current_cmd(struct s_node **head,
	struct s_node **current_cmd)
{
	*head = NULL;
	*current_cmd = NULL;
}

void	handle_operator(int *i)
{
	(*i)++;
	(*i)--;
}

struct s_node	*parse_advanced_command(char **tokens)
{
	int				i;
	struct s_node	*head;
	struct s_node	*current_cmd;

	i = 0;
	set_head_and_current_cmd(&head, &current_cmd);
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
	free_string_array(tokens);
	return (head);
}
