// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   executor copy.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/09 18:23:59 by lmangall          #+#    #+#             */
// /*   Updated: 2023/09/01 21:09:44 by lmangall         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../lib/libft/src/libft.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <errno.h>
// #include <sys/stat.h>
// #include <sys/wait.h>
// #include "../include/shell.h"
// #include "../include/node.h"
// #include "../include/executor.h"
// #include "../include/builtins.h"

// char *search_path(char *file)
// {
// 	char *paths = getenv("PATH");
// 	char **paths_arr = ft_split(paths, ':');
// 	char	*tmp;
// 	char	*command;

// 	while (*paths)
// 	{
// 		tmp = ft_strjoin(*paths_arr, "/");
// 		command = ft_strjoin(tmp, file);
// 		//free(tmp); => this free was causing a problem :
// 		// pointer being freed was not allocated
// 		if (access(command, 0) == 0)
// 			return (command);
// 		free(command);
// 		paths_arr++;
// 	}
// 	errno = ENOENT;
// 	return NULL;
// }

// int do_exec_cmd(char **argv)
// {
// 	if(strchr(argv[0], '/'))
// 	{
// 		execv(argv[0], argv);
// 	}
// 	else
// 	{
// 		char *path = search_path(argv[0]);
// 		if(!path)
// 		{
// 			return 0;
// 		}
// 		execv(path, argv);
// 		printf("\033[1;33mNOT GETTIN PRINTED\033[0m\n");
// 	free(path);
// 	}
// 	return 0;
// }

// static inline void free_argv(int argc, char **argv)
// {
// 	if(!argc)
// 		return;
// 	while(argc--)
// 	free(argv[argc]);
// }

// int do_complex_command(struct node_type_master *master_node)

	










// // Function to execute a command sequence
// int execute_command_sequence(struct node_s *sequence)
// {
//     int status = 0;
//     struct node_s *current = sequence->first_child;
//     while (current != NULL)
//     {
//         status = execute_simple_command(current);
//         current = current->next_sibling;
//     }
//     return status;
// }

// // Function to execute a pipe command
// int execute_pipe_command(struct node_type_master *master_node)
// {
// 	int status = 0;
// 	int i = 0;

// 	// Loop through the root nodes and execute them
// 	while (master_node->root_nodes[i] != NULL)
// 	{
// 		struct node_s *root_node = master_node->root_nodes[i];

// 		if (root_node->type == NODE_VAR
// 		{
// 			status = execute_simple_command(root_node);
// 		}
// 		else if (root_node->type == NODE_SPECIAL && strcmp(root_node->str, "|") == 0)
// 		{
// 			status = execute_pipe_command(root_node);
// 		}

// 		i++;
// 	}

// 	return status;
// }


// {
//     struct node_s *left = pipe_cmd->first_child;
//     struct node_s *right = left->next_sibling;

//     int pipe_fd[2];
//     if (pipe(pipe_fd) == -1)
//     {
//         perror("pipe");
//         return -1;
//     }

//     pid_t left_pid, right_pid;

//     // Fork the left side of the pipe
//     left_pid = fork();
//     if (left_pid == -1)
//     {
//         perror("fork");
//         return -1;
//     }
//     else if (left_pid == 0) // Child process for left command
//     {
//         close(pipe_fd[0]); // Close the read end of the pipe
//         dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to the write end of the pipe
//         close(pipe_fd[1]); // Close the write end of the pipe

//         int status = execute_simple_command(left);
//         exit(status);
//     }

//     // Fork the right side of the pipe
//     right_pid = fork();
//     if (right_pid == -1)
//     {
//         perror("fork");
//         return -1;
//     }
//     else if (right_pid == 0) // Child process for right command
//     {
//         close(pipe_fd[1]); // Close the write end of the pipe
//         dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to the read end of the pipe
//         close(pipe_fd[0]); // Close the read end of the pipe

//         int status = execute_simple_command(right);
//         exit(status);
//     }

//     // Close both ends of the pipe in the parent process
//     close(pipe_fd[0]);
//     close(pipe_fd[1]);

//     // Wait for both child processes to finish
//     int left_status, right_status;
//     waitpid(left_pid, &left_status, 0);
//     waitpid(right_pid, &right_status, 0);

//     return WEXITSTATUS(right_status);
// }

// // Function to execute a complex command
// int do_complex_command(struct node_type_master *master_node)
// {
//     int status = 0;
//     int i = 0;

//     // Loop through the root nodes and execute them
//     while (master_node->root_nodes[i] != NULL)
//     {
//         struct node_s *root_node = master_node->root_nodes[i];

//         if (root_node->type == NODE_COMMAND)
//         {
//             status = execute_simple_command(root_node);
//         }
//         else if (root_node->type == NODE_SPECIAL && strcmp(root_node->str, "|") == 0)
//         {
//             status = execute_pipe_command(root_node);
//         }

//         i++;
//     }

//     return status;
// }