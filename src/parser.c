/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:27:44 by lmangall          #+#    #+#             */
/*   Updated: 2023/08/10 12:05:22 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../lib/libft/src/libft.h"
#include <unistd.h>
#include "../include/shell.h"
#include "../include/lexer.h"
#include "../include/node.h"
#include "../include/shell.h"

struct node_s *parse_simple_command(struct token_s *tok)
{
	if(!tok)
		return NULL;
	
	struct node_s *cmd = new_node(NODE_COMMAND);
	if(!cmd)
	{
		free_token(tok);
		return NULL;
	}
	
		while (tok && (tok->text_len != 0 && tok->text != NULL && tok->src != NULL))
	{
		if (tok->text[0] == '\n')
		{
			free_token(tok);
			break;
		}
		struct node_s *word = new_node(NODE_VAR);
		if (!word)
		{
			free_node_tree(cmd);
			free_token(tok);
			break;
		}
		set_node_val_str(word, tok->text);
		add_child_node(cmd, word);
		free_token(tok);
		tok = tokenize(tok->src);
	}
		return cmd;
}