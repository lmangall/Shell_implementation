/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:27:44 by lmangall          #+#    #+#             */
/*   Updated: 2023/09/03 19:39:51 by lmangall         ###   ########.fr       */
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
#include "../include/free.h"



//  ->  COMMENTED OUT FOR COMPLEX AST (pipe) TESTING
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

//  ->  ADDED FOR COMPLEX AST (pipe) TESTING
struct node_type_master *parse_advanced_command(char **tokens)
{
    int i = 0;
    struct node_s *cmd = NULL;
    struct node_s *current_cmd = NULL;

    while (tokens[i] != NULL)
    {
        if ((i == 0) || ((strcmp(tokens[i - 1], "|") == 0) && (i > 0)))
        {
            struct node_s *new_cmd = create_new_command_node(tokens[i]);
            if (!new_cmd)
                return NULL;
            if (!add_command_node_to_list(&cmd, &current_cmd, new_cmd))
                return NULL;
        }
        else if (strcmp(tokens[i], "|") == 0)
        {
            struct node_s *pipe_cmd = create_pipe_command_node();
            if (!pipe_cmd)
                return NULL;
            if (!add_command_node_to_list(&cmd, &current_cmd, pipe_cmd))
                return NULL;
        }
        else
        {
            // Handle regular words (non-options)
            struct node_s *word = new_node(NODE_VAR);
            if (!word)
                return NULL;
            set_node_str(word, tokens[i]);
            if (!add_child_node(current_cmd, word))
                return NULL;
        }
        i++;
    }

    struct node_type_master *master_node = create_master_node(cmd);
    if (master_node == NULL)
    {
        return NULL;
    }
   // print_master(master_node);
   link_root_nodes(master_node);
    return master_node;
}


struct node_s *create_pipe_command_node(void)
{
    struct node_s *pipe_cmd = new_node(NODE_COMMAND);
    if (!pipe_cmd)
        return NULL;
    struct node_s *pipe_node = new_node(NODE_SPECIAL);
    if (!pipe_node)
        return NULL;
    set_node_str(pipe_node, "|");
    if (!add_child_node(pipe_cmd, pipe_node))
        return NULL;
    return pipe_cmd;
}


struct node_s *create_new_command_node(char *token)
{
    struct node_s *new_cmd = new_node(NODE_COMMAND);
    if (!new_cmd)
        return NULL;
    struct node_s *cmd_node = new_node(NODE_VAR);
    if (!cmd_node)
        return NULL;
    set_node_str(cmd_node, token);
    if (!add_child_node(new_cmd, cmd_node))
        return NULL;
    return new_cmd;
}


int add_command_node_to_list(struct node_s **cmd, struct node_s **current_cmd, struct node_s *new_cmd)
{
    if (*cmd == NULL)
    {
        *cmd = new_cmd;
        *current_cmd = *cmd;
    }
    else
    {
        (*current_cmd)->next_sibling = new_cmd;
        *current_cmd = (*current_cmd)->next_sibling;
    }
    return 1;
}


struct node_type_master *create_master_node(struct node_s *cmd)
{
    struct node_type_master *master_node = malloc(sizeof(struct node_type_master));
    if (!master_node)
        return NULL;
    master_node->type = NODE_MASTER;
    master_node->str = NULL;
    master_node->nbr_root_nodes = 0;
    master_node->root_nodes = NULL;
    struct node_s *current_cmd = cmd;
    while (current_cmd != NULL)
    {
        master_node->nbr_root_nodes++;
        master_node->root_nodes = realloc(master_node->root_nodes, sizeof(struct node_s *) * master_node->nbr_root_nodes);
        master_node->root_nodes[master_node->nbr_root_nodes - 1] = current_cmd;
        current_cmd = current_cmd->next_sibling;
    }
    return master_node;
}


//write a function that goes through the root nodes (node_command) and prints the first child of each
//the function should use the next_sibling pointer to go through the list of root nodes
static void print_root_nodes(struct node_type_master *master_node)
{
	printf("\n\n\n\n");
	struct node_s *current = master_node->root_nodes[0];
	int i = 0;
	while (current != NULL)
	{
		printf("root_nodes[%d] first_child->str = %s\n", i, current->first_child->str);
		current = current->next_sibling;
		i++;
	}
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
			if (master_node->root_nodes[i]->first_child->next_sibling != NULL)
	            printf("  root_nodes[%d] first_child->next_sibling->str = %s\n", i, master_node->root_nodes[i]->first_child->next_sibling->str);
			else
				printf("the first child has found no sibling (ie there is 1 word, no flags)\n");
            
			printf("\033[0m"); // Reset the color
			printf("\n\n\n");
        }
    }
	print_root_nodes(master_node);
}


void link_root_nodes(struct node_type_master *master_node)
{
    int i = 0;
    while (i < master_node->nbr_root_nodes)
    {
        if ((master_node->root_nodes[i]->next_sibling == NULL) && (master_node->root_nodes[i + 1]))
            add_sibling_node(master_node->root_nodes[i], master_node->root_nodes[i + 1]);
        i++;
    }
    master_node->root_nodes[master_node->nbr_root_nodes - 1]->next_sibling = NULL;
}