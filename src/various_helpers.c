/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   various_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohoro <ohoro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:36:04 by ohoro             #+#    #+#             */
/*   Updated: 2024/01/17 17:07:33 by ohoro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include "../include/executor.h"
#include "../include/expander.h"
#include "../include/free.h"
#include "../include/lexer.h"
#include "../include/main.h"
#include "../include/parser.h"
#include "../include/pipe.h"
#include "../include/redirect.h"
#include "../include/signals.h"
#include "../include/vars.h"
#include "../lib/libft/src/libft.h"
#include <errno.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

// extracted from free.c
void	free_string_array_index(char **arr, size_t i)
{
	while (arr[i] != NULL) 
	{
		if (arr[i]) 
		{
			free(arr[i]);
			arr[i] = NULL;
		}
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

// extracted from main.c
void	remove_leading_tabs(char *str)
{
	int	i;
	int	j;

	if (str == NULL)
		return ;
	i = 0;
	while (str[i] == '\t')
		i++;
	j = 0;
	while (str[i] != '\0')
	{
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
}