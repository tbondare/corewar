/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 16:15:04 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/15 16:38:23 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;
	int					i;

	d = dst;
	s = src;
	i = len - 1;
	if (d < s)
	{
		while (len-- > 0)
			*d++ = *s++;
	}
	else
	{
		while (len-- > 0)
		{
			d[i] = s[i];
			i--;
		}
	}
	return (dst);
}
