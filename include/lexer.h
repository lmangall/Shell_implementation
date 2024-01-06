/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:16:45 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 15:34:21 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

char	**lexer(char *line);

void	replace_form_feed_with_spaces(char *str);
char	*check_quotes_replace_ff(char *line);
// void	print_double_pointer_to_char(char **strArray);
int		contains_two(char *str, char c);
char	**put_space_back(char **tokens);
void	erase_quotes_str(char **str);
char	**erase_quotes(char **tokens);



/**
 * @brief Allocate memory for a new array of tokens.
 *
 * @param num_tokens The number of tokens in the array.
 * @return A pointer to the allocated memory for tokens.
 */
char	**allocate_memory_for_tokens(int num_tokens);
/**
 * @brief Allocate memory for a new token and copy the content without quotes.
 *
 * @param source The source token containing quotes.
 * @return A pointer to the new token without quotes.
 */
char	*copy_token_without_quotes(const char *source);
/**
 * @brief Remove quotes from each token in the array.
 *
 * @param tokens The array of tokens with quotes.
 * @return A new array of tokens without quotes.
 */
char	**erase_quotes_from_tokens(char **tokens);


#endif 
