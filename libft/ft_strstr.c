/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbondare <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:16:01 by tbondare          #+#    #+#             */
/*   Updated: 2017/11/30 18:50:37 by tbondare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_cmp(const char *big, const char *little)
{
	size_t	cnt;

	cnt = 0;
	while (*big == *little && *little)
	{
		big++;
		little++;
		cnt++;
	}
	return (cnt);
}

char			*ft_strstr(const char *big, const char *little)
{
	const char	*l;
	const char	*in;
	size_t		cnt;

	l = little;
	if (*little == '\0')
		return ((char*)big);
	while (*big && *little)
	{
		little = l;
		cnt = 0;
		if (*big == *little)
		{
			in = big;
			cnt = ft_cmp(big, little);
			if (cnt == ft_strlen(l))
				return ((char*)in);
			big = in + 1;
		}
		big++;
	}
	return (NULL);
}
