#ifndef SHELL_H
#define SHELL_H
#include "lexer.h"    /* struct token_s */
#include "shell.h"    /* struct token_s */

#define SHELL_PROMPT "\033[1;35mminishell$ \033[0m"

#define EOF             (-1)
#define ERRCHAR         ( 0)
#define INIT_SRC_POS    (-2)
struct source_s
{   
    char *buffer;       /* the input text */
    long bufsize;       /* size of the input text */
    long  curpos;       /* absolute char position in source */
};

//parser:
struct node_s *parse_simple_command(struct token_s *tok);

//shell:
int  parse_and_execute(struct source_s *src);
void print_prompt1(void);
void print_prompt2(void);
char *read_cmd(void);

#endif 