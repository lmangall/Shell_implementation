/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:22:39 by lmangall          #+#    #+#             */
/*   Updated: 2023/08/20 12:44:19 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../include/shell.h"
#include "../include/lexer.h"
#include "../include/executor.h"
#include "../include/minishell.h"
#include "../lib/libft/src/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

struct token_s eof_token = 
{
    .text_len = 0,
};

int main(int argc, char **argv)
{
    char *line;
    int status = 1;

    while(status)
    {
        line = readline(SHELL_PROMPT);
        if(!line)
            break;
        add_history(line);
        status = parse_and_execute(line);
        free(line);
    }

    return EXIT_SUCCESS;
}

int parse_and_execute(char *line)
{
    // skip_white_spaces(src);
    struct token_s *tok = tokenize(line);
	
    if(tok->text_len == 0 && tok->text == NULL && tok->src == NULL)
		{
			printf("parse_and_execute----0\n");
			return 0;
		}
    while(tok && (tok->text_len != 0 && tok->text != NULL))
    {
        struct node_s *cmd = parse_simple_command(line);
        if(!cmd)
			break;
        do_simple_command(cmd);
        free_node_tree(cmd);
        tok = tokenize(line);
    }
    return 1;
}