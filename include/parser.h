

#ifndef PARSER_H
#define PARSER_H


typedef struct s_data
{
	// char					*args;
	char					*paths;
	char					*envp;
	// char					*pwd;
	// char					*old_pwd;
	// struct s_simple_cmds	*simple_cmds;
	// t_lexer					*lexer_list;
	// int						pipes;
	// int						*pid;
	// bool					heredoc;
	//tokens???
}	t_data;

void	init_data(t_data *data);
int 	parse_and_execute(char *line);
int		check_dollar(char *str);
int		expansion(struct node_s *node);
// void	add_to_env(char *var);


#endif