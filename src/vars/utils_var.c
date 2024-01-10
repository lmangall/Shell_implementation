/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:57:33 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 17:57:39 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/vars.h"
#include "../../include/expander.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

void	exit_with_error(const char *errorMessage)
{
	perror(errorMessage);
	exit(EXIT_FAILURE);
}

void	copy_env_var(char *env_var, t_data *data, int i)
{
	size_t	total_length;

	total_length = 0;
	total_length = ft_strlen(data->vc[i].name);
	total_length += ft_strlen(data->vc[i].value) + 2;
	ft_strlcpy(env_var, data->vc[i].name, total_length);
	ft_strlcat(env_var, "=", total_length);
	ft_strlcat(env_var, data->vc[i].value, total_length);
}

// is this function double ?
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

char	*return_env_from_container(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_vars)
	{
		if (ft_strcmp(data->vc[i].name, "PATH") == 0)
			return (data->vc[i].value);
		i++;
	}
	return (NULL);
}
