
#include "../../include/vars.h"
#include "../../include/expander.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

int	unset_shell_var(t_data *data, const char *name)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->num_shell_vars)
	{
		if (ft_strcmp(data->shell_vc[i].name, name) == 0)
		{
			j = i;
			while (j < data->num_shell_vars - 1)
			{
				strcpy(data->shell_vc[j].name, data->shell_vc[j + 1].name);
				strcpy(data->shell_vc[j].value, data->shell_vc[j + 1].value);
				j++;
			}
			data->num_shell_vars--;
			data->shell_vc[data->num_shell_vars].name[0] = '\0';
			data->shell_vc[data->num_shell_vars].value[0] = '\0';
			return (0);
		}
		i++;
	}
	fprintf(stderr, "Variable '%s' not found\n", name);
	return (-1);
}

int	unset_var(t_data *data, const char *name)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->num_vars)
	{
		if (ft_strcmp(data->vc[i].name, name) == 0)
		{
			j = i;
			while (j < data->num_vars - 1)
			{
				strcpy(data->vc[j].name, data->vc[j + 1].name);
				strcpy(data->vc[j].value, data->vc[j + 1].value);
				j++;
			}
			data->num_vars--;
			data->vc[data->num_vars].name[0] = '\0';
			data->vc[data->num_vars].value[0] = '\0';
			return (0);
		}
		i++;
	}
	fprintf(stderr, "Variable '%s' not found\n", name);
	return (-1);
}

// if the command "unset" is called with a space 
// and a variable name, it will call this function unset
int	do_unset_builtin(char **tokens, t_data *data)
{
	int	i;

	i = 1;
	while (tokens[i] != NULL)
	{
		unset_var(data, tokens[i]);
		i++;
	}
	return (-1);
}
