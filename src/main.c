/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:22:39 by lmangall          #+#    #+#             */
/*   Updated: 2023/09/06 16:57:05 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include "../include/shell.h"
#include "../include/pipe.h"
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
#include "../include/free.h"
#include <sys/wait.h>




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
// static void free_node(struct node_s *node)
// {
//     if (!node)
//         return;

//     free_node(node->first_child);
//     free_node(node->next_sibling);
//     free(node->str);
//     free(node);
// }

// static void free_master(struct node_type_master *master)
// {
//     if (!master)
//         return;

//     for (int i = 0; i < master->nbr_root_nodes; i++)
//         free_node(master->root_nodes[i]);

//     free(master->root_nodes);
//     free(master->str);
//     free(master);
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
		// if cd is typed with an absolute or relative path, it will do_cd_builtin
		// if cd is typed without an absolute or relative path, it will do_cd_builtin
		if (ft_strncmp(line, "cd ", 3) == 0)
			do_cd_builtin(lexer(line), &data);
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

//write a command that frees the AST from the master node
static void	free_ast(struct node_type_master *master_node)
{
	int i = 0;
	while (i < master_node->nbr_root_nodes)
	{
		free_node_tree(master_node->root_nodes[i]);
		i++;
	}
	free(master_node->root_nodes);
	free(master_node);
}

int parse_and_execute(char *line, t_data *data)
{
    char **tokens = lexer(line);
    free(line);
	int status = 0;

	(void) data;

    // Check if there is a pipe in the command    ->  new cmd
    int has_pipe = 0;
    int i = 0;
    while (tokens[i] != NULL)
    {
        if (strcmp(tokens[i], "|") == 0)
        {
            has_pipe = 1;
            break;
        }
        i++;
    }

    // Parse the command
    struct node_type_master *master_node;
    if (has_pipe)
        {
		master_node = parse_advanced_command(tokens);
		set_pipe_operator(master_node);

		// print_master(master_node);
		if(fork() == 0)
			execute_pipe_command(master_node->root_nodes[0]);
		waitpid(-1, &status, 0);
		//print_master(master_node);
		free_ast(master_node);
		}
		//have parse_advanced_command return smthing for execution, instead of executing straight away
    else
    {
        struct node_s *cmd = parse_simple_command(tokens);

		i = 0;
		while(i == 0)
		{
			if(!cmd)
				break;
			do_simple_command_former(cmd);
			free_node_tree(cmd);
			free(tokens);
			i++;
		}
        // free_node(cmd);
    }
    // free(tokens);
    return 1;
}
