/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 15:42:31 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/21 15:07:04 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	g;
	size_t	ret;

	i = 0;
	g = 0;
	ret = (ft_strlen(dst) + ft_strlen(src));
	if (ft_strlen(dst) > size)
		return (ft_strlen(src) + size);
	while (dst[i] && size--)
		i++;
	while (src[g] && size-- > 1)
		dst[i++] = src[g++];
	dst[i] = '\0';
	return (ret);
}
