/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:14:51 by lmangall          #+#    #+#             */
/*   Updated: 2023/08/29 20:52:31 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <expander.h>
#include "../include/node.h"
#include "../include/shell.h"
#include "../include/minishell.h"
#include "../include/parser.h"
#include "../include/expander.h"
#include "../lib/libft/src/libft.h"

struct node_s *contains_dollar(struct node_s *node)
{
		if (node->str[0] == '$')
			return (node);
	return (NULL);
}

void expansion_substitution(struct node_s *node, t_data *data)
{
	int	i;

	i = 0;
    struct node_s *dollar_node = contains_dollar(node);
    if (dollar_node)
    {
	    while(i <= data->num_vars)
        {
		    if (ft_strcmp(dollar_node->str + 1, data->vars_container[i].name) == 0)
                set_node_str(node, data->vars_container[i].value);
        i++;
		}
    }
}

char *get_var_name(char *str)
	{
		int i;
		char *var_name;

		i = 0;
		while (str[i] != '=')
		{
			var_name[i] = str[i];
			i++;
		}
		var_name[i] = '\0';
		return (var_name);
	}

void expansion_set_var(struct node_s *node, t_data *data)
{
        char *var_name = get_var_name(node->str);
        set_var(data, var_name, node->str + strlen(var_name) + 1);
}