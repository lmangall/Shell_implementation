/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:00:24 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/11 16:08:52 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/executor.h"
#include "../include/free.h"
#include "../include/parser_nodes.h"
#include "../include/pipe.h"
#include "../include/redirect.h"
#include "../include/main.h"
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

void	redirect_input_until(struct s_node *node)
{
	char	*buff;
	int		fd[2];

	signal(SIGINT, handle_ctrl_c_heredoc);
	pipe(fd);
	while (1)
	{
		signal(SIGQUIT, handle_ctrl_d);
		buff = readline("> ");
		if (!buff)
			break ;
		if (streq(buff, node->next_sibling->first_child->str))
			break ;
		ft_putendl_fd(buff, fd[1]);
	}
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	free(buff);
}

void	redirect_input(struct s_node *node)
{
	int		in_file;

	if (node->next_sibling->first_child->str)
	{
		while (node->next_sibling->operator == RDR_INPUT)
			node = node->next_sibling;
		while (node->next_sibling->operator == RDR_INPUT)
			node = node->next_sibling;
		if (access(node->next_sibling->first_child->str, F_OK) == 0)
		{
			in_file = open(node->next_sibling->first_child->str, O_RDONLY,
					0666);
			dup2(in_file, STDIN_FILENO);
		}
		else
		{
			printf("No such file or directory\n");
			exit(1);
		}
	}
}

void	redirect_output(struct s_node *node)
{
	close(STDOUT_FILENO);
	while (node->next_sibling->operator == RDR_OUT_REPLACE
		|| node->next_sibling->operator == RDR_OUT_APPEND)
	{
		if (node->operator == RDR_OUT_REPLACE)
			open(node->next_sibling->first_child->str,
				O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (node->operator == RDR_OUT_APPEND)
			open(node->next_sibling->first_child->str,
				O_WRONLY | O_APPEND | O_CREAT, 0666);
		node = node->next_sibling;
		close(1);
	}
	if (node->operator == RDR_OUT_REPLACE)
		open(node->next_sibling->first_child->str, O_WRONLY | O_TRUNC | O_CREAT,
			0666);
	else if (node->operator == RDR_OUT_APPEND)
		open(node->next_sibling->first_child->str,
			O_WRONLY | O_APPEND | O_CREAT, 0666);
}

void	exec_redirection(struct s_node *node, t_data *data)
{
	struct s_node	*temp;

	temp = node;
	if (node->operator == RDR_INPUT)
		redirect_input(node);
	else if (node->operator == RDR_INPUT_UNTIL)
		redirect_input_until(node);
	else
		redirect_output(node);
	temp->operator = NONE;
	while (node->operator != NONE && node->operator != PIPE)
		node = node->next_sibling;
	if (node->operator == NONE)
		exec_pipe_redir(temp, data);
	else
		execute_pipe_command(node, data);
}
