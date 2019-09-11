/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 16:28:32 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/16 18:22:43 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int i;

	i = 0;
	while (n > 0)
	{
		if (((unsigned const char*)s)[i] == (unsigned char)c)
			return (((void*)s) + i);
		i++;
		n--;
	}
	return (NULL);
}
