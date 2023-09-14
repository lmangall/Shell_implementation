#include "../../lib/libft/src/libft.h"
#include "../../include/builtins.h"
#include "../../include/parser.h"
#include "../../include/expander.h"
#include "../../include/node.h"
#include "../../include/parser.h"
#include <unistd.h>
#include <errno.h>

void do_pwd_builtin(t_data *data)
{
	(void)data;
	char *pwd = getcwd(NULL, 0);

	if (pwd == NULL) {
		ft_putstr_fd("pwd: error retrieving current directory: getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return;
	}

	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free(pwd);
}