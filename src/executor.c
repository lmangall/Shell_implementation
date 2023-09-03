/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:23:59 by lmangall          #+#    #+#             */
/*   Updated: 2023/09/03 20:10:29 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/libft/src/libft.h"
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
#include "../include/free.h"

int ft_fork(struct node_type_master *master_node, int *end, int fd_in, struct node_s *current_node, int *fd)
{
    (void)master_node;

    if (current_node->prev_sibling && fd[0] != -1)
        fd_in = fd[0];

    if (current_node->type == NODE_COMMAND && current_node->first_child)
    {
        do_simple_command(current_node);
    }
    else if (current_node->type == NODE_SPECIAL)
    {
        pipe(fd);
        current_node->pipes = 2;
        current_node->pid = malloc(sizeof(int) * 2);
        current_node->pid[0] = fork();
        if (current_node->pid[0] == 0)
        {
            close(fd[0]);
            dup2(fd_in, STDIN_FILENO);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            do_simple_command(current_node->first_child);
            exit(EXIT_SUCCESS);
        }
        else
        {
            current_node->pid[1] = fork();
            if (current_node->pid[1] == 0)
            {
                close(fd[1]);
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
                if (current_node->first_child->next_sibling)
                    do_simple_command(current_node->first_child->next_sibling);
                exit(EXIT_SUCCESS);
            }
            else
            {
                close(fd[0]);
                close(fd[1]);
                if (current_node->next_sibling == NULL)
                    end[1] = 1;
            }
        }
    }
    return (0);
}

int pipe_wait(int *pid, int pipes, int *end)
{
    int i;
    int status;
    int exit_status = 0;

    i = 0;
    while (i < pipes)
    {
        waitpid(pid[i], &status, 0);
        if (WIFEXITED(status))
        {
            exit_status = WEXITSTATUS(status);
        }
        i++;
    }
    if (end[1])
        close(end[0]);
    return (exit_status);
}

int executor(struct node_type_master *master_node)
{
    struct node_s *current_node;
    int fd_in;
    int end[2] = {0, 0};
    int fd[2] = {-1, -1};

    current_node = master_node->root_nodes[0];
    fd_in = STDIN_FILENO;
    while (current_node)
    {
        if (current_node->type == NODE_SPECIAL)
        {
            ft_fork(master_node, end, fd_in, current_node, fd);
        }
        else if (current_node->type == NODE_COMMAND)
        {
            do_simple_command(current_node);
        }
        current_node = current_node->next_sibling;
    }
    pipe_wait(current_node->prev_sibling->pid, current_node->prev_sibling->pipes, end);
    return (0);
}












//below is 
//do_simple_command 
// do_simple_command_former
//search_path
//do_exec_cmd



// a function that uses do_exec_cmd to execute a simple command
int do_simple_command(struct node_s *node)
{
	struct node_s *child = node->first_child;
	if(!child)
		return 0;

	int argc = 0;
	long max_args = 255;
	char *argv[max_args+1];/* keep 1 for the terminating NULL arg */
	char *str;

	if(child)
	while(child && argc < max_args)
	{
		str = child->str;
		argv[argc] = malloc(strlen(str)+1);
		
	if(!argv[argc])
		{
			free_argv(argc, argv);
			return 0;
		}
		ft_strlcpy(argv[argc], str, strlen(str)+1);
		// maybe there should be a guard if next_sibling is inexistant
			child = child->next_sibling;
		argc++;
	}
		argv[argc] = NULL;

		
for (int i = 0; argv[i] != NULL; i++)
{
// printf("argv[%d]: %s\n", i, argv[i]);
}


		do_exec_cmd(argv);
		free_argv(argc, argv);
		return 0;

}



int do_simple_command_former(struct node_s *node)
{
	if(!node)
		return 0;
	struct node_s *child = node->first_child;
	if(!child)
	return 0;
	
	int argc = 0;
	long max_args = 255;
	char *argv[max_args+1];/* keep 1 for the terminating NULL arg */
	char *str;

	while(child)
	{
		str = child->str;
		argv[argc] = malloc(strlen(str)+1);
		
	if(!argv[argc])
		{
			free_argv(argc, argv);
			return 0;
		}
		
	strcpy(argv[argc], str);
		if(argc >= max_args)
		{
			break;
		}
		child = child->next_sibling;
		argc++;
	}
	argv[argc] = NULL;
	
	//loop to print argv
	int i = 0;
	while (i < argc)
		i++;



	pid_t child_pid = 0;
	if((child_pid = fork()) == 0)
	{

		do_exec_cmd(argv);
		fprintf(stderr, "error: failed to execute command: %s\n", 
				strerror(errno));
		if(errno == ENOEXEC)
		{
			exit(126);
		}
		else if(errno == ENOENT)
		{
			exit(127);
		}
		else
		{
			exit(EXIT_FAILURE);
		}
	}
	else if(child_pid < 0)
	{
		fprintf(stderr, "error: failed to fork command: %s\n", 
				strerror(errno));
		return 0;
	}
	int status = 0;
	waitpid(child_pid, &status, 0);
	free_argv(argc, argv);
	
	return 1;
}



//retrieve and returns the correct path of a command (given as a str)
char *search_path(char *cmd)
{
	char *paths = getenv("PATH");
	char **paths_arr = ft_split(paths, ':');
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths_arr, "/");
		command = ft_strjoin(tmp, cmd);
		//free(tmp); => this free was causing a problem :
		// pointer being freed was not allocated
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths_arr++;
	}
	errno = ENOENT;
	return NULL;
}

// takes an argument list (`**argv`) suitable for executing
//The zeroth argument, argv[0], contains the name of the command
int do_exec_cmd(char **argv)
{
    if(strchr(argv[0], '/'))
        execv(argv[0], argv);
    else
    {
        char *path = search_path(argv[0]);
        if(!path)
        {
            return 0;
        }
// printf("\033[1;31mExecuting command: %s\033[0m\n", path);
        execv(path, argv);
// printf("\033[1;33mNOT GETTIN PRINTED\033[0m\n");
        free(path);
    }
    return 0;
}
