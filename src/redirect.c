#include "../lib/libft/src/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "../include/shell.h"
#include "../include/pipe.h"
#include "../include/redirect.h"
#include "../include/node.h"
#include "../include/executor.h"
#include "../include/builtins.h"
#include "../include/free.h"

#if 1
//extern long long g_exit_status;

bool	streq(char *str1, char *str2)
{
	size_t	i;

	if ((str1 && !str2) || (!str1 && str2))
		return (false);
	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (false);
		i += 1;
	}
	return (true);
}

void redirect_input_until(struct node_s *node)
{
    char *buff;
    int fd[2];

    pipe(fd);
    while (1)
    {
        buff = readline("> ");
        if (streq(buff, node->next_sibling->first_child->str))
            break;
        ft_putendl_fd(buff, fd[1]);
    }
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    free(buff);
}

void redirect_input(struct node_s *node)
{
    int in_file;
    char *error_msg_prefix;

    if (node->next_sibling->first_child->str)
    {

        while (node->next_sibling->operator == RDR_INPUT)
            node = node->next_sibling;
        while (node->next_sibling->operator == RDR_INPUT)
            node = node->next_sibling;
        if (access(node->next_sibling->first_child->str, F_OK) == 0)
        {
            in_file = open(node->next_sibling->first_child->str, O_RDONLY, 0666);
            dup2(in_file, STDIN_FILENO);
			ft_putstr_fd("F_OK  for the file", 2);
        }
        else
        {
            error_msg_prefix = ft_strjoin("minishell: ", node->next_sibling->first_child->str);
            perror(error_msg_prefix);
            free(error_msg_prefix);
            // g_exit_status = 2;
            exit(EXIT_FAILURE);
        }
    }
}

void redirect_output(struct node_s *node)
{
    close(STDOUT_FILENO);
    while (node->next_sibling->operator == RDR_OUT_REPLACE || node->next_sibling->operator == RDR_OUT_APPEND)
    {
        if (node->operator == RDR_OUT_REPLACE)
            open(node->next_sibling->first_child->str, O_WRONLY | O_TRUNC | O_CREAT, 0666);
        else if (node->operator == RDR_OUT_APPEND)
            open(node->next_sibling->first_child->str, O_WRONLY | O_APPEND | O_CREAT, 0666);
        node = node->next_sibling;
        close(1);
    }
    if (node->operator == RDR_OUT_REPLACE)
        open(node->next_sibling->first_child->str, O_WRONLY | O_TRUNC | O_CREAT, 0666);

    else if (node->operator == RDR_OUT_APPEND)
        open(node->next_sibling->first_child->str, O_WRONLY | O_APPEND | O_CREAT, 0666);
}

void exec_redirection(struct node_s *node)
{
    struct node_s *temp;

    temp = node;
    if (node->operator == RDR_INPUT)
        redirect_input(node);
    else if (node->operator == RDR_INPUT_UNTIL)
        redirect_input_until(node);
    else
        redirect_output(node);     //mark
    temp->operator = NONE;
    while (node->operator != NONE && node->operator != PIPE)
        node = node->next_sibling;//next will be output.txt
    if (node->operator == NONE)
        exec_pipe_redir(temp);
    else
        execute_pipe_command(node);
}
#endif