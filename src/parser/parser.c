/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:27:44 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/15 22:33:46 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"
#include "../../include/free.h"
#include "../../include/parser.h"
#include "../../include/parser_nodes.h"
#include "../../include/vars.h"
#include "../../lib/libft/src/libft.h"
#include <errno.h>
#include <unistd.h>

struct s_node	*parse_simple_command(char **tokens, t_data *data)
{
	int				i;
	struct s_node	*root;
	struct s_node	*var;

	i = 0;
	root = new_node(ROOT);
	if (!root)
		return (NULL);
	while (tokens[i] != NULL)
	{
		var = new_node(VAR);
		if (!var)
			return (NULL);
		var->str = tokens[i];
		(void)data;
		add_child_node(root, var);
		i++;
	}
	return (root);
}

static void	erase_outside_quotes_on_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (contains_two(tokens[i], '\"') || contains_two(tokens[i], '\''))
			tokens[i] = erase_outside_quotes(tokens[i]);
		i++;
	}
}



// static void   replace_space_by_ff(char *str)
// {
// 	int i;

// 	i = 0;
// 	if(str[i] == ' ')
// 		while(str[i] == ' ')
// 			i++;
// 	while(str[i] != ' ')
// 	{
// 		i++;
// 	}
// 	i++;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == ' ')
// 			str[i] = '\f';
// 		i++;
// 	}
// }

int	parse_and_execute(char *line, t_data *data)
{
	char	**tokens;


	// replace_space_by_ff(line);
	check_quotes_replace_ff(line);
	tokens = lexer(line);
	put_space_back(tokens);

	data->tokens = tokens;
	if (data->erased_out_quotes == 0)
		erase_outside_quotes_on_tokens(tokens);
	simple_or_advanced(tokens, data);
	return (1);
}