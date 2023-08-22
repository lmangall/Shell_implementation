/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:27:44 by lmangall          #+#    #+#             */
/*   Updated: 2023/08/22 12:04:44 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../lib/libft/src/libft.h"
#include <unistd.h>
#include "../include/shell.h"
#include "../include/lexer.h"
#include "../include/node.h"
#include "../include/shell.h"

struct node_s *parse_simple_command(char *line)
{
	if(!line)
		return NULL;
	
	struct node_s *cmd = new_node(NODE_COMMAND);
	if(!cmd)
	{
		free(line);
		return NULL;
	}
		while (line && (ft_strlen(line) != 0 && line != NULL))
	{
		if (line[0] == '\n')
		{
			free(line);
			break;
		}
		struct node_s *word = new_node(NODE_VAR);
		if (!word)
		{
			free_node_tree(cmd);
			free(line);
			break;
		}
		set_node_str(word, line);
		add_child_node(cmd, word);
		printf("line: %s\n", line);
		free(line);
		struct token_s *tok = tokenize(line);
	}
		return cmd;
}