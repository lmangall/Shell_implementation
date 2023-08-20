#ifndef SHELL_H
#define SHELL_H
#include "lexer.h"    /* struct token_s */
#include "shell.h"    /* struct token_s */

#define SHELL_PROMPT "\033[1;35mminishell$ \033[0m"

#define EOF             (-1)
#define ERRCHAR         ( 0)
#define INIT_SRC_POS    (-2)

//parser:
struct node_s *parse_simple_command(char *line);

//shell:
int  parse_and_execute(char *line);
void print_prompt1(void);
void print_prompt2(void);
char *read_cmd(void);

#endif 