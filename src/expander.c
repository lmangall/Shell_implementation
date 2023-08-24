/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:14:51 by lmangall          #+#    #+#             */
/*   Updated: 2023/08/24 20:13:56 by lmangall         ###   ########.fr       */
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


static int replace_var(struct node_s *node, char *new_value)
{
	ft_memcpy(node->str, new_value, ft_strlen(new_value));
	return (0);
}

struct node_s *contains_dollar(struct node_s *node)
{
		if (node->str[0] == '$')
			return (node);
	return (NULL);
}

void expansion(struct node_s *node, t_data *data)
{
	int	i;

	i = 0;
    struct node_s *dollar_node = contains_dollar(node);
    if (dollar_node)
    {
        // printf("dollar_node->str: %s\n", dollar_node->str);
		// printf("\033[0;32mdata->num_vars = %d\033[0m\n", data->num_vars);
	    while(i <= data->num_vars)
        {
			//prints in green each var name	
   			// printf("\033[0;32mdata->vars_container[%d].name: %s\033[0m\n", i, data->vars_container[i].name);
		    if (ft_strcmp(dollar_node->str + 1, data->vars_container[i].name) == 0)
                replace_var(node, data->vars_container[i].value);
        i++;
		}
    }
}
