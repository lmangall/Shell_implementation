/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:27:44 by lmangall          #+#    #+#             */
/*   Updated: 2023/08/22 16:11:47 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../lib/libft/src/libft.h"
#include <unistd.h>
#include "../include/shell.h"
#include "../include/lexer.h"
#include "../include/node.h"
#include "../include/shell.h"


struct node_s *parse_simple_command(char **tokens)
{
	int i = 0;
	
	struct node_s *cmd = new_node(NODE_COMMAND);
	if(!cmd)
		return NULL;
	while(tokens[i] != NULL)
	{
		struct node_s *word = new_node(NODE_VAR);
		if (!word)
			return NULL;
		set_node_str(word, tokens[i]);
		add_child_node(cmd, word);
		i++;
	}
		return cmd;
}