/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 17:14:51 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/09 16:04:33 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/lexer.h"
#include "../../include/main.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

void	expand_var(char **str, t_vars **var)
{
	int		i;
	int		j;
	char	*str_xpnded;

	i = 0;
	j = 0;
	str_xpnded = ft_strdup("");
	while ((*str)[j] != '\0')
	{
		if ((*str)[j] == '$')
		{
			str_xpnded = ft_strjoin(str_xpnded, (*var)->value);
			i += ft_strlen((*var)->value);
			j += ft_strlen((*var)->name) + 1;
		}
		if ((*str)[j] != '\0')
		{
			str_xpnded = ft_strjoin(str_xpnded, (char []){(*str)[j], '\0'});
			j++;
			i++;
		}
	}
	free(*str);
	*str = str_xpnded;
}

t_vars	*find_var(char *name, t_data *data)
{
	int		i;
	t_vars	*control;

	i = 0;
	control = ft_calloc(1, sizeof(t_vars));
	if (!control)
		return (control);
	while (i < data->num_vars)
	{
		if (ft_strcmp(name, data->vc[i].name) == 0)
			return (&data->vc[i]);
		else
			i++;
	}
	return (control);
}

char	*identify_var(char *str, t_data *data)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (i < data->num_vars)
	{
		if (ft_strstr(str, data->vc[i].name) != NULL)
			return (data->vc[i].name);
		else
			i++;
	}
	return (NULL);
}

char	*expand(char *str, t_data *data)
{
	char	*var_name;
	t_vars	*var;
	int		expansion;

	var_name = NULL;
	var = NULL;
	expansion = 5;
	if (contains_two(str, '\"') || contains_two(str, '\''))
		expansion = quote_pattern(str);
	if (expansion <= 2 || expansion == 5)
	{
		var_name = identify_var(str, data);
		var = find_var(var_name, data);
		expand_var(&str, &var);
	}
	if (contains_two(str, '\"') || contains_two(str, '\''))
		str = (char *)erase_outside_quotes(str);
	return (str);
}
