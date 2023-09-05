// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   executor.c                                         :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/09 18:23:59 by lmangall          #+#    #+#             */
// /*   Updated: 2023/09/01 20:57:50 by lmangall         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

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

extern long long g_exit_status;       //   => get rid of this global var

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
        execv(path, argv);
        free(path);
    }
    return 0;
}

void exec_pipe_redir(struct node_s *node)
{
	 ft_putnbr_fd(node->operator, 2);

	if(node->first_child->type == NODE_SPECIAL)
		execute_pipe_command(node);
//	if(node->first_child->type == NODE_COMMAND)
	else
		do_simple_command(node);
	// exit(g_exit_status);
}


void	first_child(struct node_s *node, int pipe_fd[2])
{

	close(STDOUT_FILENO);
    dup(pipe_fd[1]);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    exec_pipe_redir(node);
}

void	second_child(struct node_s *node, int pipe_fd[2])
{
	close(STDIN_FILENO);
    dup(pipe_fd[0]);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    exec_pipe_redir(node);
}

//for multiple pipes, second child will get back here after execution
void execute_pipe_command(struct node_s *node)
{
    pid_t child_pid;
    int pipe_fd[2];
    int status;

	node->operator = NONE;
	node->first_child->type = NODE_COMMAND;
	// ft_putnbr_fd(node->operator, 2);

	if (pipe(pipe_fd) == -1)
		{
		//panic(data, PIPE_ERR, EXIT_FAILURE);
		ft_putstr_fd("pipe error\n", 2);
		}
	child_pid = fork();
	if (child_pid == -1)
		{
		//panic(data, FORK_ERR, EXIT_FAILURE);
		ft_putstr_fd("pipe error\n", 2);
		}
	if (child_pid == 0)
		first_child(node, pipe_fd);

	// ft_putstr_fd("at end of execute_pipe_command\n", 2);	
	//ft_putstr_fd("\n", 2);	

	// if (node->next_sibling->operator == PIPE)
		second_child(node->next_sibling, pipe_fd);
	// second_child(node->next_sibling->next_sibling, pipe_fd);

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(child_pid, &status, 0);
	// g_exit_status = status;

}


// a function that uses do_exec_cmd to execute a simple command
int do_simple_command(struct node_s *root_node)
{
	struct node_s *child = root_node->first_child;
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

		
	// for (int i = 0; argv[i] != NULL; i++)
	// {
	// // printf("argv[%d]: %s\n", i, argv[i]);
	// }
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