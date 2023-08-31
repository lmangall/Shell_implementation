/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:27:44 by lmangall          #+#    #+#             */
/*   Updated: 2023/08/30 14:45:56 by lmangall         ###   ########.fr       */
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


void init_vars(t_data *data) //should this take it from environ? can we just do our own ?
{
	extern char **environ;
	int i = 0;
	int j;
	int equal_sign;

	data->num_vars = 0;
	data->num_exported_vars = 0;

	while (environ[i] != NULL && i < MAX_VARS) 
	{
		equal_sign = find_equal_sign(environ[i]);
		if (equal_sign == -1) 
		{
			i++;
			continue;
		}

		j = 0;
		while (j < equal_sign && (size_t)j < sizeof(data->vars_container[i].name) - 1) 
		{
			data->vars_container[i].name[j] = environ[i][j];
			j++;
		}
		data->vars_container[i].name[j] = '\0';

		j = 0;
		while (environ[i][equal_sign + 1] != '\0' && (size_t)j < sizeof(data->vars_container[i].value) - 1) 
		{
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
		return cmd;
}