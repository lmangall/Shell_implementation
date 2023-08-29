/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:22:39 by lmangall          #+#    #+#             */
/*   Updated: 2023/08/29 18:59:54 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../include/shell.h"
#include "../include/lexer.h"
#include "../include/vars.h"
#include "../include/parser.h"
#include "../include/executor.h"
#include "../include/expander.h"
#include "../include/minishell.h"
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


int main(int argc, char **argv)
{
    char *line;
    int status;
    t_data data;
    data.paths = NULL;
    data.envp = NULL;
	

	init_vars(&data);
    // print_vars(&data);
    set_var(&data, "SUPERVARIABLE", "Leonardo da Vinci");
    // print_vars(&data);
    export_var(&data, "SUPERVARIABLE");
    // print_exported_vars(&data);
    // unset_var(&data, "SUPERVARIABLE");
    // print_vars(&data);
	
	// data = malloc(sizeof(t_data)); // Allocate memory for data
    // if (!data) 
	// {
	// 	fprintf(stderr, "lsh: allocation error\n");
	// 	exit(EXIT_FAILURE);
	// }
		
	status = 1;
    while(status)
    {
        line = readline(SHELL_PROMPT);		
	if(line[0] !=  '\0')
		{
		add_history(line);
        status = parse_and_execute(line, &data);
		}
		// if (ft_strcmp(line, "history") == 0)
		// 	display_history();
		if (ft_strcmp(line, "exit") == 0)
			status = 0;
	}

    return EXIT_SUCCESS;
}

int parse_and_execute(char *line, t_data *data)
{

	char **tokens;
	tokens = lexer(line);
	free(line);
	struct node_s *cmd = parse_simple_command(tokens);
	struct node_s *cpy = malloc(sizeof(struct node_s));


	cpy = cmd->first_child;
    // while (cpy)
    // {
    //     // printf("mark 2\n");
    //     // printf("cpy->str: %s\n", cpy->str);
    //     expansion(cpy, data);
	// 	// print_vars(data);
	// 	printf("\033[0;32mdata->num_vars = %d\033[0m\n", data->num_vars);
	// 	expansion_set_var(cpy, data);
	// 	print_vars(data);
	// 	// print nbr of VARS printf("\033[0;32mdata->num_vars = %d\033[0m\n", data->num_vars);
        cpy = cpy->next_sibling;
    // }
    //     free_node_tree(cpy);

    // First, expand all variables in the nodes
    // while (cpy)
    // {
    //     expansion(cpy, data);
    //     cpy = cpy->next_sibling;
    // }

    // Then, go through the expanded nodes to set variables
    // cpy = cmd->first_child;
    // while (cpy)
    // {
        // expansion_set_var(cpy, data);
    //     cpy = cpy->next_sibling;
    // }


	int i = 0;
    while(i == 0)
    {
        if(!cmd)
			break;
        do_simple_command(cmd);
        free_node_tree(cmd);
		free(tokens);
		i++;
    }
    return 1;
}