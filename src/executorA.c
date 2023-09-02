/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executorA.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:23:59 by lmangall          #+#    #+#             */
/*   Updated: 2023/09/02 14:48:25 by lmangall         ###   ########.fr       */
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

static void free_command_str(struct node_s *node)
{
    if (node == NULL)
    {
        return;
    }

    if (node->type == NODE_COMMAND)
    {
        free(node->str);
    }

    struct node_s *child = node->first_child;
    while (child != NULL)
    {
        free_command_str(child);
        child = child->next_sibling;
    }
}

static void free_master_command_str(struct node_type_master *master_node)
{
    if (master_node == NULL)
    {
        return;
    }

    for (int i = 0; i < master_node->nbr_root_nodes; i++)
    {
        free_command_str(master_node->root_nodes[i]);
    }
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

// static void print_pipe_write_end(int pipe_fd)
// {
//     char buffer[1024];
//     ssize_t bytes_read;

//     while ((bytes_read = read(pipe_fd, buffer, sizeof(buffer))) > 0)
//     {
//         printf("\033[1;35m"); // Set the color to purple
//         fwrite(buffer, 1, bytes_read, stdout);
//         printf("\033[0m"); // Reset the color
//     }

//     if (bytes_read == -1)
//     {
//         perror("read");
//         exit(EXIT_FAILURE);
//     }
//     else if (bytes_read == 0)
//     {
//         fprintf(stderr, "Error: pipe_fd is not open or has been closed prematurely\n");
//         printf("void_pipe_write_end 0 bytes read\n");
// 		exit(EXIT_FAILURE);
//     }
// }

// Function to execute a pipe command
int execute_pipe_command(struct node_type_master *master_node)
{

free_master_command_str(master_node);//seems not to work perfcectly
	
    struct node_s *left = master_node->root_nodes[0];
    struct node_s *right = master_node->root_nodes[2];
	// printf("master_node->root_nodes[0]->first_child->str: %s\n", master_node->root_nodes[0]->first_child->str);
	// printf("master_node->root_nodes[2]->first_child->str: %s\n", master_node->root_nodes[2]->first_child->str);

	// printf("\n\n");

	//might be more important for firstC not to point to nextS if there is none
	free(master_node->root_nodes[0]->first_child->next_sibling->str);
	
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        return -1;
    }

    pid_t left_pid;
	pid_t right_pid;
		
    // Fork the left side of the pipe
    left_pid = fork();
    if (left_pid == -1)
    {
        perror("fork");
        return -1;
    }
	
    else if (left_pid == 0) // Child process for left command
    {
// printf("\033[1;35m"); // Start writing in purple
// printf("in the else if (left_pid == 0) // Child process for left command\n");
        close(pipe_fd[0]); // Close the read end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to the write end of the pipe
// print_pipe_write_end(pipe_fd[1]);
		close(pipe_fd[1]); // Close the write end of the pipe
// printf("in the else if (left_pid == 0) // Child process for left command -2\n");

set_node_str(left->first_child, "ls");////////////    HARDCODED FOR DEBBUGING
        int status = do_simple_command(left);
// printf("status: %d\n", status);
// printf("\033[0m"); // End writing in purple
        exit(status);
    }

    // Fork the right side of the pipe
    right_pid = fork();
    if (right_pid == -1)
    {
        perror("fork");
        return -1;
    }
    else if (right_pid == 0) // Child process for right command
    {
// printf("\033[1;35m"); // Start writing in purple
// printf(" in the else if (right_pid == 0) // Child process for right command\n");
        close(pipe_fd[1]); // Close the write end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to the read end of the pipe
        close(pipe_fd[0]); // Close the read end of the pipe
// printf("in the else if (left_pid == 0) // Child process for left command  -2\n");
        int status = do_simple_command(right);
// printf("status: %d\n", status);
// printf("\033[0m"); // End writing in purple
        exit(status);
    }

    // Close both ends of the pipe in the parent process
    close(pipe_fd[0]);
// print_pipe_write_end(pipe_fd[1]);
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
printf("str: %s\n", str);
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
    printf("argv[%d]: %s\n", i, argv[i]);
}


		do_exec_cmd(argv);
		free_argv(argc, argv);
		return 0;

}