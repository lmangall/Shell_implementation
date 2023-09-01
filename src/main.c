/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:22:39 by lmangall          #+#    #+#             */
/*   Updated: 2023/09/01 21:45:11 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include "../include/shell.h"
#include "../include/lexer.h"
#include "../include/vars.h"
#include "../include/parser.h"
#include "../include/executor.h"
#include "../include/expander.h"
#include "../include/builtins.h"
#include "../include/signals.h"
#include "../lib/libft/src/libft.h"
#include <readline/readline.h>
#include <readline/history.h>


// void display_history() 
// {
// 	int i = history_base;
	
// 	while (i < history_length) 
// 	{
// 		HIST_ENTRY *entry = history_get(i);
// 		if (entry != NULL)
// 			printf("%d: %s\n", i, entry->line);
// 	}
// 		i++;
// }


int main(void)
{
	char *line;
	int status;
	t_data data;
	data.paths = NULL;
	data.envp = NULL;
	
	// data = malloc(sizeof(t_data)); // Allocate memory for data
	// if (!data) 
	// {
	// 	fprintf(stderr, "lsh: allocation error\n");
	// 	exit(EXIT_FAILURE);
	// }

	init_vars(&data);

	signal(SIGINT, handle_ctrl_c);
    signal(SIGQUIT, handle_ctrl_backslash);


	status = 1;
	while(status)
	{
		line = readline(SHELL_PROMPT);
		if (line == NULL)
		{
            handle_ctrl_d(SIGQUIT);
        }		
	if(line[0] !=  '\0')
		{
		add_history(line);
		status = parse_and_execute(line, &data);
		}
		// if (ft_strcmp(line, "history") == 0)
		// 	display_history();
		if (ft_strcmp(line, "exit") == 0)
			status = 0;
		if (ft_strcmp(line, "myenv") == 0)
			print_vars(&data);
	}
	

	return EXIT_SUCCESS;
}


int parse_and_execute(char *line, t_data *data)
{

	(void)data;
	
	// int i;
	char **tokens;
	tokens = lexer(line);
	free(line);

//  ->  COMMENTED OUT FOR COMPLEX AST (pipe) TESTING
//	struct node_s *cmd = parse_simple_command(tokens);


//  ->  ADDED FOR COMPLEX AST (pipe) TESTING
	struct node_type_master *master_node = parse_simple_command(tokens);
	execute_pipe_command(master_node);
	// free_master_node(master_node);
	free(tokens);

	
	
	
//  ->  COMMENTED OUT FOR COMPLEX AST (pipe) TESTING
	// // variable substitution
	// struct node_s *cpy = malloc(sizeof(struct node_s));
	// cpy = cmd->first_child->next_sibling;
	// while (cpy)
	// {
	// 	expansion_substitution(cpy, data);
	// 	cpy = cpy->next_sibling;
	// }
	
	// if (expansion_set_var(cmd->first_child, data) || do_cd_builtin(cmd->first_child, data))
	// 	printf("   done   \n");

//  ->  COMMENTED OUT FOR COMPLEX AST (pipe) TESTING
	// i = 0;
	// while(i == 0)
	// {
	// 	if(!cmd)
	// 		break;
	// 	do_simple_command(cmd, data);
	// 	free_node_tree(cmd);
	// 	free(tokens);
	// 	i++;
	// }
	return 1;
}

