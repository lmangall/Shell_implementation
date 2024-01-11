/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:04:01 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/11 16:26:49 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/expander.h"
#include "../../include/free.h"
#include "../../include/parser.h"
#include "../../include/parser_nodes.h"
#include "../../lib/libft/src/libft.h"

char	*return_var_value(t_data *data, char *name)
{
	int	i;

	i = 0;
	while (data->vc[i].name[0] != '\0')
	{
		if (strcmp(data->vc[i].name, name) == 0)
			return (data->vc[i].value);
		i++;
	}
	return (NULL);
}

char	*get_cd_path(char **argv, t_data *data)
{
	if (!argv[1])
		return (ft_strdup(return_var_value(data, "HOME")));
	else if (strcmp(argv[1], "-") == 0)
		return (ft_strdup(return_var_value(data, "OLDPWD")));
	else
		return (ft_strdup(argv[1]));
}

int	change_directory(char *path, t_data *data)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		printf("cd: %s: %s\n", path, strerror(errno));
		free(path);
		free(oldpwd);
		return (3);
	}
	pwd = getcwd(NULL, 0);
	set_var(data, "OLDPWD", oldpwd);
	set_var(data, "PWD", pwd);
	return (-1);
}

int	do_cd_builtin(char **argv, t_data *data)
{
	char	*path;
	int		result;

	path = get_cd_path(argv, data);
	result = change_directory(path, data);
	free(path);
	free_string_array(argv);
	return (result);
}
