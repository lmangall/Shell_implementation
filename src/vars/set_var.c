
#include "../../include/vars.h"
#include "../../include/expander.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
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