/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:59:48 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/09 15:48:42 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/executor.h"
#include "../include/free.h"
#include "../include/main.h"
#include "../include/parser_nodes.h"
#include "../include/pipe.h"
#include "../include/redirect.h"
#include "../lib/libft/src/libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

void	exec_pipe_redir(struct node_s *node, t_data *data)
{
	if (node->operator == PIPE)
		execute_pipe_command(node, data);
	else if (node->operator == NONE)
		do_simple_command(node, data);
	// maybe here we should take care of the exit code
	else
		exec_redirection(node, data);
}

void	first_child(struct node_s *node, int pipe_fd[2], t_data *data)
{
	close(STDOUT_FILENO);
	dup(pipe_fd[1]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exec_pipe_redir(node, data);
	exit(EXIT_SUCCESS);
}

void	second_child(struct node_s *node, int pipe_fd[2], t_data *data)
{
	close(STDIN_FILENO);
	dup(pipe_fd[0]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exec_pipe_redir(node, data);
	free_node_tree(node);
	exit(EXIT_SUCCESS);
}

void	execute_pipe_command(struct node_s *node, t_data *data)
{
	pid_t	child_pid1;
	pid_t	child_pid2;
	int		pipe_fd[2];
	int		status;

	node->operator = NONE;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	child_pid1 = fork();
	if (child_pid1 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid1 == 0)
		first_child(node, pipe_fd, data);
	else
	{
		child_pid2 = fork();
		if (child_pid2 == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (child_pid2 == 0)
		{
			second_child(node->next_sibling, pipe_fd, data);
		}
		else
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			waitpid(child_pid1, &status, 0);
			waitpid(child_pid2, &status, 0);
			// exit(EXIT_SUCCESS);
		}
	}
}
