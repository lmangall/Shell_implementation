/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:14:51 by lmangall          #+#    #+#             */
/*   Updated: 2023/08/24 15:53:54 by lmangall         ###   ########.fr       */
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
#include "../lib/libft/src/libft.h"


// static int replace_var(struct node_s *node)
// {
// 	ft_memcpy(node->str, get_vars_value(node->str), ft_strlen(get_vars_value(node->str)));
// 	return (0);
// }


// struct node_s *contains_dollar(struct node_s *node)
// {
// 	if (node->type == NODE_COMMAND)
// 	{
// 		if (node->str[0] == '$')
// 			return (node);
// 	}
// 	return (NULL);
// }


// void expansion(struct node_s *node, struct Vars *vars_container)
// {
// 	struct node_s *dollar_node;
// 	dollar_node = contains_dollar(node);
// 	if (dollar_node)
// 	{
// 		printf("dollar_node->str: %s\n", dollar_node->str);
// 		while(node)
// 		{
// 			if (node->type == NODE_COMMAND)
// 			{
// 				if(dollar_node->str == vars_container->name)
// 				{
// 					replace_var(node);
// 				}
// 			}
// 			node = node->next;
// 		}

		
// 	}
// }
