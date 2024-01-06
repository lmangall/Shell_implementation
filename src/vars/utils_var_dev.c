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
	printf("\nExported Variables:\n");
	int i = 0;
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
	printf("\n");
	for (int i = 0; i < data->num_vars; i++)
	{
		printf("%-18s", data->vc[i].name);
		printf("value: %s\n", data->vc[i].value);
	}
}
