/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:18:02 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 15:20:01 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

extern long long	g_exit_status;
bool				streq(char *str1, char *str2);
void				redirect_input_until(struct node_s *node);
void				redirect_input(struct node_s *node);
void				redirect_output(struct node_s *node);
void				exec_redirection(struct node_s *node, t_data *data);

#endif
