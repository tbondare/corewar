/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 16:35:33 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/22 13:22:41 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	ch;
	size_t			len;

	ch = (unsigned char)c;
	len = ft_strlen(s) + 1;
	while (len-- > 0)
	{
		if (s[len] == ch)
		{
			s = &s[len];
			return ((char *)s);
		}
	}
	return (NULL);
}
