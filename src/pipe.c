/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:59:48 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/15 15:57:55 by lmangall         ###   ########.fr       */
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

int	exec_pipe_redir(struct s_node *node, t_data *data)
{
// printf("exec_pipe_redir\n");
	if (node->operator == PIPE)
		execute_pipe_command(node, data);
	else if (node->operator == NONE)
	{
// printf("exec_pipe_redir A\n");
		do_simple_command(node, data);
        free_node_tree_recursive(node);

// printf("exec_pipe_redir A2\n");
	}
	else
	{
// printf("exec_pipe_redir B\n");
		exec_redirection(node, data);
		}

printf("exec_pipe_redir returning\n");
	return(1);
}

void	first_child(struct s_node *node, int pipe_fd[2], t_data *data)
{
	close(STDOUT_FILENO);
	dup(pipe_fd[1]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exec_pipe_redir(node, data);
	// exit(get_var(data, "?"));
}

void	second_child(struct s_node *node, int pipe_fd[2], t_data *data)
{
	close(STDIN_FILENO);
	dup(pipe_fd[0]);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	exec_pipe_redir(node, data);
	free_node_tree(node);
	// exit(get_var(data, "?"));
}

void	run_second_child_process(struct s_node *node, 
							int pipe_fd[2], pid_t child_pid1, t_data *data)
{
	pid_t	child_pid2;
	int		status;

	status = 0;
	child_pid2 = fork();
	if (child_pid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (child_pid2 == 0) 
		second_child(node->next_sibling, pipe_fd, data);
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		waitpid(child_pid1, &status, 0);
		waitpid(child_pid2, &status, 0);
		update_status(status, data);
		free_node_tree_recursive(node);
		free_string_array(data->tokens);
		exit(get_var(data, "?"));
	}
}

void	execute_pipe_command(struct s_node *node, t_data *data)
{
	pid_t	child_pid1;
	int		pipe_fd[2];

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
		run_second_child_process(node, pipe_fd, child_pid1, data);
	}
}
