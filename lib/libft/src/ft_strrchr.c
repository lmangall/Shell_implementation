/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:45:14 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/05 11:56:44 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	length;

	length = ft_strlen(str);
	if (!ft_isascii(c))
		return ((char *) &str[0]);
	while (length >= 0)
	{
		if (str[length] == c)
			return ((char *) &str[length]);
		length--;
	}
	return ((void *) 0);
}

/*
int    main (void)
{
    const char s[] = "trouve moi ca, ca, et ca finalement";
    char c = 'c';
    char *ret;

    ret = ft_strchr(s, c);

    printf("string after last '%c' is: '%s'\n", c, ret);
}
*/
