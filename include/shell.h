#ifndef SHELL_H
#define SHELL_H
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../include/shell.h"
#include "../include/lexer.h"
#include "../include/vars.h"
#include "../include/parser.h"
#include "../include/executor.h"
#include "../include/expander.h"
#include "../lib/libft/src/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

#define SHELL_PROMPT "\033[1;35mminishell$ \033[0m"

#define EOF             (-1)
#define ERRCHAR         ( 0)
#define INIT_SRC_POS    (-2)

//parser:
struct node_s *parse_simple_command(char **tokens);

int parse_and_execute(char *line, t_data *data);

void print_prompt1(void);
void print_prompt2(void);
char *read_cmd(void);

#endif 