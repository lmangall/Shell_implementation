/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:18:02 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/11 16:06:47 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

bool				streq(char *str1, char *str2);
void				redirect_input_until(struct s_node *node);
void				redirect_input(struct s_node *node);
void				redirect_output(struct s_node *node);
void				exec_redirection(struct s_node *node, t_data *data);

#endif
