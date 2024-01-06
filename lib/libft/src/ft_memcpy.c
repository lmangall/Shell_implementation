/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:04:49 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/06 21:43:41 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	unsigned int count;
	const char *copy_src = src;
	char *copy_dest = dest;

	for (count = 0; count <= size; count++) 
	{
		copy_dest[count] = copy_src[count];
	}
	return (dest);
}
/*
int main(void)
{
    char			src[] = "Pleaseletmebe";
    unsigned char	dest[] = "I will get you";
    size_t			n = 10;

	char	*s1 = memcpy(dest, src, n);
	char	*s2 = ft_memcpy(dest, src, n);
	printf ("memcpy: %s\nft_memcpy: %s\n", s1, s2);
}
*/