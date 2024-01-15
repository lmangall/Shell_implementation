/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:18:14 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/15 09:57:48 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H



void	handle_ctrl_c(int sig);
void	handle_ctrl_backslash(int sig);
void	handle_ctrl_d(int sig);
void	handle_ctrl_c_heredoc(int sig);
void	handle_ctrl_c_in_command(int sig);

#endif