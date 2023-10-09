/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:02:12 by lmangall          #+#    #+#             */
/*   Updated: 2023/10/09 15:02:18 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shell.h"
#include "../include/signals.h"
#include <stdio.h>
#include <stdlib.h>

void	handle_ctrl_c(int sig)
{
	printf("\n");
	rl_on_new_line();       // Gehe zur neuen Zeile
	rl_replace_line("", 0); // Lösche die aktuelle Zeile
	rl_redisplay();         // Zeige die leere Zeile an
	// printf("%s ", SHELL_PROMPT); // Zeige die Eingabeaufforderung
	(void)sig; // Verhindert die Warnung über ungenutzte Variable 'sig'
}

void	handle_ctrl_backslash(int sig)
{
	// funny...shouldn't do anything :)
	(void)sig;
}

void	handle_ctrl_d(int sig)
{
	printf("\n");
	(void)sig;
	exit(0);
}

void	handle_ctrl_c_heredoc(int sig)
{
	printf("\n");
	(void)sig;
	exit(0);
}