/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:02:12 by lmangall          #+#    #+#             */
/*   Updated: 2023/12/12 11:07:15 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"
#include "../include/signals.h"
#include <stdio.h>
#include <stdlib.h>

void	handle_ctrl_c(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

void	handle_ctrl_backslash(int sig)
{
	(void)sig;
	printf("quit (core dumped)\n");
	//exit(0);
}

void	handle_ctrl_c_simple_command(int sig)
{
	(void)sig;
	printf("   \n");
	//exit(0);
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
	(void)sig;
	exit(0);
}