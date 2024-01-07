/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:10:59 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 22:34:36 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../include/main.h"
# include "parser_nodes.h"

int	check_for_builtins(char *line, t_data *data);
int	do_cd_builtin(char **argv, t_data *data);
int	do_echo_builtin(char **argv);
int	do_pwd_builtin(t_data *data);
int	do_env_builtin(t_data *data);
int	do_exit_builtin(char *line, t_data *data);

#endif