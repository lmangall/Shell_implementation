/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:02:12 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/16 11:43:44 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/executor.h"
#include "../include/free.h"
#include "../include/main.h"
#include "../include/parser_nodes.h"
#include "../include/pipe.h"
#include "../include/signals.h"
#include "../include/redirect.h"
#include "../lib/libft/src/libft.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

int	g_global_exit_status;

void	handle_ctrl_c(int sig)
{
	g_global_exit_status = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	handle_ctrl_backslash(int sig)
{
	(void)sig;
	printf("quit (core dumped) -> everything is fine, "
		"this is supposed to happen\n");
}

void	handle_ctrl_c_in_command(int sig)
{
	(void)sig;
	printf("   \n");
}

void	handle_ctrl_d(int sig)
{
	printf("exit\n");
	(void)sig;
	exit(0);
}

void	handle_ctrl_c_heredoc(int sig)
{
	printf("             \n");
	exit(sig + 128);
}
