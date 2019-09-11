/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:19:43 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/18 15:21:39 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t				lnsr;
	unsigned char		*d;
	unsigned const char	*s;

	lnsr = ft_strlen(src);
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (lnsr >= len)
	{
		while (len-- > 0)
			*d++ = *s++;
		return ((char*)dst);
	}
	if (lnsr < len)
	{
		while (*s != '\0')
			*d++ = *s++;
		lnsr = len - lnsr;
		while (lnsr-- > 0)
			*d++ = '\0';
		return ((char*)dst);
	}
	return ((char*)dst);
}
