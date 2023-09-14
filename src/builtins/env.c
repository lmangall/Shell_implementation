#include "../../lib/libft/src/libft.h"
#include "../../include/builtins.h"
#include "../../include/parser.h"
#include "../../include/expander.h"
#include "../../include/node.h"
#include "../../include/parser.h"
#include <unistd.h>
#include <errno.h>

void do_env_builtin(t_data *data)
{
   
	printf("\n");
	for (int i = 0; i < data->num_vars; i++) 
	{
		printf("%-18s", data->vars_container[i].name);
		printf("value: %s\n", data->vars_container[i].value);
	}
}
