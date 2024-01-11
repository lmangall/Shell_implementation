/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:17:56 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/11 16:06:47 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H
# include "parser_nodes.h"

void	exec_pipe_redir(struct s_node *node, t_data *data);
void	first_child(struct s_node *node, int pipe_fd[2], t_data *data);
void	second_child(struct s_node *node, int pipe_fd[2], t_data *data);
void	execute_pipe_command(struct s_node *node, t_data *data);

#endif