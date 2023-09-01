/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:27:44 by lmangall          #+#    #+#             */
/*   Updated: 2023/09/01 18:32:25 by lmangall         ###   ########.fr       */
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

//THIS FUNCTION IS MOR OR LESS DOUBLE
int find_equal_sign(char *str) 
{
	int i;
	i = 0;
	while (str[i] != '\0') 
	{
		if (str[i] == '=')
			return(i);
		i++;
	}
	return(-1);
}




void init_vars(t_data *data) {
	extern char **environ; // Assumption: extern declaration for the environment variables
    int i = 0;
    int j;
    int equal_sign;

    data->num_vars = 0;
    data->num_exported_vars = 0;

    while (environ[i] != NULL && i < MAX_VARS) {
        equal_sign = find_equal_sign(environ[i]);

        if (equal_sign != -1) {
            j = 0;

            while (j < equal_sign && (size_t)j < sizeof(data->vars_container[i].name) - 1) {
                data->vars_container[i].name[j] = environ[i][j];
                j++;
            }
            data->vars_container[i].name[j] = '\0';

            j = 0;
            while (environ[i][equal_sign + 1] != '\0' && (size_t)j < sizeof(data->vars_container[i].value) - 1) {
                data->vars_container[i].value[j] = environ[i][equal_sign + 1];
                j++;
                equal_sign++;
            }
            data->vars_container[i].value[j] = '\0';

            data->num_vars++;
        }

        i++;
        if (i >= MAX_VARS) {
            environ[i] = NULL; // Ensure we don't go out of bounds
        }
    }

    data->vars_container[data->num_vars].name[0] = '\0';
    data->vars_container[data->num_vars].value[0] = '\0';
}


void print_vars(const t_data *data) 
{
	printf("\n");
	for (int i = 0; i < data->num_vars; i++) 
	{
		printf("%-18s", data->vars_container[i].name);
		printf("value: %s\n", data->vars_container[i].value);
	}
}

int set_var(t_data *data, const char *name, const char *value)
{
    if (data->num_vars >= MAX_VARS)
    {
        fprintf(stderr, "Maximum number of variables reached\n");
        return -1;
    }

    int i = 0;
    while (i < data->num_vars)
    {
        if (ft_strcmp(data->vars_container[i].name, name) == 0)
        {
            strncpy(data->vars_container[i].value, value, sizeof(data->vars_container[i].value) - 1);
            data->vars_container[i].value[sizeof(data->vars_container[i].value) - 1] = '\0';
            return 0;
        }
        i++;
    }

    // Variable not found, add it
    if (data->num_vars < MAX_VARS)
    {
        strncpy(data->vars_container[data->num_vars].name, name, sizeof(data->vars_container[data->num_vars].name) - 1);
        data->vars_container[data->num_vars].name[sizeof(data->vars_container[data->num_vars].name) - 1] = '\0';
        strncpy(data->vars_container[data->num_vars].value, value, sizeof(data->vars_container[data->num_vars].value) - 1);
        data->vars_container[data->num_vars].value[sizeof(data->vars_container[data->num_vars].value) - 1] = '\0';
        data->num_vars++;
        return 0;
    }
    else
    {
        fprintf(stderr, "Maximum number of variables reached\n");
        return -1;
    }
}


int unset_var(t_data *data, const char *name)
{
    int i;
    int j;

    i = 0;
    while (i < data->num_vars)
    {
        if (ft_strcmp(data->vars_container[i].name, name) == 0)
        {
            j = i;
            while (j < data->num_vars - 1)
            {
                strcpy(data->vars_container[j].name, data->vars_container[j + 1].name);
                strcpy(data->vars_container[j].value, data->vars_container[j + 1].value);
                j++;
            }
            data->num_vars--;
            data->vars_container[data->num_vars].name[0] = '\0';
            data->vars_container[data->num_vars].value[0] = '\0';
            return 0;
        }
        i++;
    }
    fprintf(stderr, "Variable '%s' not found\n", name);
    return -1;
}


int export_var(t_data *data, const char *name)
{
	int i;
	int j;

	i = 0;
	while (i < data->num_vars)
	{
		if (ft_strcmp(data->vars_container[i].name, name) == 0)
		{
			j = 0;
			while (j < data->num_exported_vars)
			{
				if (ft_strcmp(data->exported_vars_container[j].name, name) == 0)
					return (0); // Bereits exportiert
				j++;
			}

			if (data->num_exported_vars >= MAX_VARS)
				return (0); // Kein Platz für weitere exportierte Variablen

			data->exported_vars_container[data->num_exported_vars] = data->vars_container[i];
			data->num_exported_vars++;
			return (1); // Erfolgreich exportiert
		}
		i++;
	}
	return (0); // Variable nicht gefunden
}

void print_exported_vars(const t_data *data)
{
	printf("\nExported Variables:\n");
	int i = 0;
	while (i < data->num_exported_vars)
	{
		printf("%-18s", data->exported_vars_container[i].name);
		printf("value: %s\n", data->exported_vars_container[i].value);
		i++;
	}
}


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

	search_special(cmd);
		return cmd;
}


int search_special(struct node_s *cmd)
{
	printf("inside search_special\n");
	struct node_s *current = cmd->first_child;
	while(current->next_sibling)
	{
		if (ft_strcmp(current->str, "|") == 0)
		{
			printf("found pipe\n");


/////////

		struct node_type_master *master_node = malloc(sizeof(struct node_type_master));
		if(!master_node)
			printf("malloc failed\n");
	    // memset(master_node, 0, sizeof(struct node_type_master));
		// struct node_type_master *master_node = new_node(NODE_MASTER);
		
		master_node->root_nodes = malloc(sizeof(struct node_s *) * 3);

////////
			//creating the root for the pipe
			struct node_s *root_pipe = new_node(NODE_COMMAND);
			if(!root_pipe)
				printf("malloc failed\n");

			root_pipe->first_child = current;
			current->type = NODE_SPECIAL;
			
			//creating the root for "wc"
			struct node_s *root_cmd = new_node(NODE_COMMAND);
			if(!root_cmd)
				printf("malloc failed\n");

			root_cmd->first_child = current->next_sibling;
			root_cmd->type = NODE_VAR;

//////// assigning the pipe and "wc" to the master node
			master_node->root_nodes[0] = cmd;	
			master_node->root_nodes[1] = current;	
			master_node->root_nodes[2] = root_cmd;	
			master_node->root_nodes[3] = NULL;	
			master_node->nbr_root_nodes	= 3;
///////

			
			current->next_sibling = NULL;
			
			//current->str = "pipe_content";
			current->prev_sibling->next_sibling = NULL;
			current->prev_sibling->first_child = NULL;

			current = current->next_sibling;


			print_master(master_node);
			return 1;
		}
		current = current->next_sibling;

	}

	return (0);

}


//a function that print the whole ast from node_type_master
void print_master(struct node_type_master *master_node)
{
	printf("inside print_master\n");
	int i = 0;
	while(i < master_node->nbr_root_nodes)
	{
		printf("master_node->root_nodes[%d]->str: %s\n", i, master_node->root_nodes[i]->str);
		printf("master_node->root_nodes[%d]->first_child->str: %s\n", i, master_node->root_nodes[i]->first_child->str);

		i++;
	}
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