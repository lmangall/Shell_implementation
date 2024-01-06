#ifndef SHELL_H
#define SHELL_H
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../include/lexer.h"
#include "../include/vars.h"
#include "../include/parser.h"
#include "../include/executor.h"
#include "../lib/libft/src/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

#define SHELL_PROMPT "\033[1;35mminishell$ \033[0m"

#define EOF             (-1)
#define ERRCHAR         ( 0)
#define INIT_SRC_POS    (-2)


/**
 * @brief Parse and execute a given command line.
 *
 * This function parses the command line, determines the type of command,
 * and delegates the execution to the appropriate handler function.
 *
 * @param line The input command line to be parsed and executed.
 * @param data A pointer to the data structure containing relevant information.
 * @return 1 on successful execution.
 */
int parse_and_execute(char *line, t_data *data);


#endif 