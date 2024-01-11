/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:11:07 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/11 16:04:42 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include "vars.h"
# include "parser_nodes.h"

char	*search_path(char *cmd, t_data *data);
int		exec_cmd(char**argv, t_data *data);
/**
 * @brief Update the command exit status and perform cleanup.
 *
 * This function takes the exit status of a command,
 *  updates the command exit status
 * variable, and sets the corresponding variable
 * in the data structure. It also performs
 * any necessary cleanup operations.
 *
 * @param status The exit status of the executed command.
 * @param data   A pointer to the data structure containing relevant information.
 */
void	update_status_and_cleanup(int status, t_data *data);

/**
 * @brief Execute a command and update the status.
 *
 * This function determines the type of command (advanced or simple),
 * executes it, and updates the command exit status and relevant variables.
 *
 * @param tokens The array of command tokens.
 * @param data   A pointer to the data structure containing relevant information.
 */
void	simple_or_advanced(char **tokens, t_data *data);

char	*duplicate_string(const char *str);
char	**build_argv(struct s_node *root_node, int *argc);
void	free_argv(char **argv);
int		do_simple_command(struct s_node *root_node, t_data *data);


#endif