/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmangall <lmangall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 16:23:27 by lmangall          #+#    #+#             */
/*   Updated: 2024/01/05 20:23:21 by lmangall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	t;

	dstlen = ft_strlen(dst);
	t = 0;
	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	while (src[t] != '\0' && dstlen + 1 < size)
	{
		dst[dstlen] = src[t];
		dstlen++;
		t++;
	}
	dst[dstlen] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[t]));
}
