/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 20:22:39 by lmangall          #+#    #+#             */
/*   Updated: 2023/08/19 20:30:00 by lmangall         ###   ########.fr       */
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

int main(int argc, char **argv)
{
    char *cmd;
        // if(strcmp(cmd, "exit\n") == 0)
        // {
        //     free(cmd);
        //     break;
        // }
        struct source_s src;
        src.buffer   = cmd;
        src.bufsize  = strlen(cmd);
        src.curpos   = INIT_SRC_POS;
        parse_and_execute(&src);        
		free(cmd);
    exit(EXIT_SUCCESS);
} 

int parse_and_execute(struct source_s *src)
{
    // skip_white_spaces(src);
    struct token_s *tok = tokenize(src);
    if(tok->text_len == 0 && tok->text == NULL && tok->src == NULL)
		return 0;
    while(tok && (tok->text_len != 0 && tok->text != NULL && tok->src != NULL))
    {
        struct node_s *cmd = parse_simple_command(tok);
        if(!cmd)
			break;
        do_simple_command(cmd);
        free_node_tree(cmd);
        tok = tokenize(src);
    }
    return 1;
}