
#include "../../lib/libft/src/libft.h"
#include "../../include/builtins.h"
#include "../../include/parser.h"
#include "../../include/expander.h"
#include "../../include/node.h"
#include "../../include/parser.h"

char *get_var_value(t_data *data, char *name)
{
	int i;
	i = 0;
	while (data->vars_container[i].name[0] != '\0')
	{
		if (strcmp(data->vars_container[i].name, name) == 0)
			return (data->vars_container[i].value);
		i++;
	}
	return (NULL);
}

void do_cd_builtin(char **argv, t_data *data)
{
	char *path;
	char *oldpwd;
	char *pwd;

	path = NULL;
	oldpwd = NULL;
	pwd = NULL;

	write(1, "...inside the builtin cd :)\n", 28);

	if (argv[1] == NULL) {
		path = ft_strdup(get_var_value(data, "HOME"));
	} else if (ft_strcmp(argv[1], "-") == 0) {
		path = ft_strdup(get_var_value(data, "OLDPWD"));
	} else {
		path = ft_strdup(argv[1]);
	}

	oldpwd = getcwd(NULL, 0);
	if (chdir(path) == -1) {
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		free(path);
		free(oldpwd);
		return;
	}
	pwd = getcwd(NULL, 0);
	set_var(data, "OLDPWD", oldpwd);
	set_var(data, "PWD", pwd);
	free(path);
	free(oldpwd);
	free(pwd);
}
#if 0
int do_cd_builtin(struct node_s *path, t_data *data) 
{

	//printf("cd builtin\n");
	//printf("cmd->str: %s\n", path->str);
	if (path->next_sibling)
	{
		chdir(path->next_sibling->str);
		// printf("cmd->next_sibling->str: %s\n", path->next_sibling->str);
		//update pwd in the vars_container
		// this might be wrong because it is maybe too short
		set_var(data, "PWD", path->next_sibling->str);
		return(1);
	}
	else
	{
		// gonna fix this later
		// because could be different for our purposes
		
		// chdir(get_var_value(data, "HOME"));
		// printf("data->home: %s\n", get_var_value(data, "HOME"));
	}

	return (0);
}
#endif