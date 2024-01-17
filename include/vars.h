/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:18:17 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 15:32:43 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_H
# define VARS_H

# define MAX_VARS 100

typedef struct s_vars
{
	char	name[50];
	char	value[150];
}			t_vars;

typedef struct s_data
{
	char			*paths;
	char			*envp;
	int				num_vars;
	int				num_shell_vars;
	char			*last_command_exit_status;
	t_vars			vc[MAX_VARS];
	t_vars			shell_vc[MAX_VARS];
	char			**tokens;
	char			**argv;
	char			**envp_arr;
	char			*path;
	int				erased_out_quotes;
	struct s_node	*ast;
}	t_data;

// vars
int			check_for_variable_setting(t_data *data, char *token);
void		init_vars(t_data *data, char **envp);
int			is_valid_variable_declaration(const char *input);

/**
 * @brief Converts the variables container to an array of strings (envp).
 *
 * This function takes a data structure containing variables and converts it
 * into the standard environment variable format (envp) required by functions
 * like execve. It allocates memory for the resulting array and returns it.
 * The caller is responsible for freeing the memory when it is no longer needed.
 *
 * @param data A data structure containing information about variables.
 * @return An array of strings (envp) representing the variables.
 */
char		**convert_vc_to_envp(t_data *data);
// set
int			set_shell_var(t_data *data, const char *name, const char *value);
int			set_var(t_data *data, const char *name, const char *value);
// export
int			export_var(t_data *data, const char *name);
int			do_export_builtin(char **tokens, t_data *data);
// unset
int			unset_shell_var(t_data *data, const char *name);
int			unset_var(t_data *data, const char *name);
int			do_unset_builtin(char **tokens, t_data *data);
// utils
char		*return_env_from_container(t_data *data);
int			find_equal_sign(char *str);
void		copy_env_var(char *env_var, t_data *data, int i);
void		exit_with_error(const char *errorMessage);
// utils_dev
void		print_vars(const t_data *data);
void		print_exported_vars(const t_data *data);
int			set_existing_var(t_data *data, int i, const char *value);

#endif
