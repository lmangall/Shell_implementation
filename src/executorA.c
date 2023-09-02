/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executorA.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:23:59 by lmangall          #+#    #+#             */
/*   Updated: 2023/09/02 23:41:32 by lmangall         ###   ########.fr       */
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

// static void free_command_str(struct node_s *node)
// {
//     if (node == NULL)
//     {
//         return;
//     }

//     if (node->type == NODE_COMMAND)
//     {
//         free(node->str);
//     }

//     struct node_s *child = node->first_child;
//     while (child != NULL)
//     {
//         free_command_str(child);
//         child = child->next_sibling;
//     }
// }

// static void free_master_command_str(struct node_type_master *master_node)
// {
//     if (master_node == NULL)
//     {
//         return;
//     }

//     for (int i = 0; i < master_node->nbr_root_nodes; i++)
//     {
//         free_command_str(master_node->root_nodes[i]);
//     }
// }






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



static inline void free_argv(int argc, char **argv)
{
	if(!argc)
		return;
	while(argc--)
	free(argv[argc]);
}
void	first_child(struct node_s *node, int pipe_fd[2])
{
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[0]);
    do_simple_command(node);
}

void	second_child(struct node_s *node, int pipe_fd[2])
{
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[1]);
    do_simple_command(node);
}

int execute_pipe_command(struct node_type_master *master_node)
{
    int pipe_fd[2];
    pid_t pid1, pid2;
    int status;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        return EXIT_FAILURE;
    }
    else if (pid1 == 0)
    {
		set_node_str(master_node->root_nodes[0]->first_child, "ls"); // !!!
        first_child(master_node->root_nodes[0], pipe_fd);
        // exit(EXIT_SUCCESS);
    }

    pid2 = fork();
    if (pid2 == -1)
    {
        perror("fork");
        return EXIT_FAILURE;
    }
    else if (pid2 == 0)
    {
		set_node_str(master_node->root_nodes[2]->first_child, "wc");// !!!
        second_child(master_node->root_nodes[2], pipe_fd);
        // exit(EXIT_SUCCESS);
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);

    return WEXITSTATUS(status);
}


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
	// while(child)
	{
		str = child->str;
		argv[argc] = malloc(strlen(str)+1);
		
	if(!argv[argc])
		{
			free_argv(argc, argv);
			return 0;
		}
// printf("str: %s\n", str);
	strcpy(argv[argc], str);
		// if(argc >= max_args)
		// {
		// 	break;     //that doesn't work in an if statement
		// }

//commentend so we do one command without args
//if you uncomment be carefull checking that 
//there is no pointer to next_sibling pointing at wrong place or such...
		// child = child->next_sibling;///////causes problems
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