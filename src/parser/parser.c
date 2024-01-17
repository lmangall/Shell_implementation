/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 18:27:44 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/17 15:47:12 by ohoro            ###   ########.fr       */
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
		var->str = ft_strdup(tokens[i]);
		(void)data;
		add_child_node(root, var);
		i++;
	}
	free_string_array(tokens);
	return (root);
}

void	erase_outside_quotes_on_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if ((contains_two(tokens[i], '\"') || contains_two(tokens[i], '\'')))
			erase_outside_quotes(&tokens[i]);
		i++;
	}
}

int	parse_and_execute(char *line, t_data *data)
{
	char	**tokens;

	check_quotes_replace_ff(line);
	tokens = lexer(line);
	put_space_back(tokens);
	if (data->erased_out_quotes == 0)
		erase_outside_quotes_on_tokens(tokens);
	simple_or_advanced(tokens, data);
	return (1);
}
