
#include "../../lib/libft/src/libft.h"
#include "../../include/builtins.h"
#include "../../include/parser.h"
#include "../../include/expander.h"
#include "../../include/node.h"
#include "../../include/parser.h"


int contains_cd(struct node_s *node)//change it for a node that contains ONLY cd
{
	int i;
	
	i = 0;
	while (node->str[i] != '\0')
	{
		if (node->str[i] == 'c' && node->str[i + 1] == 'd')
			return(1);
		i++;
	}
	return(0);
}

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