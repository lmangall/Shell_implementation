/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:37:03 by ohoro             #+#    #+#             */
/*   Updated: 2024/01/17 15:29:14 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include "../include/main.h"
# include "../include/lexer.h"
# include "../include/vars.h"
# include "../include/parser.h"
# include "../include/executor.h"
# include "../include/expander.h"
# include "../lib/libft/src/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

/**
 * @brief Check if a string is enclosed 
 * in quotes and determine the type of quotes.
 *
 * This function examines the given string to check if it
 *  is enclosed in quotes.
 * It supports both double quotes (") and single quotes ('). 
 * The function returns:
 * - 2 if the string is enclosed in double quotes.
 * - 3 if the string is enclosed in single quotes.
 * - 5 if the string is not enclosed in quotes.
 *
 * @param str The input string to be checked.
 * @return An integer representing the type of quotes or 5 if not 
 * enclosed in quotes.
 */
int			inside_quote(const char *str);

/**
 * @brief Count the occurrences of a character in a string and check
 *  if it appears twice.
 *
 * This function counts the occurrences of a specified character
 *  in a string
 * and returns 1 if the character appears exactly twice,
 *  and 0 otherwise.
 *
 * @param str The input string to be checked.
 * @param c The character to be counted.
 * @return 1 if the character appears twice, 0 otherwise.
 */
int			contains_two(char *str, char c);

/**
 * @brief Determine the pattern of quotes in a string.
 *
 * This function analyzes the pattern of quotes in the 
 * given string and returns an integer code:
 * - 1 if the string contains double quotes (").
 * - 4 if the string contains single quotes (').
 * - 2 if the string contains both double and single quotes.
 * - 5 if the string contains neither double nor single quotes.
 *
 * @param str The input string to be analyzed.
 * @return An integer representing the quote pattern.
 */
int			quote_pattern(const char *str);
// /**
//  * @brief Replaces the variable in the given node's string with its value.
//  * 
//  * @param node The node to replace the variable in.
//  * @return int Returns 0 on success.
//  */
// static int replace_var(struct s_node *node);

// /**
//  * @brief Checks if the given node's string contains a dollar sign.
//  * 
//  * @param node The node to check.
//  * @return struct s_node* Returns the node if it contains a 
//  * dollar sign, otherwise returns NULL.
//  */
// struct s_node *contains_dollar(struct s_node *node);

/*
** Expands variables in the given command node's string.
** @param node The command node to expand variables in.
** @param data The data structure containing the variables to expand.
*/
// void	expand(struct s_node **node, t_data *data);
char		*expand(char *line, t_data *data);

/*
** Identifies the variable name in the given string.
** @param str The string to search for the variable name.
** @param data The data structure containing the variables to search for.
** @return The variable name if found, otherwise NULL.
*/
char		*identify_var(char *str, t_data *data);

/*
** Search if the first encountered $VAR exists
** If so it returns its name
** @param str The string to expand the variable in.
** @param data The data structure containing the variables to expand.
** @return The name of the VAR found.
*/
void		expand_var(char **str, t_vars **var);

/*
** Finds the value of the given variable name in the given data structure.
** @param name The name of the variable to find the value of.
** @param data The data structure containing the variables to search for.
** @return The value of the variable if found, otherwise NULL.
*/
char		*find_val(char *name, t_data *data);

/*
** Finds the variable with the given name in the given data structure.
** @param name The name of the variable to find.
** @param data The data structure containing the variables to search for.
** @return The variable if found, otherwise NULL.
*/
t_vars		*find_var(char *name, t_data *data);

void		erase_outside_quotes(char **str);

/**
 * @brief Find the first occurrence of quotes in the string.
 *
 * @param str The input string to be examined.
 * @return A pointer to the first occurrence of quotes or NULL if not found.
 */
const char	*find_first_quotes(const char *str);
/**
* @brief Find the last occurrence of quotes in the string.
*
* @param str The input string to be examined.
* @return A pointer to the last occurrence of quotes or NULL if not found.
*/
const char	*find_last_quotes(const char *str);

/**
* @return 2 if there are double quotes
*         3 if there are single quotes
*         5 if different or missing quotes
*/
int			inside_quote(const char *str);

/**
 * @brief Determine the presence and types of quotes in a given string.
 *
 * This function analyzes a string and categorizes the 
 * occurrence and types of quotes.
 *
 * @param str The input string to be examined.
 *
 * @return 0 if there are no quotes										EXPAND
 * @return 1 if there are double quotes (not inside single quotes)		EXPAND
 * @return 2 if there are single quotes inside double quotes			EXPAND
 * @return 3 if there are double quotes inside single quotes			DONT_EXPAND
 * @return 4 if there are single quotes									DONT_EXPAND
 */

char		*find_var_value(char *var_name, t_data *data);
char		*extract_variable_name(char *str, int *original_index);
void		append_variable_value(char *var_value, char *expanded_str,
				int *expanded_index);
char		*allocate_memory_for_expanded_string(char *str);
int			is_inside_single_quotes(char *str, int current_index);

#endif 
