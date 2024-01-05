#include "../../include/vars.h"
#include "../../include/expander.h"
#include "../../include/node.h"
#include "../../include/parser.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

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

//called from utils.c
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
char **convert_vars_container_to_envp(t_data *data)
{
	char **envp = malloc((data->num_vars + 1) * sizeof(char *));
	if (envp == NULL)
	{
		perror("Ceci est une erreur");
		exit(EXIT_FAILURE);
	}

	int i = 0;
	while (i < data->num_vars)
	{
		char *env_var = malloc(strlen(data->vars_container[i].name) + ft_strlen(data->vars_container[i].value) + 2);
		if (env_var == NULL)
		{
			perror("Tout va bien se passer");
			exit(EXIT_FAILURE);
		}

		sprintf(env_var, "%s=%s", data->vars_container[i].name, data->vars_container[i].value);
		envp[i] = env_var;

		i++;
	}

	envp[data->num_vars] = NULL;

	return envp;
}