/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:02:56 by lmangall          #+#    #+#             */
/*   Updated: 2023/10/13 12:36:55 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/node.h"
#include "../include/parser.h"
#include "../include/shell.h"
#include "../include/vars.h"
#include "../lib/libft/src/libft.h"
#include <unistd.h>

// get_vars_value takes a name and returns the value of the variable with that name
// it returns NULL if it failed
// char *get_vars_value(char *name)
// {
// 	int i;

// 	i = 0;
// 	while (vars_container[i].name[0] != '\0')
// 	{
// 		if (strcmp(vars_container[i].name, name) == 0)
// 			return (vars_container[i].value);
// 		i++;
// 	}
// 	return (NULL);
// }

// THIS FUNCTION IS MOR OR LESS DOUBLE
int	find_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	init_vars(t_data *data, char **envp)
{
	int	i;
	int	j;
	int	equal_sign;

	// extern char **envp;
	// Assumption: extern declaration for the envpment variables
	i = 0;
	data->num_vars = 0;
	data->num_exported_vars = 0;
	while (envp[i] != NULL && i < MAX_VARS)
	{
		equal_sign = find_equal_sign(envp[i]);
		if (equal_sign != -1)
		{
			j = 0;
			while (j < equal_sign
				&& (size_t)j < sizeof(data->vars_container[i].name) - 1)
			{
				data->vars_container[i].name[j] = envp[i][j];
				j++;
			}
			data->vars_container[i].name[j] = '\0';
			j = 0;
			while (envp[i][equal_sign + 1] != '\0'
				&& (size_t)j < sizeof(data->vars_container[i].value) - 1)
			{
				data->vars_container[i].value[j] = envp[i][equal_sign + 1];
				j++;
				equal_sign++;
			}
			data->vars_container[i].value[j] = '\0';
			data->num_vars++;
		}
		i++;
		if (i >= MAX_VARS)
			envp[i] = NULL; // Ensure we don't go out of bounds
	}
	data->vars_container[data->num_vars].name[0] = '\0';
	data->vars_container[data->num_vars].value[0] = '\0';
}

void	print_vars(const t_data *data)
{
	printf("\n");
	for (int i = 0; i < data->num_vars; i++)
	{
		printf("%-18s", data->vars_container[i].name);
		printf("value: %s\n", data->vars_container[i].value);
	}
}

int	set_var(t_data *data, const char *name, const char *value)
{
	int	i;

	if (data->num_vars >= MAX_VARS)
	{
		fprintf(stderr, "Maximum number of variables reached\n");
		return (-1);
	}
	i = 0;
	while (i < data->num_vars)
	{
		if (ft_strcmp(data->vars_container[i].name, name) == 0)
		{
			strncpy(data->vars_container[i].value, value,
				sizeof(data->vars_container[i].value) - 1);
			data->vars_container[i].value[sizeof(data->vars_container[i].value)
				- 1] = '\0';
			return (0);
		}
		i++;
	}
	// Variable not found, add it
	if (data->num_vars < MAX_VARS)
	{
		strncpy(data->vars_container[data->num_vars].name, name,
			sizeof(data->vars_container[data->num_vars].name) - 1);
		data->vars_container[data->num_vars].name[sizeof(data->vars_container[data->num_vars].name)
			- 1] = '\0';
		strncpy(data->vars_container[data->num_vars].value, value,
			sizeof(data->vars_container[data->num_vars].value) - 1);
		data->vars_container[data->num_vars].value[sizeof(data->vars_container[data->num_vars].value)
			- 1] = '\0';
		data->num_vars++;
		return (0);
	}
	else
	{
		fprintf(stderr, "Maximum number of variables reached\n");
		return (-1);
	}
}

int	unset_var(t_data *data, const char *name)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->num_vars)
	{
		if (ft_strcmp(data->vars_container[i].name, name) == 0)
		{
			j = i;
			while (j < data->num_vars - 1)
			{
				strcpy(data->vars_container[j].name, data->vars_container[j
					+ 1].name);
				strcpy(data->vars_container[j].value, data->vars_container[j
					+ 1].value);
				j++;
			}
			data->num_vars--;
			data->vars_container[data->num_vars].name[0] = '\0';
			data->vars_container[data->num_vars].value[0] = '\0';
			return (0);
		}
		i++;
	}
	fprintf(stderr, "Variable '%s' not found\n", name);
	return (-1);
}

int	export_var(t_data *data, const char *name)
{
	int	i;
	int	j;

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

void	print_exported_vars(const t_data *data)
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


/// there is a get_var_value function in the cd.c file (in builtins)


// int isValidVariableDeclaration(const char *input)
// this function checks if the input consist of only valid characters till the first equal sign
// valid characters are: Capital letters, numbers and underscores
// and after the first equal sign, it doesn't matter what the input is
// returns 1 if valid, 0 if not
int isValidVariableDeclaration(const char *input)
{
    // Check if the input is empty or starts with an equal sign
    if (input == NULL || input[0] == '=')
    {
        return 0; // Invalid input
    }

    int i = 0;

    // Check characters before the first equal sign
    while (input[i] != '=' && input[i] != '\0')
    {
        // Check if the character is a capital letter, number, or underscore
        if (!((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= '0' && input[i] <= '9') || input[i] == '_'))
        {
            return 0; // Invalid character encountered
        }
        i++;
    }

    return 1; // Valid variable declaration
}


int check_for_variable_setting(t_data *data, char *token)
{
    // Check if the token is a valid variable declaration
    if (isValidVariableDeclaration(token))
    {
        // Find the equal sign
        int equal_sign = find_equal_sign(token);
        set_var(data, token, token + equal_sign + 1);

        return 1; // Variable set
    }
    else
    {
        return 0; // Variable not set
    }
}