
#include "../../include/expander.h"
#include "../../include/parser.h"
#include "../../include/parser_nodes.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

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
		if (ft_strcmp(data->vc[i].name, name) == 0)
		{
			strncpy(data->vc[i].value, value, sizeof(data->vc[i].value) - 1);
			data->vc[i].value[sizeof(data->vc[i].value) - 1] = '\0';
			return (0);
		}
		i++;
	}
	if (data->num_vars < MAX_VARS)
	{
		strncpy(data->vc[data->num_vars].name, name,
			sizeof(data->vc[data->num_vars].name) - 1);
		data->vc[data->num_vars].name[sizeof(data->vc[data->num_vars].name)
			- 1] = '\0';
		strncpy(data->vc[data->num_vars].value, value,
			sizeof(data->vc[data->num_vars].value) - 1);
		data->vc[data->num_vars].value[sizeof(data->vc[data->num_vars].value)
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

int	set_shell_var(t_data *data, const char *name, const char *value)
{
	int	i;

	if (data->num_shell_vars >= MAX_VARS)
	{
		fprintf(stderr, "Maximum number of shell variables reached\n");
		return (-1);
	}
	i = 0;
	while (i < data->num_shell_vars)
	{
		if (ft_strcmp(data->shell_vc[i].name, name) == 0)
		{
			strncpy(data->shell_vc[i].value, value,
				sizeof(data->shell_vc[i].value) - 1);
			data->shell_vc[i].value[sizeof(data->shell_vc[i].value) - 1] = '\0';
			return (0);
		}
		i++;
	}
	if (data->num_shell_vars < MAX_VARS)
	{
		strncpy(data->shell_vc[data->num_shell_vars].name, name,
			sizeof(data->shell_vc[data->num_shell_vars].name) - 1);
		data->shell_vc[data->num_shell_vars].name[sizeof(data->shell_vc[data->num_shell_vars].name)
			- 1] = '\0';
		strncpy(data->shell_vc[data->num_shell_vars].value, value,
			sizeof(data->shell_vc[data->num_shell_vars].value) - 1);
		data->shell_vc[data->num_shell_vars].value[sizeof(data->shell_vc[data->num_shell_vars].value)
			- 1] = '\0';
		data->num_shell_vars++;
		return (0);
	}
	else
	{
		fprintf(stderr, "Maximum number of shell variables reached\n");
		return (-1);
	}
}