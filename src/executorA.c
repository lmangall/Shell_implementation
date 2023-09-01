/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executorA.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:23:59 by lmangall          #+#    #+#             */
/*   Updated: 2023/09/01 22:26:59 by lmangall         ###   ########.fr       */
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

char *search_path(char *file)
{
	char *paths = getenv("PATH");
	char **paths_arr = ft_split(paths, ':');
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths_arr, "/");
		command = ft_strjoin(tmp, file);
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
		printf("\033[1;31mExecuting command: %s\033[0m\n", path);
        execv(path, argv);
        printf("\033[1;33mNOT GETTIN PRINTED\033[0m\n");
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

// Function to execute a pipe command
int execute_pipe_command(struct node_type_master *master_node)
{
    struct node_s *left = master_node->root_nodes[0];
    struct node_s *right = master_node->root_nodes[2];
	printf("master_node->root_nodes[0]->first_child->str: %s\n", master_node->root_nodes[0]->first_child->str);
	printf("master_node->root_nodes[2]->first_child->str: %s\n", master_node->root_nodes[2]->first_child->str);

	
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return -1;
    }

    pid_t left_pid;
	pid_t right_pid;
	
	printf("mark1\n");
	
    // Fork the left side of the pipe
    left_pid = fork();
    if (left_pid == -1)
    {
        perror("fork");
        return -1;
    }
    else if (left_pid == 0) // Child process for left command
    {
        close(pipe_fd[0]); // Close the read end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to the write end of the pipe
        close(pipe_fd[1]); // Close the write end of the pipe

        int status = do_simple_command(left);
		printf("after do_simple_command LEFT\n");
        exit(status);
    }

	printf("mark2\n");

    // Fork the right side of the pipe
    right_pid = fork();
    if (right_pid == -1)
    {
        perror("fork");
        return -1;
    }
    else if (right_pid == 0) // Child process for right command
    {
        close(pipe_fd[1]); // Close the write end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to the read end of the pipe
        close(pipe_fd[0]); // Close the read end of the pipe

        int status = do_simple_command(right);
		printf("after do_simple_command RIGHT\n");
        exit(status);
    }

	printf("mark3\n");

	printf("left_pid = %d\n", left_pid);

    // Close both ends of the pipe in the parent process
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both child processes to finish
    int left_status, right_status;
    waitpid(left_pid, &left_status, 0);
    waitpid(right_pid, &right_status, 0);

    return WEXITSTATUS(right_status);
}



// a function that uses do_exec_cmd to execute a simple command
int do_simple_command(struct node_s *node)
{
	printf("do_simple_command\n");


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

		do_exec_cmd(argv);
		free_argv(argc, argv);
		return 0;

}