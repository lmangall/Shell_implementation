/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:22:39 by lmangall          #+#    #+#             */
/*   Updated: 2023/09/02 23:26:17 by lmangall         ###   ########.fr       */
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
    char **tokens = lexer(line);
    free(line);

	(void) data;

    // Check if there is a pipe in the command
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
        master_node = parse_advanced_command(tokens);
    else
    {
        struct node_s *cmd = parse_simple_command(tokens);
        master_node = create_master_node(cmd);
        // free_node(cmd);
    }

    // Execute the command
    if (master_node)
    {
        execute_pipe_command(master_node);
        // free_master(master_node);
    }

    // free(tokens);
    return 1;
}
