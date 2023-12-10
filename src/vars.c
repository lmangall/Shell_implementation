/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:02:56 by lmangall          #+#    #+#             */
/*   Updated: 2023/12/10 16:58:35 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"
#include "../include/node.h"
#include "../include/parser.h"
#include "../include/shell.h"
#include "../include/vars.h"
#include "../lib/libft/src/libft.h"
#include <unistd.h>

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

	i = 0;
	data->num_vars = 0;
	data->num_shell_vars = 0;
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
			envp[i] = NULL;
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

char	*return_env_from_container(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_vars)
	{
		if (ft_strcmp(data->vars_container[i].name, "PATH") == 0)
			return (data->vars_container[i].value);
		i++;
	}
	return (NULL);
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

int set_shell_var(t_data *data, const char *name, const char *value)
{
    int i;

    if (data->num_shell_vars >= MAX_VARS)
    {
        fprintf(stderr, "Maximum number of shell variables reached\n");
        return (-1);
    }

    i = 0;
    while (i < data->num_shell_vars)
    {
        if (ft_strcmp(data->shell_vars_container[i].name, name) == 0)
        {
            strncpy(data->shell_vars_container[i].value, value,
                    sizeof(data->shell_vars_container[i].value) - 1);
            data->shell_vars_container[i].value[sizeof(data->shell_vars_container[i].value) - 1] = '\0';
            return (0);
        }
        i++;
    }

    // Variable not found, add it
    if (data->num_shell_vars < MAX_VARS)
    {
        strncpy(data->shell_vars_container[data->num_shell_vars].name, name,
                sizeof(data->shell_vars_container[data->num_shell_vars].name) - 1);
        data->shell_vars_container[data->num_shell_vars].name[sizeof(data->shell_vars_container[data->num_shell_vars].name) - 1] = '\0';
        strncpy(data->shell_vars_container[data->num_shell_vars].value, value,
                sizeof(data->shell_vars_container[data->num_shell_vars].value) - 1);
        data->shell_vars_container[data->num_shell_vars].value[sizeof(data->shell_vars_container[data->num_shell_vars].value) - 1] = '\0';
        data->num_shell_vars++;
        return (0);
    }
    else
    {
        fprintf(stderr, "Maximum number of shell variables reached\n");
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

// if the command "unset" is called with a space and a variable name, it will call this function unset
int do_unset_builtin(char **tokens, t_data *data)
{
	int	i;

	i = 1;
	while (tokens[i] != NULL)
	{
		unset_var(data, tokens[i]);
		i++;
	}
	return (0);
}

int unset_shell_var(t_data *data, const char *name)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->num_shell_vars)
	{
		if (ft_strcmp(data->shell_vars_container[i].name, name) == 0)
		{
			j = i;
			while (j < data->num_shell_vars - 1)
			{
				strcpy(data->shell_vars_container[j].name, data->shell_vars_container[j
					+ 1].name);
				strcpy(data->shell_vars_container[j].value, data->shell_vars_container[j
					+ 1].value);
				j++;
			}
			data->num_shell_vars--;
			data->shell_vars_container[data->num_shell_vars].name[0] = '\0';
			data->shell_vars_container[data->num_shell_vars].value[0] = '\0';
			return (0);
		}
		i++;
	}
	fprintf(stderr, "Variable '%s' not found\n", name);
	return (-1);
}

int export_var(t_data *data, const char *name)
{
    int i;
    int j;

    i = 0;
    while (i < data->num_shell_vars)
    {
        if (ft_strcmp(data->shell_vars_container[i].name, name) == 0)
        {
            j = 0;
            while (j < data->num_vars)
            {
                if (ft_strcmp(data->vars_container[j].name, name) == 0)
                    return (0);
                j++;
            }
            if (data->num_vars >= MAX_VARS)
                return (0);
            data->vars_container[data->num_vars] = data->shell_vars_container[i];
            data->num_vars++;
			unset_shell_var(data, name);
            return (1);
        }
        i++;
    }
    return (0);
}

int do_export_builtin(char **tokens, t_data *data)
{
	int	i;

	i = 1;
	while (tokens[i] != NULL)
	{
		export_var(data, tokens[i]);
		i++;
	}
	return (0);
}

void	print_exported_vars(const t_data *data)
{
	printf("\nExported Variables:\n");
	int i = 0;
	while (i < data->num_shell_vars)
	{
		printf("%-18s", data->shell_vars_container[i].name);
		printf("value: %s\n", data->shell_vars_container[i].value);
		i++;
	}
}


/// there is a get_var_value function in the cd.c file (in builtins)


// int isValidVariableDeclaration(const char *input)
// this function checks if the input consist of only valid characters till the first equal sign
// valid characters are: Capital letters, numbers and underscores
// and after the first equal sign, it doesn't matter what the input is
// returns 1 if valid, 0 if not
int is_valid_variable_declaration(const char *input)
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

//maybe transfor into doxygen coments 
        // Find the equal sign
		// copy everything before the equal sign into name
		// copy everything after the equal sign into value
int check_for_variable_setting(t_data *data, char *token)
{
    if (is_valid_variable_declaration(token))
    {
        int equal_sign = find_equal_sign(token);
		char *name;
		char *value;
		name = ft_substr(token, 0, equal_sign);
		value = ft_substr(token, equal_sign + 1, ft_strlen(token) - equal_sign);
		set_shell_var(data, name, value);
        return 1;
    }
    else
        return 0;
}


/**
 * @brief Converts the variables container to an array of strings (envp).
 *
 * This function takes a data structure containing variables and converts it
 * into the standard environment variable format (envp) required by functions
 * like execve. It allocates memory for the resulting array and returns it.
 * The caller is responsible for freeing the memory when it is no longer needed.
 *
 * @param data A data structure containing information about variables.
 * @return An array of strings (envp) representing the variables.
 */
char	**convert_vars_container_to_envp(t_data *data)
{
	char	**envp = malloc((data->num_vars + 1) * sizeof(char *));
	if (envp == NULL) {
		perror("Ceci est une erreur");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < data->num_vars; i++) {
		char *env_var = malloc(strlen(data->vars_container[i].name) + strlen(data->vars_container[i].value) + 2);
		if (env_var == NULL) {
			perror("Tout va bien se passer");
			exit(EXIT_FAILURE);
		}

		sprintf(env_var, "%s=%s", data->vars_container[i].name, data->vars_container[i].value);
		envp[i] = env_var;
	}

	envp[data->num_vars] = NULL;

	return envp;
}