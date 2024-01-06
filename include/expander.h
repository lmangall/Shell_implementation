#ifndef EXPANDER_H
#define EXPANDER_H

#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "../include/main.h"
#include "../include/lexer.h"
#include "../include/vars.h"
#include "../include/parser.h"
#include "../include/executor.h"
#include "../include/expander.h"
#include "../lib/libft/src/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

// /**
//  * @brief Replaces the variable in the given node's string with its value.
//  * 
//  * @param node The node to replace the variable in.
//  * @return int Returns 0 on success.
//  */
// static int replace_var(struct node_s *node);

// /**
//  * @brief Checks if the given node's string contains a dollar sign.
//  * 
//  * @param node The node to check.
//  * @return struct node_s* Returns the node if it contains a dollar sign, otherwise returns NULL.
//  */
// struct node_s *contains_dollar(struct node_s *node);


/*
** Expands variables in the given command node's string.
** @param node The command node to expand variables in.
** @param data The data structure containing the variables to expand.
*/
// void	expand(struct node_s **node, t_data *data);
char *expand(char *line, t_data *data);

/*
** Identifies the variable name in the given string.
** @param str The string to search for the variable name.
** @param data The data structure containing the variables to search for.
** @return The variable name if found, otherwise NULL.
*/
char	*identify_var(char *str, t_data *data);

/*
** Search if the first encountered $VAR exists
** If so it returns its name
** @param str The string to expand the variable in.
** @param data The data structure containing the variables to expand.
** @return The name of the VAR found.
*/
void	expand_var(char **str, t_vars **var);

/*
** Finds the value of the given variable name in the given data structure.
** @param name The name of the variable to find the value of.
** @param data The data structure containing the variables to search for.
** @return The value of the variable if found, otherwise NULL.
*/
char	*find_val(char *name, t_data *data);

/*
** Finds the variable with the given name in the given data structure.
** @param name The name of the variable to find.
** @param data The data structure containing the variables to search for.
** @return The variable if found, otherwise NULL.
*/
t_vars	*find_var(char *name, t_data *data);


int quote_pattern(const char *str);
char *erase_outside_quotes(const char *str);


/**
 * @brief Find the first occurrence of quotes in the string.
 *
 * @param str The input string to be examined.
 * @return A pointer to the first occurrence of quotes or NULL if not found.
 */
const	char	*find_first_quotes(const char *str);
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
int inside_quote(const char *str);

/**
 * @brief Determine the presence and types of quotes in a given string.
 *
 * This function analyzes a string and categorizes the occurrence and types of quotes.
 *
 * @param str The input string to be examined.
 *
 * @return 0 if there are no quotes										EXPAND
 * @return 1 if there are double quotes (not inside single quotes)		EXPAND
 * @return 2 if there are single quotes inside double quotes			EXPAND
 * @return 3 if there are double quotes inside single quotes			DONT_EXPAND
 * @return 4 if there are single quotes									DONT_EXPAND
 */
int	quote_pattern(const char *str);

#endif 
