/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:55:43 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/15 22:07:00 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/parser.h"
#include "../../include/parser_nodes.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

static int	add_var_from_env(t_data *data, char *env_var)
{
	int	equal_sign;
	int	j;

	equal_sign = find_equal_sign(env_var);
	if (equal_sign == -1)
		return (0);
	j = 0;
	while (j < equal_sign && (size_t)j < sizeof(data->vc[data->num_vars].name)
		- 1)
	{
		data->vc[data->num_vars].name[j] = env_var[j];
		j++;
	}
	data->vc[data->num_vars].name[j] = '\0';
	j = 0;
	while (env_var[equal_sign + 1] != '\0'
		&& (size_t)j < sizeof(data->vc[data->num_vars].value) - 1)
	{
		data->vc[data->num_vars].value[j] = env_var[equal_sign + 1];
		j++;
		equal_sign++;
	}
	data->vc[data->num_vars].value[j] = '\0';
	data->num_vars++;
	return (1);
}

void	init_vars(t_data *data, char **envp)
{
	int	i;

	i = 0;
	data->num_vars = 0;
	data->num_shell_vars = 0;
	while (envp[i] != NULL && i < MAX_VARS)
	{
		if (add_var_from_env(data, envp[i]))
			i++;
		if (i >= MAX_VARS)
			envp[i] = NULL;
	}
	data->vc[data->num_vars].name[0] = '\0';
	data->vc[data->num_vars].value[0] = '\0';
	data->erased_out_quotes = 0;
	set_var(data, "?", "0");
}

int	is_valid_variable_declaration(const char *input)
{
	int	i;

	if (find_equal_sign((char *) input) == -1)
		return (-1);
	if (input == NULL || input[0] == '=')
	{
		return (0);
	}
	i = 0;
	while (input[i] != '=' && input[i] != '\0')
	{
		if (!((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= '0'
					&& input[i] <= '9') || input[i] == '_'))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

// called from utils.c
int	check_for_variable_setting(t_data *data, char *token)
{
	int		equal_sign;
	char	*name;
	char	*value;

	if (is_valid_variable_declaration(token) != -1)
	{
		equal_sign = find_equal_sign(token);
		name = ft_substr(token, 0, equal_sign);
		value = ft_substr(token, equal_sign + 1, ft_strlen(token) - equal_sign);
		set_shell_var(data, name, value);
		free(name);
		free(value);
		return (3);
	}
	else
		return (1);
}

// should envp be freed ?
char	**convert_vc_to_envp(t_data *data)
{
	char	**envp;
	int		i;
	char	*env_var;

	i = 0;
	envp = malloc((data->num_vars + 1) * sizeof(char *));
	if (envp == NULL)
	{
		exit_with_error("Ceci est une erreur");
	}
	while (i < data->num_vars)
	{
		env_var = malloc(ft_strlen(data->vc[i].name)
				+ ft_strlen(data->vc[i].value) + 2);
		if (env_var == NULL)
		{
			exit_with_error("Tout va bien se passer");
		}
		copy_env_var(env_var, data, i);
		envp[i] = env_var;
		i++;
	}
	envp[data->num_vars] = NULL;
	return (envp);
}
