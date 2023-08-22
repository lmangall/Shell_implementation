/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:27:44 by lmangall          #+#    #+#             */
/*   Updated: 2023/08/22 20:41:51 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../lib/libft/src/libft.h"
#include <unistd.h>
#include "../include/shell.h"
#include "../include/lexer.h"
#include "../include/node.h"
#include "../include/shell.h"
#include "../include/parser.h"


void	init_data(t_data *data)
{
	// data->args = NULL;
	// data->paths = NULL;
	// data->envp = NULL;
	// data->pwd = NULL;

	data->paths = getenv("PATHS");
	// data->envp = getenv("ENV");

}

void	syntax_check(char **tokens)
{
	int i;
	char *var;

	i = 0;
    while (tokens[i] != NULL)
	{
		if (tokens[i][0] == '$')
		{
            printf("$ sign identified in token nbr %i\n", i);
			var = tokens[i];
			// add_to_env(var);
		}
	i++;
	}
}

// void	add_to_env(char *var)
// {
// 	char *var_name;
// 	char *var_value;
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (var[i] != '=')
// 	{
// 		var_name[i] = var[i];
// 		i++;
// 	}
// 	i++;
// 	while (var[i] != '\0')
// 	{
// 		var_value[j] = var[i];
// 		i++;
// 		j++;
// 	}
// 	setenv(var_name, var_value, 0);
// }


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