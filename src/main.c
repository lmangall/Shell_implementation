/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:22:39 by lmangall          #+#    #+#             */
/*   Updated: 2023/08/24 11:57:25 by lmangall         ###   ########.fr       */
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
#include "../include/minishell.h"
#include "../lib/libft/src/libft.h"
#include <readline/readline.h>
#include <readline/history.h>


int main(int argc, char **argv)
{
    char *line;
    int status;
	t_data *data;
	init_vars();
	set_vars("$SUPERVARIABLE", "Leonardo da Vinci");
	//print_vars();
	unset_vars("SUPERVARIABLE");

	data = malloc(sizeof(t_data)); // Allocate memory for data
    if (!data) 
	{
		fprintf(stderr, "lsh: allocation error\n");
		exit(EXIT_FAILURE);
	}
		
	status = 1;
    while(status)
    {
        line = readline(SHELL_PROMPT);		
        add_history(line);
		init_data(data);
        status = parse_and_execute(line);
        free(line);
    }

    return EXIT_SUCCESS;
}

int parse_and_execute(char *line)
{
	char **tokens;
	
	tokens = lexer(line);
	free(line);
	struct node_s *cmd = parse_simple_command(tokens);
	expansion(cmd);
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