#include "../../lib/libft/src/libft.h"
#include "../../include/builtins.h"
#include "../../include/parser.h"
#include "../../include/expander.h"
#include "../../include/node.h"
#include "../../include/parser.h"
#include <unistd.h>
#include <errno.h>

int	check_and_builtins(char *line, t_data *data)
{
	if (ft_strncmp(line, "exit", 3) == 0)
		return(-1);
	if (ft_strncmp(line, "cd ", 3) == 0)
		do_cd_builtin(lexer(line), data);
	if (ft_strcmp(line, "env") == 0)///     => check if working properly
		do_env_builtin(data);
	if (ft_strcmp(line, "pwd") == 0)
		do_pwd_builtin(data);
	// if (ft_strcmp(line, "export") == 0)
	// 	do_export_builtin(tokens, data);
	// if (ft_strcmp(line, "unset") == 0)
	// 	do_unset_builtin(tokens, data);
	// if (ft_strcmp(line, "history") == 0)
	// 	display_history();
	return(1);
}