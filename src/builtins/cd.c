/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:04:01 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 17:59:26 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include "../../include/expander.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
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

int	do_cd_builtin(char **argv, t_data *data)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;

	path = NULL;
	oldpwd = NULL;
	pwd = NULL;
	if (argv[1] == NULL)
		path = ft_strdup(return_var_value(data, "HOME"));
	else if (ft_strcmp(argv[1], "-") == 0)
		path = ft_strdup(return_var_value(data, "OLDPWD"));
	else
		path = ft_strdup(argv[1]);
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		printf("cd: %s: %s\n", path, strerror(errno));
		free(path);
		free(oldpwd);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	set_var(data, "OLDPWD", oldpwd);
	set_var(data, "PWD", pwd);
	free(path);
	free(oldpwd);
	free(pwd);
	return (-1);
}
