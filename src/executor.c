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
#include "../include/pipe.h"
#include "../include/shell.h"
#include "../include/node.h"
#include "../include/executor.h"
#include "../include/builtins.h"
#include "../include/free.h"

// extern long long g_exit_status;       //   => get rid of this global var

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