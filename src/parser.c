/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:27:44 by lmangall          #+#    #+#             */
/*   Updated: 2023/09/02 15:44:59 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/src/libft.h"
#include <unistd.h>
#include "../include/shell.h"
#include "../include/lexer.h"
#include "../include/node.h"
#include "../include/vars.h"
#include "../include/shell.h"
#include "../include/parser.h"


//  ->  COMMENTED OUT FOR COMPLEX AST (pipe) TESTING
// struct node_s *parse_simple_command(char **tokens)
// {
// 	int i = 0;
	
// 	struct node_s *cmd = new_node(NODE_COMMAND);
// 	if(!cmd)
// 		return NULL;
// 	while(tokens[i] != NULL)
// 	{
// 		struct node_s *word = new_node(NODE_VAR);
// 		if (!word)
// 			return NULL;
// 		set_node_str(word, tokens[i]);
// 		add_child_node(cmd, word);
// 		i++;
// 	}
// 	return cmd;
// }

//  ->  ADDED FOR COMPLEX AST (pipe) TESTING
struct node_type_master *parse_simple_command(char **tokens)
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
	
	struct node_type_master *master_node = search_special(cmd);
	return master_node;
	
}


struct node_type_master *search_special(struct node_s *cmd)
{
	struct node_s *current = cmd->first_child;
	
	while(current->next_sibling)
	{
		if (ft_strcmp(current->str, "|") == 0)
		{
//////////creating the master node
		struct node_type_master *master_node = malloc(sizeof(struct node_type_master));
		if(!master_node)
			printf("malloc failed\n");		
		master_node->root_nodes = malloc(sizeof(struct node_s *) * 3);

//////////creating the root for the pipe
			struct node_s *root_pipe = new_node(NODE_COMMAND);
			if(!root_pipe)
				printf("malloc failed\n");

			root_pipe->first_child = current;
			current->type = NODE_SPECIAL;

//////////creating the root for "wc"
			struct node_s *root_cmd = new_node(NODE_COMMAND);
			if(!root_cmd)
				printf("malloc failed\n");
			root_cmd->first_child = current->next_sibling;

//////// assigning the pipe and "wc" to the master node
			master_node->root_nodes[0] = cmd;	
			master_node->root_nodes[1] = root_pipe;	
			master_node->root_nodes[2] = root_cmd;	
			master_node->root_nodes[3] = NULL;	
			master_node->nbr_root_nodes	= 3;

			/// CAREFULL SEGFAULTING BELOW
			//  master_node->root_nodes[0]->first_child->next_sibling = NULL;
			//  master_node->root_nodes[1]->first_child->next_sibling = NULL;

// print_master(master_node);                   => to print the complex AST
			return (master_node);
		}
		current = current->next_sibling;

	}

	return (0);

}


void print_master(struct node_type_master *master_node)
{
    if (master_node == NULL)
    {
        printf("Master node is NULL\n");
        return;
    }

    printf("\033[1;33m"); // Set the color to orange
    printf("Master Node Type: NODE_MASTER\n");
    printf("Number of Root Nodes: %d\n", master_node->nbr_root_nodes);
    printf("\033[0m"); // Reset the color

    for (int i = 0; i < master_node->nbr_root_nodes; i++)
    {
        printf("\033[1;33m"); // Set the color to orange
        printf("Node %d:\n", i);
        printf("\033[0m"); // Reset the color
        if (master_node->root_nodes[i] == NULL)
        {
            printf("  Root Node is NULL\n");
        }
        else
        {
            printf("  Root Node Type: %d\n", master_node->root_nodes[i]->type);
            printf("  Root Node String: %s\n", master_node->root_nodes[i]->str);
            printf("\033[1;33m"); // Set the color to orange
            printf("  Root Node FC Type: %d\n", master_node->root_nodes[i]->first_child->type);
            printf("  root_nodes[%d] first_child->str = %s\n", i, master_node->root_nodes[i]->first_child->str);
            printf("\033[0m"); // Reset the color
        }
    }
}
