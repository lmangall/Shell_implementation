/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:27:44 by lmangall          #+#    #+#             */
/*   Updated: 2023/08/24 16:53:26 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../lib/libft/src/libft.h"
#include <unistd.h>
#include "../include/shell.h"
#include "../include/lexer.h"
#include "../include/node.h"
#include "../include/vars.h"
#include "../include/shell.h"
#include "../include/parser.h"

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
    extern char **environ;
    int i = 0;
    int j;
    int equal_sign;

    data->num_vars = 0;

    while (environ[i] != NULL && i < MAX_VARS) {
        equal_sign = find_equal_sign(environ[i]);
        if (equal_sign == -1) {
            i++;
            continue;
        }

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
        i++;

        if (i >= MAX_VARS) {
            break;
        }
    }

    data->vars_container[data->num_vars].name[0] = '\0';
    data->vars_container[data->num_vars].value[0] = '\0';
}


void print_vars(const t_data *data) {
    for (int i = 0; i < data->num_vars; i++) {
        printf("name: %s\n", data->vars_container[i].name);
        printf("value: %s\n", data->vars_container[i].value);
    }
}

int set_var(t_data *data, const char *name, const char *value) {
    if (data->num_vars >= MAX_VARS) {
        fprintf(stderr, "Maximum number of variables reached\n");
        return -1;
    }

    for (int i = 0; i < data->num_vars; i++) {
        if (strcmp(data->vars_container[i].name, name) == 0) {
            strncpy(data->vars_container[i].value, value, sizeof(data->vars_container[i].value));
            data->vars_container[i].value[sizeof(data->vars_container[i].value) - 1] = '\0';
            return 0;
        }
    }

    // Variable nicht gefunden, füge sie hinzu
    strncpy(data->vars_container[data->num_vars].name, name, sizeof(data->vars_container[data->num_vars].name));
    data->vars_container[data->num_vars].name[sizeof(data->vars_container[data->num_vars].name) - 1] = '\0';
    strncpy(data->vars_container[data->num_vars].value, value, sizeof(data->vars_container[data->num_vars].value));
    data->vars_container[data->num_vars].value[sizeof(data->vars_container[data->num_vars].value) - 1] = '\0';
    data->num_vars++;

    return 0;
}

int unset_var(t_data *data, const char *name) {
    for (int i = 0; i < data->num_vars; i++) {
        if (strcmp(data->vars_container[i].name, name) == 0) {
            for (int j = i; j < data->num_vars - 1; j++) {
                strcpy(data->vars_container[j].name, data->vars_container[j + 1].name);
                strcpy(data->vars_container[j].value, data->vars_container[j + 1].value);
            }
            data->num_vars--;
            data->vars_container[data->num_vars].name[0] = '\0';
            data->vars_container[data->num_vars].value[0] = '\0';
            return 0;
        }
    }
    fprintf(stderr, "Variable '%s' not found\n", name);
    return -1;
}






int	check_dollar(char *str)
{
	if (str[0] == '$')
		return(1);
	return (0);
}

// static int replace_var(struct node_s *node)
// {
// // 	char 
// // 	node->str = get_vars_value(node->str);

// // }	
// 	//ft_memchr
// 	ft_memcpy(node->str, get_vars_value(node->str), ft_strlen(get_vars_value(node->str)));
// 	return (0);
// }

//a function that transverses  the AST and use the check_dollar function to identify a dollar and print a statement
//the function is called expansion 
// int expansion(struct node_s *node)
// {
// 	if (node->type == NODE_VAR)
// 	{
// 		if (check_dollar(node->str) == 1)
// 		{
// 			printf("Dollar found in %s\n", node->str);
// 			//print_vars(); //    THIS SEGAULTS
// 			// replace_var(node);
// 			printf("str after replace_var: %s\n", node->str);
// 		}
// 	}
// 	if (node->first_child)
// 		expansion(node->first_child);
// 	if (node->next_sibling)
// 		expansion(node->next_sibling);
// 	return (0);
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