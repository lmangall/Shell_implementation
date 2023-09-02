/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_draft2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:23:59 by lmangall          #+#    #+#             */
/*   Updated: 2023/09/02 20:39:30 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "../include/shell.h"
#include "../include/node.h"
#include "../include/executor.h"
#include "../include/builtins.h"

char *search_path(char *cmd)
{
    char *paths = getenv("PATH");
    char **paths_arr = ft_split(paths, ':');
    char *tmp;
    char *command;

    while (*paths)
    {
        tmp = ft_strjoin(*paths_arr, "/");
        command = ft_strjoin(tmp, cmd);
        if (access(command, 0) == 0)
            return (command);
        free(command);
        paths_arr++;
    }
    return NULL;
}

int do_exec_cmd(char **argv)
{
    if (strchr(argv[0], '/'))
        execv(argv[0], argv);
    else
    {
        char *path = search_path(argv[0]);
        if (!path)
        {
            return 0;
        }
        execv(path, argv);
        free(path);
    }
    return 0;
}

static inline void free_argv(int argc, char **argv)
{
    if (!argc)
        return;
    while (argc--)
        free(argv[argc]);
}

void execute_command(struct node_s *node)
{
    struct node_s *child = node->first_child;
    if (!child)
        return;

    int argc = 0;
    long max_args = 255;
    char *argv[max_args + 1];
    char *str;

    while (child)
    {
        str = child->str;
        argv[argc] = malloc(strlen(str) + 1);

        if (!argv[argc])
        {
            free_argv(argc, argv);
            return;
        }

        strcpy(argv[argc], str);
        argc++;
        child = child->next_sibling;
    }

    argv[argc] = NULL;

    do_exec_cmd(argv);
    free_argv(argc, argv);
}

int execute_pipe_command(struct node_type_master *master_node)
{
printf("execute_pipe_command\n");
    int pipe_fd[2];
    pid_t pid;
    int status;

    for (int i = 0; i < 2; i++)
    {
printf("1i: %d\n", i);
        if (pipe(pipe_fd) == -1)
        {
            perror("pipe");
            return EXIT_FAILURE;
        }

        pid = fork();
        if (pid == -1)
        {
printf("1pid: %d\n", pid);
            perror("fork");
            return EXIT_FAILURE;
        }
        else if (pid == 0)
        {
printf("2pid: %d\n", pid);
            if (i != 0)
            {
printf("2i: %d\n", i);
                dup2(pipe_fd[0], STDIN_FILENO);
                close(pipe_fd[1]);
            }
            if (i != master_node->nbr_root_nodes - 1)
            {
printf("3i: %d\n", i);
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
            }
            execute_command(master_node->root_nodes[i]);
            exit(EXIT_SUCCESS);
        }
printf("i: %d\n", i);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
    }

    for (int i = 0; i < master_node->nbr_root_nodes; i++)
    {
        wait(&status);
    }

    return WEXITSTATUS(status);
}