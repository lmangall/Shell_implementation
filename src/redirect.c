/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:00:24 by lmangall          #+#    #+#             */
/*   Updated: 2023/12/12 13:53:12 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/executor.h"
#include "../include/free.h"
#include "../include/node.h"
#include "../include/pipe.h"
#include "../include/redirect.h"
#include "../include/shell.h"
#include "../include/signals.h"
#include "../lib/libft/src/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

// #if 1
// extern long long g_exit_status;

bool	streq(char *str1, char *str2)
{
	size_t	i;

	if ((str1 && !str2) || (!str1 && str2))
		return (false);
	i = 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (false);
		i += 1;
	}
	return (true);
}

void	redirect_input_until(struct node_s *node)
{
	char	*buff;
	int		fd[2];

	signal(SIGINT, handle_ctrl_c_heredoc);
	pipe(fd);
	while (1)
	{
		buff = readline("> ");
		if (!buff)
			break ;
		if (streq(buff, node->next_sibling->first_child->str))
			break ;
		ft_putendl_fd(buff, fd[1]);
	}
	signal(SIGINT, handle_ctrl_c);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(buff);
}

void	redirect_input(struct node_s *node)
{
	int		in_file;
	char	*error_msg_prefix;

	if (node->next_sibling->first_child->str)
	{
		while (node->next_sibling->operator== RDR_INPUT)
			node = node->next_sibling;
		while (node->next_sibling->operator== RDR_INPUT)
			node = node->next_sibling;
		if (access(node->next_sibling->first_child->str, F_OK) == 0)
		{
			in_file = open(node->next_sibling->first_child->str, O_RDONLY,
					0666);
			dup2(in_file, STDIN_FILENO);
		}
		else
		{
			error_msg_prefix = ft_strjoin("minishell: ",
					node->next_sibling->first_child->str);
			perror(error_msg_prefix);
			free(error_msg_prefix);
			// g_exit_status = 2;
			exit(EXIT_FAILURE);
		}
	}
}

void	redirect_output(struct node_s *node)
{
	close(STDOUT_FILENO);
	while (node->next_sibling->operator== RDR_OUT_REPLACE
		|| node->next_sibling->operator== RDR_OUT_APPEND)
	{
		if (node->operator== RDR_OUT_REPLACE)
			open(node->next_sibling->first_child->str,
				O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (node->operator== RDR_OUT_APPEND)
			open(node->next_sibling->first_child->str,
				O_WRONLY | O_APPEND | O_CREAT, 0666);
		node = node->next_sibling;
		close(1);
	}
	if (node->operator== RDR_OUT_REPLACE)
		open(node->next_sibling->first_child->str, O_WRONLY | O_TRUNC | O_CREAT,
			0666);
	else if (node->operator== RDR_OUT_APPEND)
		open(node->next_sibling->first_child->str,
			O_WRONLY | O_APPEND | O_CREAT, 0666);
}

void	exec_redirection(struct node_s *node, t_data *data)
{
	struct node_s	*temp;

	temp = node;
	if (node->operator== RDR_INPUT)
		redirect_input(node);
	else if (node->operator== RDR_INPUT_UNTIL)
		redirect_input_until(node);
	else
		redirect_output(node); // mark
	temp->operator= NONE;
	while (node->operator != NONE && node->operator != PIPE)
		node = node->next_sibling; // next will be output.txt
	if (node->operator == NONE)
		exec_pipe_redir(temp, data);
	else
		execute_pipe_command(node, data);
}

// struct node_s *identify_redirection(struct node_s *node)
// {
// 	while (node->operator != NONE)
// 	{
// 		if (node->operator == RDR_INPUT)
// 			return (node);
// 		node = node->next_sibling;
// 	}
// 	return (NULL);
// }

// #endif