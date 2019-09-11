/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 19:36:04 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/16 16:26:49 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;

	d = dst;
	s = src;
	while (n > 0)
	{
		if (*s == (unsigned char)c)
		{
			*d = *s;
			return (d + 1);
		}
		*d++ = *s++;
		n--;
	}
	return (NULL);
}
