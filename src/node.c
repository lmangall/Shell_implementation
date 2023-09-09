#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "../include/node.h"
#include "../include/shell.h"
#include "../lib/libft/src/libft.h"
#include "../include/free.h"


t_operator get_operator(char *operator)
{
    t_operator op;

    if (!operator)
        op = NONE;
    else if (ft_strcmp(operator, "|") == 0)
        op = PIPE;
    else if (ft_strcmp(operator, ">>") == 0)
        op = RDR_OUT_APPEND;
    else if (ft_strcmp(operator, ">") == 0)
        op = RDR_OUT_REPLACE;
    else if (ft_strcmp(operator, "<<") == 0)
        op = RDR_INPUT_UNTIL;
    else if (ft_strcmp(operator, "<") == 0)
        op = RDR_INPUT;
    else
        op = NONE;
    free(operator);
    return op;
}


struct node_s *new_node(enum node_type_e type)
{

    struct node_s *node = malloc(sizeof(struct node_s));
    if(!node)
		return NULL;
    
    memset(node, 0, sizeof(struct node_s));
    node->type = type;
    
    return node;
}
int add_child_node(struct node_s *parent, struct node_s *child)
{
    if (parent == NULL || child == NULL)
        return 0;
    if (parent->first_child == NULL)
    {
        parent->first_child = child;
        return 1;
    }
    else
    {
        struct node_s *current_child = parent->first_child;
        while (current_child->next_sibling != NULL)
            current_child = current_child->next_sibling;
        current_child->next_sibling = child;
        return 1;
    }
}

void set_node_str(struct node_s *node, char *val)
{
    if(!val)
		node->str = NULL;
    else
    {
        char *val2 = malloc(strlen(val)+1);    
    	if(!val2)
		    node->str = NULL;
        else
        {
			if(node->str)
				free(node->str);
            strcpy(val2, val);
            node->str = val2;
        }
    }

}void free_node_tree(struct node_s *node)
{
    if(!node)
    {
        return;
    }
    struct node_s *child = node->first_child;
    
    while(child)
    {
        struct node_s *next = child->next_sibling;
        free_node_tree(child);
        child = next;
    }
    free(node);
}

int add_sibling_node(struct node_s *parent, struct node_s *child)
{
    if (parent == NULL || child == NULL)
        return 0;
    if (parent->next_sibling == NULL)
    {
        parent->next_sibling = child;
        return 1;
    }
    return 0;
}