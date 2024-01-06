#include "../../include/vars.h"
#include "../../include/expander.h"
#include "../../include/parser_nodes.h"
#include "../../include/parser.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

///This should probably be DELETED
void	print_exported_vars(const t_data *data)
{
	int	i;

	i = 0;
	printf("\nExported Variables:\n");
	while (i < data->num_shell_vars)
	{
		printf("%-18s", data->shell_vc[i].name);
		printf("value: %s\n", data->shell_vc[i].value);
		i++;
	}
}

///This should probably be DELETED
void	print_vars(const t_data *data)
{
	int	i;

	i = 0;
	printf("\n");
	while (i < data->num_vars)
	{
		printf("%-18s", data->vc[i].name);
		printf("value: %s\n", data->vc[i].value);
		i++;
	}
}
