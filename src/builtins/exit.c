#include "../../include/builtins.h"
#include "../../include/expander.h"
#include "../../include/free.h"
#include "../../include/parser.h"
#include "../../include/parser_nodes.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"

int	do_exit_builtin(char *line, t_data *data)
{
	int		exit_code;
	char	**argv;

	(void)data;
	argv = ft_split(line, ' ');
	if (argv[1] != NULL && argv[2] == NULL)
	{
		exit_code = ft_atoi(argv[1]);
	}
	else if (argv[1] == NULL)
	{
		exit_code = 0;
	}
	else
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		exit_code = 1;
	}
	free(argv);
	exit(exit_code);
}

